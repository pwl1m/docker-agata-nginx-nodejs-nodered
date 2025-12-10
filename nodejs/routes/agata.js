const { Router } = require('express');
const AgataCrypto = require('../utils/crypto');
const logger = require('../utils/logger');
const fileLogger = require('../utils/fileLogger');
const { normalizeToFlat } = require('../utils/agataParser');
const changeDetector = require('../utils/changeDetector');
const configValidator = require('../utils/configValidator');

const router = Router();

// FILA DE COMANDOS (simples, em memória)
const pendingCommands = new Map(); // serial -> comando

// ROTA PRINCIPAL - Recebe telemetria do device
router.post('/agata', (req, res) => {
  logger.info('🎯 Rota /agata acionada', { 
    hasRawBody: !!req.rawBody, 
    hasBody: !!req.body,
    rawBodyType: typeof req.rawBody,
    bodyType: typeof req.body
  });
  
  // ✅ Pegar rawBody que foi populado pelo middleware
  const rawData = req.rawBody || req.body;
  
  const bodyPreview = typeof rawData === 'string' ? rawData.slice(0, 100) : JSON.stringify(rawData).slice(0, 128);
  logger.info('🔍 /agata CORPO BRUTO', { preview: bodyPreview, contentType: req.headers['content-type'] });

  if (!rawData || typeof rawData !== 'string' || rawData.length < 10) {
    logger.error('Payload muito curto', { length: rawData ? rawData.length : 0 });
    return res.status(200).json({ code: 200, config: 0, data: "" });
  }

  // Extrai serial/payload
  const serial = rawData.substring(0, 6);
  const encryptedPayload = rawData.substring(6);

  // 1. Descriptografar
  let decrypted;
  try {
    decrypted = AgataCrypto.decrypt(serial, encryptedPayload);
    logger.info('✅ Descriptografia bem-sucedida', { serial });
  } catch (err) {
    logger.error('❌ Erro ao descriptografar', { serial, error: err.message });
    return res.status(200).json({ code: 200, config: 0, data: "" });
  }

  // 2. Parsear JSON
  let payload;
  try {
    const sanitized = decrypted.replace(/[\x00-\x1F\x80-\xFF]/g, '');
    payload = JSON.parse(sanitized);
    logger.info('✅ Dados recebidos', { serial, blc: payload.blc });

    // 3. Salvar com detecção de mudanças
    fileLogger.saveWithChangeDetection(payload, 'agata')
      .then(saveResult => {
        if (saveResult && saveResult.hasChanges) {
          logger.info('💾 Dados com mudanças salvos', {
            serial,
            changedFields: saveResult.changedFields,
            filepath: saveResult.filepath
          });
        }
      })
      .catch(err => logger.error('Erro ao salvar', { serial, error: err.message }));

  } catch (err) {
    logger.error('❌ Erro ao parsear JSON', { 
      serial, 
      error: err.message, 
      decryptedPreview: decrypted ? decrypted.slice(0, 120) : '' 
    });
  }

  // 4. Verificar se há comando pendente para este device
  const comando = pendingCommands.get(serial);

  if (comando) {
    pendingCommands.delete(serial);

    // Se já vier no formato pronto (code, config, data)
    if (comando.code && comando.config !== undefined && comando.data) {
      logger.info('📤 Enviando comando para device', { serial, type: 'config' });
      return res.status(200).json(comando);
    }

    // Senão, criptografa o comando genérico
    const comandoStr = typeof comando === 'string' ? comando : JSON.stringify(comando);
    const encrypted = AgataCrypto.encrypt(serial, comandoStr);

    logger.info('📤 Enviando comando para device', { serial, type: 'generic' });

    return res.status(200).json({
      code: 200,
      config: 1,
      data: encrypted
    });
  }

  // 5. Resposta padrão (sem comando)
  res.status(200).json({
    code: 200,
    config: 0,
    data: ""
  });
});

// ENFILEIRAR COMANDO
router.post('/agata/send-command', (req, res) => {
  const { serial, comando } = req.body;

  if (!serial || !comando) {
    return res.status(400).json({ error: 'serial e comando são obrigatórios' });
  }

  pendingCommands.set(serial, comando);

  logger.info('Comando enfileirado', { serial });

  res.json({
    ok: true,
    message: 'Comando enfileirado. Será enviado no próximo ciclo do device.',
    serial
  });
});

// VER COMANDOS PENDENTES
router.get('/agata/queue/:serial', (req, res) => {
  const serial = req.params.serial;
  const comando = pendingCommands.get(serial);

  res.json({
    serial,
    hasPending: !!comando,
    comando: comando || null
  });
});

// VER TODOS OS COMANDOS PENDENTES
router.get('/agata/queue', (req, res) => {
  const all = {};
  pendingCommands.forEach((cmd, serial) => {
    all[serial] = cmd;
  });

  res.json({
    total: pendingCommands.size,
    commands: all
  });
});

// ENDPOINT PARA VERIFICAR MUDANÇAS
router.get('/agata/changes/:serial', (req, res) => {
  const serial = req.params.serial;
  const limit = parseInt(req.query.limit) || 10;
  
  const history = changeDetector.getChangeHistory(serial, limit);
  
  res.json({
    serial,
    history,
    totalChanges: history.length
  });
});

// ENDPOINT PARA VERIFICAR ÚLTIMOS VALORES
router.get('/agata/last-values/:serial', (req, res) => {
  const serial = req.params.serial;
  const map = changeDetector.lastValues.get(serial);
  
  if (!map) {
    return res.status(404).json({
      error: 'Serial não encontrado ou sem histórico'
    });
  }
  
  res.json({
    serial,
    lastValues: Object.fromEntries(map),
    lastUpdate: new Date().toISOString()
  });
});

// POST nova configuração
router.post('/agata/config/:serial', (req, res) => {
  const serial = req.params.serial;
  const config = req.body;
  
  // Validar
  const validation = configValidator.validateConfig(config);
  if (!validation.valid) {
    return res.status(400).json({
      error: 'Configuração inválida',
      details: validation.errors
    });
  }
  
  // Montar array [29 valores] com timestamp automático
  const configArray = configValidator.buildConfigArray(config, 1);
  
  // Montar objeto com chave "alteracao"
  const comandoObj = {
    alteracao: configArray
  };
  
  // Criptografar o objeto completo
  const comandoStr = JSON.stringify(comandoObj);
  const encrypted = AgataCrypto.encrypt(serial, comandoStr);
  
  // Formato do comando para o device
  const comando = {
    code: 200,
    config: 1,
    data: encrypted
  };
  
  // Enfileirar
  pendingCommands.set(serial, comando);
  
  logger.info('Config enfileirada', { serial, array: configArray });
  
  res.json({
    ok: true,
    serial,
    enfileirado: true
  });
});

module.exports = router;