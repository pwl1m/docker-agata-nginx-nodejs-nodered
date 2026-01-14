'use strict';
const { Router } = require('express');
const router = Router();
const crypto = require('crypto');
const AgataCrypto = require('../utils/crypto');
const logger = require('../utils/logger');
const redisClient = require('../utils/redisClient');
const repository = require('../database/repository');
const agataHelpers = require('../utils/agataHelpers');


// HELPERS
function getRecentPayloads(req) {
  return req.app.get('recentPayloads') || new Map();
}

// ROTAS ESPECÍFICAS PRIMEIRO

// POST /agata/send-command - ENFILEIRAR COMANDO NO REDIS
router.post('/agata/send-command', async (req, res) => {
  logger.info('🟢 Recebido comando para enfileirar', { body: req.body });

  try {
    const { serial, comando, formato, usuario_id } = req.body || {};

    if (!serial || !/^\d{6}$/.test(serial)) {
      logger.warn('❌ Serial inválido', { serial });
      return res.status(400).json({ error: 'Serial inválido (deve ter 6 dígitos)' });
    }

    if (!comando) {
      logger.warn('❌ Comando não informado');
      return res.status(400).json({ error: 'Comando não informado' });
    }

    // Determinar formato de criptografia
    let dadosParaCriptografar;
    if (formato === 'array' && comando.alteracao) {
      dadosParaCriptografar = comando.alteracao;
    } else {
      dadosParaCriptografar = comando;
    }

    const comandoJson = JSON.stringify(dadosParaCriptografar);

    logger.info('🔐 Criptografando comando', {
      serial,
      formato: formato || 'object',
      tamanho: comandoJson.length,
      elementos: Array.isArray(dadosParaCriptografar) ? dadosParaCriptografar.length : 'N/A',
      preview: comandoJson.substring(0, 100)
    });

    const comandoCriptografado = AgataCrypto.encrypt(serial, comandoJson);

    if (!comandoCriptografado) {
      throw new Error('Falha na criptografia do comando');
    }

    // Validar integridade (descriptografar para testar)
    const testeDecrypt = AgataCrypto.decrypt(serial, comandoCriptografado);
    const integridadeOk = testeDecrypt === comandoJson;

    logger.info('🔓 Validação de integridade', {
      serial,
      ok: integridadeOk,
      tamanhoOriginal: comandoJson.length,
      tamanhoDescriptografado: testeDecrypt.length
    });

    if (!integridadeOk) {
      throw new Error('Falha na validação de integridade da criptografia');
    }

    // Registrar alteração no banco (se usuario_id informado)
    // O usuario_id é opcional. Se presente, registra no banco. O formato do comando para o device é mantido conforme documentação.
    // O usuario_id nunca vai para o device - é usado apenas para registrar no banco quem fez a alteração.
    // O payload para o device permanece inalterado.

    let alteracaoId = null;
    if (usuario_id) {
      try {
        alteracaoId = await repository.saveAlteracaoUsuario({
          serial,
          usuario_id,
          comando_enviado: dadosParaCriptografar,
          ip_origem: req.ip || req.headers['x-real-ip'],
          user_agent: req.headers['user-agent']
        });
        logger.info('✅ Alteração registrada', { serial, usuario_id, alteracaoId });
      } catch (dbErr) {
        logger.error('⚠️ Erro ao registrar alteração (não bloqueante)', { error: dbErr.message });
      }
    }

    const respostaParaDevice = {
      code: 200,
      config: 1,
      data: comandoCriptografado
    };

    await redisClient.set(
      `agata:cmd:${serial}`,
      JSON.stringify(respostaParaDevice),
      { EX: 3600 }
    );

    // Atualizar status para 'enviado'
    if (alteracaoId) {
      repository.updateAlteracaoStatus(alteracaoId, 'enviado').catch(() => {});
    }

    logger.info('✅ Comando enfileirado no Redis', {
      serial,
      formato: formato || 'object',
      alteracaoId,
      ttl: 3600
    });

    res.json({
      success: true,
      message: `Comando enfileirado para ${serial}`,
      alteracao_id: alteracaoId,
      formato: formato || 'object',
      tamanho: comandoJson.length
    });

  } catch (error) {
    logger.error('❌ Erro ao enfileirar comando', {
      error: error.message,
      stack: error.stack
    });
    res.status(500).json({ error: error.message });
  }
});

// GET /agata/queue/:serial - OBSERVADOR DE FILA (REDIS)
router.get('/agata/queue/:serial', async (req, res) => {
  const { serial } = req.params;

  try {
    const command = await redisClient.get(`agata:cmd:${serial}`);

    logger.info(`[QUEUE_OBSERVER] Consulta Redis para Serial: ${serial}`, {
      found: !!command
    });

    res.json({
      serial,
      has_pending_command: !!command,
      command: command ? JSON.parse(command) : null
    });
  } catch (err) {
    logger.error('Erro ao consultar fila', { serial, error: err.message });
    res.status(500).json({ error: err.message });
  }
});

