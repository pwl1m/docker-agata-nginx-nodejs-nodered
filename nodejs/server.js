'use strict';
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const path = require('path');
const logger = require('./utils/logger');
const agataRoutes = require('./routes/agata');
const websocketManager = require('./utils/websocketManager');
const redisClient = require('./utils/redisClient');

const app = express();
const PORT = process.env.PORT || 3000;

// Servidor HTTP + inicialização WS depois do Redis
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
app.use(helmet({
  contentSecurityPolicy: false // Desativar CSP para teste local (scripts inline)
}));
app.use(cors());
app.use(morgan('combined'));
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));

app.use((req, res, next) => {
    if (req.headers['content-type'] === 'text/html') {
        let data = '';
        req.on('data', chunk => {
            data += chunk;
        });
        req.on('end', () => {
            console.log('Corpo bruto recebido:', data);
            // Tenta processar o corpo como JSON ou salva como texto
            try {
                req.body = JSON.parse(data);
            } catch (err) {
                req.body = { raw: data }; // Salva o corpo bruto como texto
            }
            next();
        });
    } else {
        next();
    }
});

// Rotas
app.use('/', agataRoutes);

app.get('/test', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'test-websocket.html'));
});

// Health
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'OK',
    ws_clients: websocketManager.getStatus().connected, // Mostrar status WS
    timestamp: new Date().toISOString()
  });
});

// 404
app.use((req, res) => res.status(404).json({ error: 'Not found' }));

// Handler de erro
app.use((err, req, res, next) => {
  logger.error('Unhandled error', { err: err.message });
  res.status(500).json({ error: 'Internal error' });
});

server.listen(PORT, '0.0.0.0', () => {
  logger.info(`🚀 Servidor rodando na porta ${PORT}`);
  logger.info(`📡 Agata: POST http://localhost:${PORT}/agata`);
  logger.info(`🔌 WebSocket: ws://localhost:${PORT}/ws`);
  logger.info(`🧪 Teste UI: http://localhost:${PORT}/test`);
});

// Graceful shutdown
const shutdown = async (signal) => {
  logger.info(`Recebido sinal ${signal}, desligando...`);
  try { await redisClient.disconnect(); } catch {}
  server.close(() => {
    logger.info('HTTP server encerrado');
    process.exit(0);
  });
  // Force exit se não fechar em 5s
  setTimeout(() => process.exit(1), 5000).unref();
};
['SIGINT','SIGTERM'].forEach(sig => process.on(sig, () => shutdown(sig)));