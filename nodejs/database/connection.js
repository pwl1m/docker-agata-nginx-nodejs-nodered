'use strict';
const logger = require('../utils/logger');

let pool = null;
let mysqlEnabled = false;

async function getPool() {
  if (pool) return pool;

  // Só tenta conectar se as variáveis de ambiente existirem
  if (!process.env.MYSQL_HOST) {
    logger.info('MySQL não configurado (MYSQL_HOST ausente) - modo offline');
    return null;
  }

  try {
    const mysql = require('mysql2/promise');
    
    pool = mysql.createPool({
      host: process.env.MYSQL_HOST,
      port: parseInt(process.env.MYSQL_PORT || '3306', 10),
      user: process.env.MYSQL_USER || 'root',
      password: process.env.MYSQL_PASSWORD || '',
      database: process.env.MYSQL_DATABASE || 'agata',
      waitForConnections: true,
      connectionLimit: 10,
      queueLimit: 0
    });

    const conn = await pool.getConnection();
    conn.release();
    mysqlEnabled = true;
    logger.info('MySQL conectado');
  } catch (err) {
    logger.warn('MySQL indisponível - continuando sem banco', { error: err.message });
    pool = null;
  }

  return pool;
}

async function query(sql, params = []) {
  const p = await getPool();
  if (!p) return { insertId: null, affectedRows: 0 };
  
  const [rows] = await p.execute(sql, params);
  return rows;
}

function isEnabled() {
  return mysqlEnabled;
}

async function close() {
  if (pool) {
    await pool.end();
    pool = null;
    mysqlEnabled = false;
    logger.info('MySQL desconectado');
  }
}

module.exports = { getPool, query, close, isEnabled };