// GET /agata/queue - VER FILA DE COMANDOS (REDIS)
router.get('/agata/queue', async (req, res) => {
  try {
    const keys = await redisClient.keys('agata:cmd:*');
    const queue = {};

    for (const key of keys) {
      const serial = key.replace('agata:cmd:', '');
      const value = await redisClient.get(key);
      queue[serial] = value ? JSON.parse(value) : null;
    }

    logger.info('[QUEUE_LIST] Listagem completa da fila', { total: keys.length });

    res.json({
      total: keys.length,
      commands: queue
    });
  } catch (err) {
    logger.error('Erro ao listar fila', { error: err.message });
    res.status(500).json({ error: err.message });
  }
});

// POST /agata - TELEMETRIA
router.post(/^\/agata\/?$/, async (req, res) => {
  const rawBody = req.body || '';

  // Validação 1: Tamanho mínimo
  if (!rawBody || rawBody.length < 10) {
    logger.error('❌ Payload muito curto', { length: rawBody.length });
    const body = JSON.stringify({ code: 200, config: 0, data: "" });
    res.set('Content-Type', 'application/json');
    res.set('Content-Length', String(Buffer.byteLength(body)));
    res.set('Connection', 'close');
    return res.status(200).send(body);
  }

  // Validação 2: Serial válido
  const serial = rawBody.substring(0, 6);

  if (!/^\d{6}$/.test(serial)) {
    logger.error('❌ Serial inválido detectado', {
      serial,
      preview: rawBody.substring(0, 50),
      length: rawBody.length
    });
    const body = JSON.stringify({ code: 200, config: 0, data: "" });
    res.set('Content-Type', 'application/json');
    res.set('Content-Length', String(Buffer.byteLength(body)));
    res.set('Connection', 'close');
    return res.status(200).send(body);
  }

  // Validação 3: Detectar payload duplicado (cache 30s)
  const recentPayloads = getRecentPayloads(req);

  try {
    const payloadHash = crypto.createHash('md5').update(rawBody).digest('hex');
    const recent = recentPayloads.get(serial);

    if (recent && recent.hash === payloadHash && (Date.now() - recent.timestamp) < 30000) {
      logger.warn('⚠️ Payload duplicado detectado', {
        serial,
        age: Date.now() - recent.timestamp
      });
      const body = JSON.stringify({ code: 200, config: 0, data: "" });
      res.set('Content-Type', 'application/json');
      res.set('Content-Length', String(Buffer.byteLength(body)));
      res.set('Connection', 'close');
      return res.status(200).send(body);
    }

    recentPayloads.set(serial, { hash: payloadHash, timestamp: Date.now() });

    setTimeout(() => {
      const entry = recentPayloads.get(serial);
      if (entry && (Date.now() - entry.timestamp) > 60000) {
        recentPayloads.delete(serial);
      }
    }, 60000);
  } catch (hashErr) {
    logger.error('❌ Erro ao verificar duplicação', { serial, error: hashErr.message });
  }

  const encryptedPayload = rawBody.substring(6);

  // Descriptografia
  let decrypted, payload;
  try {
    decrypted = AgataCrypto.decrypt(serial, encryptedPayload);
    payload = JSON.parse(decrypted.replace(/[\x00-\x1F\x80-\xFF]/g, ''));

    logger.info('✅ Telemetria processada', {
      serial,
      blc: payload.blc,
      eventos: payload.event?.length || 0,
      erros: payload.erros?.length || 0
    });

    logger.logProcessedData({ serial, payload });

    // Publicar no Redis para WebSocket
    try {
      const message = JSON.stringify({
        type: 'telemetry',
        serial,
        timestamp: new Date().toISOString(),
        data: payload
      });

      redisClient.publish('device_updates', message)
        .catch(err => logger.error('❌ Erro ao publicar no Redis', { error: err.message }));
    } catch (redisErr) {
      logger.error('❌ Erro ao preparar mensagem Redis', { error: redisErr.message });
    }

  } catch (err) {
    logger.error('❌ Erro ao processar telemetria', { serial, error: err.message });
    const body = JSON.stringify({ code: 200, config: 0, data: "" });
    res.set('Content-Type', 'application/json');
    res.set('Content-Length', String(Buffer.byteLength(body)));
    res.set('Connection', 'close');
    return res.status(200).send(body);
  }

  // Verificar se há comando pendente no Redis
  try {
    const redisKey = `agata:cmd:${serial}`;
    const comandoPendenteRaw = await redisClient.get(redisKey);

    if (comandoPendenteRaw) {
      await redisClient.del(redisKey);
      const comandoPendente = JSON.parse(comandoPendenteRaw);

      const respostaCompacta = JSON.stringify(comandoPendente);

      logger.info('📤 Enviando comando do Redis para device', {
        serial,
        tamanho: respostaCompacta.length,
        config: comandoPendente.config
      });

      res.set('Content-Type', 'application/json');
      res.set('Content-Length', String(Buffer.byteLength(respostaCompacta)));
      res.set('Connection', 'close');
      return res.status(200).send(respostaCompacta);
    }

    logger.debug('ℹ️ Sem comando pendente', { serial });
    const body = JSON.stringify({ code: 200, config: 0, data: "" });
    res.set('Content-Type', 'application/json');
    res.set('Content-Length', String(Buffer.byteLength(body)));
    res.set('Connection', 'close');
    return res.status(200).send(body);

  } catch (redisErr) {
    logger.error('❌ Erro ao verificar comando pendente', { serial, error: redisErr.message });
    const body = JSON.stringify({ code: 200, config: 0, data: "" });
    res.set('Content-Type', 'application/json');
    res.set('Content-Length', String(Buffer.byteLength(body)));
    res.set('Connection', 'close');
    return res.status(200).send(body);
  }
});

