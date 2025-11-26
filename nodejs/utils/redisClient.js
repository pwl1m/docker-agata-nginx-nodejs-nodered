const redis = require('redis');
const logger = require('./logger');

class RedisClient {
  constructor() {
    this.client = null;
    this.publisher = null;
    this.subscriber = null;
    this.connected = false;
  }

  async connect() {
    if (this.connected) return;
    const cfg = {
      socket: {
        host: process.env.REDIS_HOST || 'redis',
        port: parseInt(process.env.REDIS_PORT || '6379', 10),
        reconnectStrategy: (retries) => retries > 10 ? new Error('Redis fail') : Math.min(retries * 200, 3000)
      }
    };
    try {
      this.client = redis.createClient(cfg);
      this.client.on('error', e => logger.error('Redis client error', { msg: e.message }));
      await this.client.connect();

      this.publisher = redis.createClient(cfg);
      this.publisher.on('error', e => logger.error('Redis publisher error', { msg: e.message }));
      await this.publisher.connect();

      this.subscriber = redis.createClient(cfg);
      this.subscriber.on('error', e => logger.error('Redis subscriber error', { msg: e.message }));
      await this.subscriber.connect();

      this.connected = true;
      logger.info('Redis conectado');
    } catch (e) {
      logger.error('Redis conexão falhou', { msg: e.message });
      throw e;
    }
  }

  async get(key) {
    if (!this.connected) return null;
    try { return await this.client.get(key); }
    catch (e) { logger.error('Redis GET falhou', { key, msg: e.message }); return null; }
  }

  async setEx(key, seconds, value) {
    if (!this.connected) return false;
    try { await this.client.setEx(key, seconds, value); return true; }
    catch (e) { logger.error('Redis SETEX falhou', { key, msg: e.message }); return false; }
  }

  async publish(channel, message) {
    if (!this.connected) return false;
    try { await this.publisher.publish(channel, message); return true; }
    catch (e) { logger.error('Redis PUBLISH falhou', { channel, msg: e.message }); return false; }
  }

  async subscribe(channel, cb) {
    if (!this.connected) return;
    try {
      await this.subscriber.subscribe(channel, cb);
      logger.info('Redis inscrito', { channel });
    } catch (e) {
      logger.error('Redis SUBSCRIBE falhou', { channel, msg: e.message });
    }
  }

  async ping() {
    if (!this.connected) return false;
    try { return (await this.client.ping()) === 'PONG'; }
    catch { return false; }
  }

  async disconnect() {
    if (!this.connected) return;
    try {
      await this.client.quit();
      await this.publisher.quit();
      await this.subscriber.quit();
      this.connected = false;
      logger.info('Redis desconectado');
    } catch (e) {
      logger.error('Redis disconnect erro', { msg: e.message });
    }
  }

  async set(key, value) {
    try {
      if (!this.client) throw new Error('Redis não conectado');
      await this.client.set(key, value);
      return true;
    } catch (e) {
      logger.error('Redis SET falhou', { key, error: e.message });
      return false;
    }
  }
}

module.exports = new RedisClient();