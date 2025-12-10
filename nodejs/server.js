'use strict';
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const path = require('path');
const logger = require('./utils/logger');
const websocketManager = require('./utils/websocketManager');
const redisClient = require('./utils/redisClient');

const app = express();
const PORT = process.env.PORT || 3000;

// Servidor HTTP + inicialização WebScoket depois do Redis
const server = require('http').createServer(app);

redisClient.connect()
  .then(() => {
    logger.info('Redis conectado, inicializando WebSocket...');
    websocketManager.initialize(server);
  })
  .catch(err => {
    logger.error('Falha ao conectar Redis', { error: err.message });
  });

app.set('trust proxy', true);

app.use(cors());

app.use(morgan('combined'));

// ✅ LOG ABSOLUTO - antes de qualquer middleware
app.use((req, res, next) => {
  logger.info('🚨 REQUISIÇÃO RECEBIDA', {
    method: req.method,
    path: req.path,
    url: req.url,
    contentType: req.headers['content-type']
  });
  next();
});

// ✅ Middleware condicional: RAW para /agata, JSON para o resto
app.use((req, res, next) => {
  if (req.method === 'POST' && /^\/agata\/?$/.test(req.path)) {
    logger.info('📥 Iniciando leitura RAW do body');
    // RAW para a rota do device
    let data = '';
    req.setEncoding('utf8');
    
    req.on('data', chunk => {
      data += chunk;
      logger.info('📦 Chunk recebido', { size: chunk.length, chunk: chunk.substring(0, 50) });
    });
    
    req.on('end', () => {
      req.rawBody = data;
      req.body = data; // ✅ Também colocar em req.body para compatibilidade
      logger.info('✅ Body completo recebido', { 
        length: data.length, 
        preview: data.substring(0, 100),
        hasRawBody: !!req.rawBody,
        hasBody: !!req.body
      });
      next();
    });
    
    req.on('error', err => {
      logger.error('❌ Erro ao ler corpo', { error: err.message });
      if (!res.headersSent) {
        res.status(400).json({ error: 'Bad request' });
      }
    });
  } else {
    // JSON para todas as outras rotas
    express.json({ limit: '10mb' })(req, res, next);
  }
});

// ✅ ROTAS DE COMANDO - agora sem conflito
const agataRouter = require('./routes/agata');
app.use('/', agataRouter);

app.get('/test', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'test-websocket.html'));
});

// Health
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'OK',
    ws_clients: websocketManager.getStatus().connected,
    timestamp: new Date().toISOString()
  });
});

// 404
app.use((req, res) => res.status(404).json({ error: 'Not found' }));

// Handler de erro
app.use((err, req, res, next) => {
  logger.error('Erro não capturado', { err: err.message });
  res.status(500).json({ error: 'Internal error' });
});

server.listen(PORT, '0.0.0.0', () => {
  logger.info(`Servidor rodando na porta ${PORT}`);
  logger.info(`Agata: POST http://localhost:${PORT}/agata`);
  logger.info(`WebSocket: ws://localhost:${PORT}/ws`);
});

// Garante que as conexões sejam fechadas de forma segura
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