router.post('/agata/send-command-timestamp', async (req, res) => {
  logger.info('🔔 Recebido comando (timestamp route) para enfileirar', { body: req.body });

  try {
    const { serial, comando, formato, usuario_id } = req.body || {};

    if (!serial || !/^\d{6}$/.test(serial)) {
      return res.status(400).json({ error: 'Serial inválido' });
    }
    if (!comando) {
      return res.status(400).json({ error: 'Campo comando ausente' });
    }

    // Determinar dados que vão para o device (mesma lógica do send-command)
    let dadosParaCriptografar;
    if (formato === 'array' && comando.alteracao) {
      dadosParaCriptografar = comando.alteracao;
    } else {
      dadosParaCriptografar = comando;
    }

    // Injeta timestamp SEMPRE (s, índice 28)
    dadosParaCriptografar = agataHelpers.injectTimestamp(dadosParaCriptografar, {
      unit: 's',
      index: Number(process.env.AGATA_TIMESTAMP_INDEX || 28)
    });
    logger.info('Timestamp injetado (send-command-timestamp)', { serial });

    // Assinatura normalizada e checagem (opcional)
    const signature = agataHelpers.normalizeForSignature(dadosParaCriptografar, { index: Number(process.env.AGATA_TIMESTAMP_INDEX || 28) });
    const lastKey = `agata:last-alteration:${serial}`;
    let alteracaoId = null;

    try {
      if (process.env.AGATA_ENABLE_SIGNATURE_CHECK === 'true') {
        const last = await redisClient.get(lastKey);
        if (last === signature) {
          logger.info('Alteração idêntica à última registrada — pulando gravação no banco', { serial });
        } else {
          alteracaoId = await repository.saveAlteracaoUsuario({
            serial,
            usuario_id,
            comando_enviado: dadosParaCriptografar,
            ip_origem: req.ip || req.headers['x-real-ip'],
            user_agent: req.headers['user-agent']
          });
          await redisClient.set(lastKey, signature, { EX: Number(process.env.AGATA_LAST_ALTER_TTL_SECONDS || 86400) });
          logger.info('Alteração registrada (send-command-timestamp)', { serial, alteracaoId });
        }
      } else {
        alteracaoId = await repository.saveAlteracaoUsuario({
          serial,
          usuario_id,
          comando_enviado: dadosParaCriptografar,
          ip_origem: req.ip || req.headers['x-real-ip'],
          user_agent: req.headers['user-agent']
        });
        logger.info('Alteração registrada sem checagem (send-command-timestamp)', { serial, alteracaoId });
      }
    } catch (dbErr) {
      logger.warn('Erro ao gravar alteração (não bloqueante)', { error: dbErr.message });
    }

    // Criptografar e publicar/enfileirar
    const comandoCriptografado = AgataCrypto.encrypt(serial, JSON.stringify(dadosParaCriptografar));
    if (!comandoCriptografado) {
      return res.status(500).json({ error: 'Falha ao criptografar comando' });
    }

    // Mesma estrutura usada por /agata (garante que o device irá receber o comando)
    const respostaParaDevice = {
      code: 200,
      config: 1,
      data: comandoCriptografado
    };
    // TTL consistente com send-command
    const ttl = Number(process.env.AGATA_COMMAND_TTL_SECONDS || 3600);
    await redisClient.set(`agata:cmd:${serial}`, JSON.stringify(respostaParaDevice), { EX: ttl });
    logger.info('✅ Comando enfileirado no Redis (key agata:cmd)', { serial, ttl });

    const channel = process.env.AGATA_QUEUE_CHANNEL || 'agata:commands';
    await redisClient.publish(channel, JSON.stringify({ serial, payload: comandoCriptografado }));

    return res.json({
      ok: true,
      enqueued: true,
      channel,
      serial,
      alteracaoId,
      encrypted_preview: comandoCriptografado.substring(0, 40)
    });
  } catch (error) {
    logger.error('Erro em send-command-timestamp', { error: error.message });
    return res.status(500).json({ error: 'Erro interno' });
  }
});

module.exports = router;