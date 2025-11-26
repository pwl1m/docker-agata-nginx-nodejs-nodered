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

    // 1. Validar tamanho mínimo/máximo
    if (bodyLength < 20) {
      logger.warn('Body muito curto', { length: bodyLength, ip: req.ip });
      return res.status(200).json({
        code: 200,
        config: -1,
        error: 'body_too_short',
        ts: new Date().toISOString()
      });
    }

    if (bodyLength > 500000) {
      logger.warn('Body muito grande', { length: bodyLength, ip: req.ip });
      return res.status(200).json({
        code: 200,
        config: -1,
        error: 'body_too_large',
        ts: new Date().toISOString()
      });
    }

    // 2. Detectar payload duplicado (múltiplos seriais)
    const serialMatches = rawBody.match(/\d{6}[A-Za-z0-9+/=]{20,}/g);
    if (serialMatches && serialMatches.length > 1) {
      logger.warn('Payload duplicado detectado', {
        count: serialMatches.length,
        serials: serialMatches.map(m => m.substring(0, 6)),
        ip: req.ip,
        length: bodyLength
      });

      // Extrair apenas o primeiro payload válido
      const firstValid = serialMatches[0];
      const cleanedBody = rawBody.substring(rawBody.indexOf(firstValid));

      logger.info('Payload sanitizado', {
        original_length: bodyLength,
        cleaned_length: cleanedBody.length,
        ip: req.ip
      });

      req.body = Buffer.from(cleanedBody, 'utf8');
      req.sanitized = true;
    }

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

    // 5. Log detalhado para debug (se necessário)
    if (process.env.DEBUG === 'true') {
      logger.debug('Body validado', {
        length: req.body.length,
        sanitized: req.sanitized || false,
        format: startsWithSerial ? 'encrypted' : 'json',
        sample: req.body.toString().substring(0, 80),
        ip: req.ip,
        request_id: req.headers['x-request-id']
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

/**
 * Middleware para sanitizar payloads do Agata
 * Remove duplicatas e lixo do payload
 */
function sanitizePayload(req, res, next) {
  try {
    const rawBody = req.body.raw || req.body;

    // Remover duplicatas
    const serialMatches = rawBody.match(/\d{6}[A-Za-z0-9+/=]{20,}/g);
    if (serialMatches && serialMatches.length > 1) {
      req.body.raw = serialMatches[0]; // Manter apenas o primeiro payload válido
    }

    // Remover lixo do início
    req.body.raw = req.body.raw.replace(/^[^0-9A-Za-z+/=]+/, '');

    next();
  } catch (error) {
    console.error('Erro ao sanitizar payload:', error.message);
    return res.status(400).json({ error: 'Erro ao sanitizar payload' });
  }
}

module.exports = { validateAgataBody, sanitizePayload };