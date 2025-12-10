const logger = require('../utils/logger');

/**
 * validar e sanitizar body raw do Agata
 * Detecta e corrige payloads malformados/duplicados
 */
function validateAgataBody(req, res, next) {
  try {
    const ct = req.headers['content-type'];
    let rawBody;
    if (Buffer.isBuffer(req.body)) rawBody = req.body.toString('utf8');
    else if (typeof req.body === 'string') rawBody = req.body;
    else rawBody = JSON.stringify(req.body || '');

    // Log de diagnóstico: primeiros 200 chars
    const sample = rawBody ? rawBody.substring(0, 200) : '';
    const len = rawBody ? rawBody.length : 0;
    const logger = require('../utils/logger');
    logger.info('BodyValidator: corpo recebido', { contentType: ct, length: len, sample });

    if (!rawBody || len === 0) {
      return res.status(200).json({ code: 200, config: -1, error: 'empty_body' });
    }

    const match = rawBody.match(/(\d{6}[A-Za-z0-9+/=]+)/);
    if (match) {
      req.body = match[1]; // passar como string pura
      return next();
    }

    // Se for JSON, deixa a rota tratar
    const t = rawBody.trim();
    if (t.startsWith('{') || t.startsWith('[')) {
      try { req.body = JSON.parse(t); return next(); } catch {}
    }

    return res.status(200).json({
      code: 200, config: -1, error: 'invalid_format',
      hint: 'esperado: 6 dígitos + base64 ou JSON'
    });
  } catch (error) {
    return res.status(200).json({ code: 200, config: -1, error: 'validation_error' });
  }
}

module.exports = { validateAgataBody };