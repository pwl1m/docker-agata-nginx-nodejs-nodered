const { Server } = require('socket.io');
const logger = require('./logger');
const redisClient = require('./redisClient');

class WebSocketManager {
    constructor() {
        this.io = null;
        this.initialized = false;
    }

    initialize(httpServer) {
        if (this.initialized) return;

        // Criar servidor Socket.io
        this.io = new Server(httpServer, {
            path: '/ws',
            cors: {
                origin: '*', // MUDAR em produção (especificar domínio do React)
                methods: ['GET', 'POST']
            },
            transports: ['websocket', 'polling'],
            pingTimeout: 60000,
            pingInterval: 25000
        });

        // Conectar ao Redis Pub/Sub
        this.setupRedisSubscription();

        this.io.on('connection', (socket) => {
            const clientId = socket.id;
            const ip = socket.handshake.address;

            logger.info('WebSocket: Cliente conectado', { clientId, ip });

            // Cliente pode se inscrever em devices específicos
            socket.on('subscribe', (data) => {
                const { serial } = data;
                if (serial) {
                    socket.join(`device:${serial}`);
                    logger.info('WebSocket: Cliente inscrito', { clientId, serial });
                }
            });

            socket.on('unsubscribe', (data) => {
                const { serial } = data;
                if (serial) {
                    socket.leave(`device:${serial}`);
                    logger.info('WebSocket: Cliente desinscrito', { clientId, serial });
                }
            });

            socket.on('disconnect', (reason) => {
                logger.info('WebSocket: Cliente desconectado', { clientId, reason });
            });

            socket.on('error', (err) => {
                logger.error('WebSocket: Erro no socket', { clientId, error: err.message });
            });
        });

        this.initialized = true;
        logger.info('WebSocket: Servidor inicializado');
    }

    // Inscrever no Redis Pub/Sub
    async setupRedisSubscription() {
        try {
            await redisClient.subscribe('device_updates', (message) => {
                try {
                    const update = JSON.parse(message);
                    this.broadcast(update);
                } catch (err) {
                    logger.error('WebSocket: Erro ao parsear mensagem Redis', err);
                }
            });

            logger.info('WebSocket: Inscrito no canal Redis "device_updates"');
        } catch (err) {
            logger.error('WebSocket: Falha ao inscrever no Redis', err);
        }
    }

    // Envia atualização para todos
    broadcast(update) {
        if (!this.io) return;
        const { serial } = update || {};
        if (serial) this.io.to(`device:${serial}`).emit('device_update', update);
        this.io.emit('device_update', update);
    }

    // Enviar atualização diretamente (sem Redis)
    emit(event, data) {
        if (!this.initialized) {
            logger.warn('WebSocket: Tentativa de emit antes de inicializar');
            return;
        }
        this.io.emit(event, data);
    }

    // Status
    getStatus() {
        if (!this.io) return { connected: 0 };

        const sockets = this.io.sockets.sockets;
        return {
            connected: sockets.size,
            clients: Array.from(sockets.keys())
        };
    }
}

// Singleton
module.exports = new WebSocketManager();