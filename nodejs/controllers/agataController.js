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
const commandQueue = new Map(); 

function enqueueCommand(serial, comando) {
  const arr = commandQueue.get(serial) || [];
  arr.push({ id: Date.now(), comando, tentativas: 0, ultima: 0 });
  commandQueue.set(serial, arr);
}

// controle da fila
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

// nucleo
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
        // Salvar modelo plano em pasta
        await fileLogger.saveFlatProcessedData(flatPayload);
    } catch (err) {
        logger.error('Falha no parsing do payload', { serial, decryptedPayload, error: err.message });
        await fileLogger.logRawData({ serial, decryptedPayload, error: err.message }, 'parse-error');
        stats.failed_parse++;
        return res.status(400).json({ error: 'Falha no parsing do payload' });
    }

    // Logar os dados processados
    logger.logProcessedData(parsedPayload);
    await fileLogger.saveFlatProcessedData(flatPayload);
    await fileLogger.logTextTransaction(parsedPayload, 'agata');

    stats.successful++;
    latestPayload = { serial, payload: parsedPayload };

    // Auditoria: comando executado
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