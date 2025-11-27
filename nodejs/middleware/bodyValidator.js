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

    let rawBody = Buffer.isBuffer(req.body) ? req.body.toString('utf8') : String(req.body);
    const originalLength = rawBody.length;

    // 1. Detectar e extrair payload válido (6 dígitos + base64)
    const validPayloadPattern = /(\d{6}[A-Za-z0-9+/=]+)/;
    const match = rawBody.match(validPayloadPattern);

    if (match) {
      const cleanedBody = match[1];
      
      if (cleanedBody.length !== originalLength) {
        logger.warn('Payload duplicado/corrompido detectado e limpo', {
          original_length: originalLength,
          cleaned_length: cleanedBody.length,
          removed: originalLength - cleanedBody.length,
          ip: req.ip
        });
        
        rawBody = cleanedBody;
        req.body = Buffer.from(cleanedBody, 'utf8');
        req.sanitized = true;
      }
    }

    // 2. Validar formato: deve começar com 6 dígitos ou ser JSON
    const startsWithSerial = /^\d{6}/.test(rawBody);
    const isJSON = rawBody.trim().startsWith('{') || rawBody.trim().startsWith('[');

    if (!startsWithSerial && !isJSON) {
      logger.error('Formato inválido após limpeza', {
        sample: rawBody.substring(0, 100),
        length: rawBody.length,
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