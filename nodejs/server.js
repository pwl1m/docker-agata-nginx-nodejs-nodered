'use strict';
const express = require('express');
const cors = require('cors');
const morgan = require('morgan');
const path = require('path');
const fs = require('fs');
const logger = require('./utils/logger');
const websocketManager = require('./utils/websocketManager');
const redisClient = require('./utils/redisClient');

const app = express();
const PORT = process.env.PORT || 3000;
const server = require('http').createServer(app);

// CONFIGURAÇÃO DO MODO DEBUG
const DEBUG_RAW_PAYLOAD = process.env.DEBUG_RAW_PAYLOAD === 'true' || true;
const RAW_INCOMING_DIR = path.join(__dirname, 'logs', 'raw-incoming');

if (DEBUG_RAW_PAYLOAD) {
  if (!fs.existsSync(RAW_INCOMING_DIR)) {
    fs.mkdirSync(RAW_INCOMING_DIR, { recursive: true });
  }
  console.log('═══════════════════════════════════════════════════════════');
  console.log('🔍 MODO DEBUG ATIVO: Salvando payloads brutos em:', RAW_INCOMING_DIR);
  console.log('═══════════════════════════════════════════════════════════');
}

// FUNÇÃO: Salvar payload bruto
function saveRawIncoming(req, rawBody) {
  if (!DEBUG_RAW_PAYLOAD) return;

  try {
    const timestamp = new Date().toISOString();
    const dateStr = timestamp.split('T')[0];
    
    const debugData = {
      _debug_timestamp: timestamp,
      _debug_method: req.method,
      _debug_path: req.path,
      _debug_ip: req.ip || req.headers['x-real-ip'] || req.connection?.remoteAddress || 'unknown',
      _debug_content_type: req.headers['content-type'] || 'não informado',
      _debug_content_length: req.headers['content-length'] || rawBody?.length || 0,
      _debug_user_agent: req.headers['user-agent'] || 'não informado',
      _debug_headers: req.headers,
      _debug_body_raw: rawBody,
      _debug_body_length: rawBody?.length || 0,
      _debug_body_preview_100: rawBody?.substring?.(0, 100) || '',
      _debug_possible_serial: rawBody?.substring?.(0, 6) || 'N/A',
      _debug_serial_is_numeric: /^\d{6}$/.test(rawBody?.substring?.(0, 6) || ''),
    };

    const filename = `raw-incoming-${dateStr}.log`;
    const filepath = path.join(RAW_INCOMING_DIR, filename);
    const logLine = JSON.stringify(debugData, null, 2) + '\n\n---END-OF-REQUEST---\n\n';
    
    fs.appendFileSync(filepath, logLine);
    
    console.log('═══════════════════════════════════════════════════════════');
    console.log(`🔍 [DEBUG RAW] ${timestamp}`);
    console.log(`   Method: ${req.method} | Path: ${req.path}`);
    console.log(`   IP: ${debugData._debug_ip}`);
    console.log(`   Body Length: ${debugData._debug_body_length}`);
    console.log(`   Serial?: ${debugData._debug_possible_serial} (numeric: ${debugData._debug_serial_is_numeric})`);
    console.log(`   Preview: ${debugData._debug_body_preview_100}...`);
    console.log('═══════════════════════════════════════════════════════════');

  } catch (err) {
    console.error('❌ Erro ao salvar debug raw:', err.message);
  }
}

// ESTADO COMPARTILHADO
const pendingCommands = new Map();
const recentPayloads = new Map();

// CONEXÃO REDIS + WEBSOCKET
redisClient.connect()
  .then(() => {
    logger.info('Redis conectado, inicializando WebSocket...');
    websocketManager.initialize(server);
  })
  .catch(err => {
    logger.error('Falha ao conectar Redis', { error: err.message });
  });

// MIDDLEWARES BÁSICOS - São padrão da propria arquitetura express 
app.set('trust proxy', true);
app.use(cors());
app.use(morgan('combined'));

app.use((req, res, next) => {
  logger.info('🚨 REQUISIÇÃO RECEBIDA', {
    method: req.method,
    path: req.path,
    url: req.url,
    contentType: req.headers['content-type']
  });
  next();
});

