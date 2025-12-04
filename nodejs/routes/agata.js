const { Router } = require('express');
const AgataCrypto = require('../utils/crypto');
const logger = require('../utils/logger');
const fileLogger = require('../utils/fileLogger');
const { normalizeToFlat } = require('../utils/agataParser');

const router = Router();

// FILA DE COMANDOS (simples, em memória)
const pendingCommands = new Map(); // serial -> comando

// ROTA PRINCIPAL - Recebe telemetria do device
router.post('/agata', (req, res) => {
  const rawData = req.body.raw || req.body;

  if (!rawData || typeof rawData !== 'string' || rawData.length < 10) {
    return res.status(400).json({ error: 'Dados inválidos' });
  }

  const serial = rawData.substring(0, 6);
  const encryptedPayload = rawData.substring(6);

  // 1. Descriptografar
  let decrypted;
  try {
    decrypted = AgataCrypto.decrypt(serial, encryptedPayload);
  } catch (err) {
    logger.error('Erro ao descriptografar', { serial, error: err.message });
    return res.status(200).json({ code: 200, config: 0, data: "" });
  }

  // 2. Parsear JSON
  let payload;
  try {
    payload = JSON.parse(decrypted);
    logger.info('Dados recebidos', { serial, blc: payload.blc });
    logger.logProcessedData({ serial, payload });
  } catch (err) {
    logger.error('Erro ao parsear JSON', { serial, error: err.message });
  }

  // 3. Verificar se há comando pendente para este device
  const comando = pendingCommands.get(serial);

  if (comando) {
    // Remove da fila e envia
    pendingCommands.delete(serial);

    const comandoStr = typeof comando === 'string' ? comando : JSON.stringify(comando);
    const encrypted = AgataCrypto.encrypt(serial, comandoStr);

    logger.info('Enviando comando para device', { serial, comando });

    return res.status(200).json({
      code: 200,
      config: 1,
      data: encrypted
    });
  }

  // 4. Resposta padrão (sem comando)
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

module.exports = router;