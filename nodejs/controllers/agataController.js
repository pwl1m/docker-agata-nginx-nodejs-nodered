const redisClient = require('../utils/redisClient');
const websocketManager = require('../utils/websocketManager');
const logger = require('../utils/logger');
const fileLogger = require('../utils/fileLogger');
const { normalizeToFlat } = require('../utils/agataParser');
const AgataCrypto = require('../utils/crypto');

let latestPayload = null;
const stats = {
  total_requests: 0,
  successful: 0,
  failed_decrypt: 0,
  failed_parse: 0,
  sanitized: 0
};

// fila em memória (substituir por DB depois)
const commandQueue = new Map(); // serial -> [ { id, comando, tentativas, ultima } ]

function enqueueCommand(serial, comando) {
  const arr = commandQueue.get(serial) || [];
  arr.push({ id: Date.now(), comando, tentativas: 0, ultima: 0 });
  commandQueue.set(serial, arr);
}

function getNextCommand(serial) {
  const arr = commandQueue.get(serial) || [];
  const now = Date.now();
  for (const cmd of arr) {
    // Retry se nunca enviado ou passou 60s desde última tentativa e tentativas < 3
    if ((cmd.ultima === 0 || (now - cmd.ultima) > 60000) && cmd.tentativas < 3) {
      cmd.tentativas++;
      cmd.ultima = now;
      return cmd;
    }
  }
  return null;
}

exports.injectTestCommand = (req, res) => {
  const { serial, comando } = req.body;
  if (!serial || !comando) {
    logger.error('Comando de teste faltando serial/comando', { body: req.body });
    return res.status(400).json({ error: 'serial/comando faltando' });
  }
  enqueueCommand(serial, comando);
  logger.info('Comando de teste enfileirado', { serial, comando });
  return res.json({ ok: true });
};

exports.ingest = async (req, res) => {
    const rawData = req.body.raw || req.body;
    stats.total_requests++;

    // Extrair o serial e descriptografar o payload
    const serial = rawData.substring(0, 6);
    const encryptedPayload = rawData.substring(6);
    let decryptedPayload;
    try {
        decryptedPayload = AgataCrypto.decrypt(serial, encryptedPayload);
        // Salvar dado puro (descriptografado)
        await fileLogger.logDecryptedData(decryptedPayload, { serial, ip: req.ip });
    } catch (err) {
        logger.error('Erro na descriptografia', { serial, error: err.message, ip: req.ip });
        await fileLogger.logRawData({ serial, encryptedPayload, error: err.message }, 'decrypt-error');
        stats.failed_decrypt++;
        return res.status(400).json({ error: 'Falha na descriptografia' });
    }

    if (!decryptedPayload) {
        logger.error('Falha na descriptografia', { serial, ip: req.ip });
        await fileLogger.logRawData({ serial, encryptedPayload }, 'decrypt-error');
        stats.failed_decrypt++;
        return res.status(400).json({ error: 'Falha na descriptografia' });
    }

    let parsedPayload;
    let flatPayload;
    try {
        parsedPayload = JSON.parse(decryptedPayload);
        // Normalizar para modelo plano
        flatPayload = normalizeToFlat(parsedPayload, req.ip)[0];
        // Salvar modelo plano na nova pasta
        await fileLogger.saveFlatProcessedData(flatPayload);
    } catch (err) {
        logger.error('Falha no parsing do payload', { serial, decryptedPayload, error: err.message });
        await fileLogger.logRawData({ serial, decryptedPayload, error: err.message }, 'parse-error');
        stats.failed_parse++;
        return res.status(400).json({ error: 'Falha no parsing do payload' });
    }

    // Logar os dados processados
    logger.logProcessedData(parsedPayload);
    await fileLogger.saveAllDevicesData(serial, parsedPayload);
    await fileLogger.logTextTransaction(parsedPayload, 'agata');

    stats.successful++;
    latestPayload = { serial, payload: parsedPayload };

    // Auditoria: comando executado, se houver
    if (parsedPayload.comando) {
        logger.info('Comando executado', { serial, comando: parsedPayload.comando });
        await fileLogger.logRawData({ serial, comando: parsedPayload.comando }, 'command-executed');
    }

    // WebSocket: notificar clientes
    try {
        websocketManager.broadcast({ serial, payload: parsedPayload });
        logger.info('WebSocket broadcast', { serial });
    } catch (err) {
        logger.error('Erro no WebSocket broadcast', { serial, error: err.message });
    }

    // Redis: exemplo de log de erro
    try {
        await redisClient.set(`device:${serial}:last`, JSON.stringify(parsedPayload));
    } catch (err) {
        logger.error('Erro ao salvar no Redis', { serial, error: err.message });
    }

    // Retornar a resposta
    return res.json({ ok: true, serial, payload: parsedPayload });
};