app.use((req, res, next) => {
  // APENAS /agata ou /agata/ (telemetria) usa raw body
  // Outras rotas como /agata/send-command usam JSON normal
  if (req.method === 'POST' && /^\/agata\/?$/.test(req.path)) {
    let data = '';
    req.setEncoding('utf8');
    req.on('data', chunk => data += chunk);
    req.on('end', () => {
      req.rawBody = data;
      req.body = data;
      saveRawIncoming(req, data);
      logger.info('📦 Body recebido (RAW)', {
        length: data.length,
        contentType: req.headers['content-type']
      });
      next();
    });
    req.on('error', err => {
      logger.error('❌ Erro ao ler corpo', { error: err.message });
      saveRawIncoming(req, `[ERROR] ${err.message}`);
      if (!res.headersSent) {
        res.status(200).json({ code: 400, config: 0, data: "" });
      }
    });
  } else {
    // Todas as outras rotas usam JSON parser normal
    express.json({ limit: '10mb' })(req, res, next);
  }
});

// EXPOR ESTADO COMPARTILHADO PARA ROTAS
app.set('pendingCommands', pendingCommands);
app.set('recentPayloads', recentPayloads);

// ROTAS
const agataRouter = require('./routes/agata');
app.use('/', agataRouter);

// ROTA DE DEBUG - RAW INCOMING
app.get('/debug/raw-incoming', (req, res) => {
  if (!DEBUG_RAW_PAYLOAD) {
    return res.status(404).json({ error: 'Debug mode disabled' });
  }
  
  try {
    const files = fs.readdirSync(RAW_INCOMING_DIR).filter(f => f.endsWith('.log')).sort().reverse();
    
    if (files.length === 0) {
      return res.json({ message: 'Nenhum log encontrado', files: [] });
    }
    
    const latestFile = files[0];
    const latestPath = path.join(RAW_INCOMING_DIR, latestFile);
    const content = fs.readFileSync(latestPath, 'utf8');
    const entries = content.split('---END-OF-REQUEST---').filter(e => e.trim());
    
    res.json({
      debug_enabled: true,
      log_directory: RAW_INCOMING_DIR,
      files: files.slice(0, 10),
      latest_file: latestFile,
      total_entries_today: entries.length,
      last_5_entries: entries.slice(-5).map(e => {
        try { return JSON.parse(e.trim()); } 
        catch { return { raw: e.substring(0, 200) }; }
      })
    });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'OK',
    debug_mode: DEBUG_RAW_PAYLOAD,
    ws_clients: websocketManager.getStatus().connected,
    pending_commands: pendingCommands.size,
    timestamp: new Date().toISOString()
  });
});

app.get('/debug/state', (req, res) => {
  res.json({
    pending_commands: pendingCommands.size,
    recent_payloads: recentPayloads.size
  });
});

// 404
app.use((req, res) => res.status(404).json({ error: 'Not found' }));

// Handler de erro
app.use((err, req, res, next) => {
  logger.error('Erro não capturado', { err: err.message, stack: err.stack, path: req.path });
  res.status(200).json({ code: 200, config: 0, data: "" });
});

// INICIAR SERVER
server.listen(PORT, '0.0.0.0', () => {
  logger.info(`Servidor rodando na porta ${PORT}`);
  logger.info(`Agata: POST http://localhost:${PORT}/agata`);
  logger.info(`WebSocket: ws://localhost:${PORT}/ws`);
  if (DEBUG_RAW_PAYLOAD) {
    logger.info(`🔍 Debug Raw: GET http://localhost:${PORT}/debug/raw-incoming`);
  }
});

const shutdown = async (signal) => {
  logger.info(`Recebido sinal ${signal}, desligando...`);
  try { await redisClient.disconnect(); } catch {}
  server.close(() => {
    logger.info('HTTP server encerrado');
    process.exit(0);
  });
  setTimeout(() => process.exit(1), 5000).unref();
};
['SIGINT','SIGTERM'].forEach(sig => process.on(sig, () => shutdown(sig)));