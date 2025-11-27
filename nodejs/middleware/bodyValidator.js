const logger = require('../utils/logger');

/**
 * Middleware para validar e sanitizar body raw do Agata
 * Detecta e corrige payloads malformados/duplicados
 */
function validateAgataBody(req, res, next) {
  try {
    if (!req.body || req.body.length === 0) {
      logger.warn('Body vazio recebido', { ip: req.ip, headers: req.headers });
      return res.status(200).json({
        code: 200,
        config: -1,
        error: 'empty_body',
        ts: new Date().toISOString()
      });
    }

    const rawBody = Buffer.isBuffer(req.body) ? req.body.toString('utf8') : String(req.body);
    const bodyLength = rawBody.length;

    // 3. Detectar lixo no início (headers HTTP, chunks, etc)
    const garbagePattern = /^[^0-9A-Za-z+/=]{1,50}/;
    const garbageMatch = rawBody.match(garbagePattern);

    if (garbageMatch) {
      logger.warn('Lixo detectado no início do payload', {
        garbage: garbageMatch[0],
        garbage_length: garbageMatch[0].length,
        ip: req.ip
      });

      // Remover lixo do início
      const cleanedBody = rawBody.replace(garbagePattern, '');

      logger.info('Lixo removido do payload', {
        original_length: bodyLength,
        cleaned_length: cleanedBody.length,
        ip: req.ip
      });

      req.body = Buffer.from(cleanedBody, 'utf8');
      req.sanitized = true;
    }

    // 4. Validar formato: deve começar com 6 dígitos ou ser JSON
    const startsWithSerial = /^\d{6}/.test(rawBody);
    const isJSON = rawBody.trim().startsWith('{') || rawBody.trim().startsWith('[');

    if (!startsWithSerial && !isJSON) {
      logger.error('Formato inválido', {
        sample: rawBody.substring(0, 100),
        length: bodyLength,
        ip: req.ip
      });

      return res.status(200).json({
        code: 200,
        config: -1,
        error: 'invalid_format',
        hint: 'esperado: 6 dígitos + base64 ou JSON',
        ts: new Date().toISOString()
      });
    }
    
    next();

  } catch (error) {
    logger.error('Erro no middleware de validação', {
      error: error.message,
      stack: error.stack,
      ip: req.ip
    });

    return res.status(200).json({
      code: 200,
      config: -1,
      error: 'validation_error',
      ts: new Date().toISOString()
    });
  }
}

module.exports = { validateAgataBody };