exports.latest = (req, res) => {
  if (!latestPayload) {
    logger.info('Consulta ao latestPayload sem dados');
    return res.status(404).json({ error: 'Nenhum dado recebido ainda' });
  }
  logger.info('Consulta ao latestPayload', { serial: latestPayload.serial });
  res.json(latestPayload);
};

exports.legacy = (req, res) => {
  if (!latestPayload) {
    logger.info('Consulta ao legacy sem dados');
    return res.status(404).json({ error: 'Nenhum dado recebido ainda' });
  }
  logger.info('Consulta ao legacy', { serial: latestPayload.serial });
  res.json([latestPayload]);
};

exports.history = async (req, res) => {
  const serial = req.params.serial || req.query.serial;

  if (!serial || !/^\d{6}$/.test(serial)) {
    logger.error('Serial inválido na consulta de histórico', { serial });
    return res.status(400).json({ error: 'Serial inválido (esperado: 6 dígitos)' });
  }

  try {
    const fs = require('fs').promises;
    const path = require('path');
    const filepath = path.join(__dirname, '../logs/processed', `device-${serial}.json`);

    const data = await fs.readFile(filepath, 'utf8');
    const history = JSON.parse(data);

    logger.info('Histórico consultado', { serial, total: history.length });
    res.json({
      serial,
      total: history.length,
      data: history
    });
  } catch (err) {
    logger.error('Histórico não encontrado', { serial, error: err.message });
    res.status(404).json({
      error: 'Histórico não encontrado',
      serial,
      message: err.message
    });
  }
};

exports.summary = async (req, res) => {
  try {
    const fs = require('fs').promises;
    const path = require('path');
    const filepath = path.join(__dirname, '../logs/processed', 'device-summary.json');

    const data = await fs.readFile(filepath, 'utf8');
    const summary = JSON.parse(data);

    logger.info('Resumo consultado', { total: Object.keys(summary).length });
    res.json(summary);
  } catch (err) {
    logger.error('Resumo não encontrado', { error: err.message });
    res.status(404).json({
      error: 'Summary não encontrado',
      message: err.message
    });
  }
};

exports.cleanup = async (req, res) => {
  try {
    const fs = require('fs').promises;
    const path = require('path');
    const processedDir = path.join(__dirname, '../logs/processed');

    let removed = [];

    // Remover arquivos de devices inválidos
    const invalidSerials = ['unknown', 'invalid', 'null', 'undefined'];

    for (const serial of invalidSerials) {
      const filename = `device-${serial}.json`;
      const filepath = path.join(processedDir, filename);

      try {
        await fs.unlink(filepath);
        removed.push(filename);
        logger.info('Arquivo removido', { filename });
      } catch (err) {
        // Arquivo não existe, ok
      }
    }

    // Limpar summary
    const summaryFile = path.join(processedDir, 'device-summary.json');
    try {
      const data = await fs.readFile(summaryFile, 'utf8');
      const summary = JSON.parse(data);

      let cleanedCount = 0;
      for (const serial of invalidSerials) {
        if (summary[serial]) {
          delete summary[serial];
          cleanedCount++;
        }
      }

      await fs.writeFile(summaryFile, JSON.stringify(summary, null, 2));
      logger.info('Summary limpo', { cleanedCount });
    } catch (err) {
      // Summary não existe, ok
    }

    logger.info('Cleanup realizado', { removed_files: removed });
    res.json({
      ok: true,
      removed_files: removed,
      timestamp: new Date().toISOString()
    });
  } catch (err) {
    logger.error('Erro no cleanup', { error: err.message });
    res.status(500).json({
      error: 'Erro ao limpar registros',
      message: err.message
    });
  }
};

exports.stats = (req, res) => {
  logger.info('Consulta de stats', { stats });
  res.json({
    ...stats,
    success_rate: stats.total_requests > 0
      ? ((stats.successful / stats.total_requests) * 100).toFixed(2) + '%'
      : '0%',
    uptime_seconds: process.uptime(),
    memory_usage: process.memoryUsage()
  });
};