'use strict';
const db = require('./connection');
const logger = require('../utils/logger');

/**
 * Mapeamento: índice do array monit -> nome do campo
 */
const MONIT_MAP = {
  sens1: 0, sens2: 1, sens3: 2, sens4: 3,
  sens5: 4, sens6: 5, sens7: 6, sens8: 7,
  selecao_metais: 8,
  filtro_ruido: 9,
  tensao_5v: 10,
  tensao_15v_pos: 11,
  tensao_15v_neg: 12,
  tensao_ac: 13,
  tensao_bateria: 14,
  tensao_fonte: 15,
  anula1: 16, anula2: 17, anula3: 18, anula4: 19,
  anula5: 20, anula6: 21, anula7: 22, anula8: 23,
  cont_entradas: 24,
  cont_saidas: 25,
  cont_bloqueios: 26,
  cont_desbloqueios: 27,
  timestamp_device: 28,
  sinal_rele: 29,
  sinal_trava: 30,
  tempo_pulso_rele: 31,
  tempo_pulso_trava: 32,
  modo_travamento: 33,
  volume_buzzer: 34,
  canal: 35,
  status_pgdm: 36
};

/**
 * Wrapper seguro - só executa se MySQL estiver disponível
 */
async function safeQuery(fn) {
  try {
    if (!db.isEnabled()) return null;
    return await fn();
  } catch (err) {
    logger.warn('MySQL query falhou (não bloqueante)', { error: err.message });
    return null;
  }
}

/**
 * Salvar telemetria completa
 */
async function saveTelemetry(serial, payload, ip) {
  return safeQuery(async () => {
    const monit = payload.monit || [];
    const now = new Date();
    const get = (key) => monit[MONIT_MAP[key]] ?? null;

    await db.query(`
      INSERT INTO devices (serial, primeira_comunicacao, ultima_comunicacao, total_comunicacoes, ip_origem)
      VALUES (?, ?, ?, 1, ?)
      ON DUPLICATE KEY UPDATE 
        ultima_comunicacao = VALUES(ultima_comunicacao),
        total_comunicacoes = total_comunicacoes + 1,
        ip_origem = VALUES(ip_origem)
    `, [serial, now, now, ip]);

    const result = await db.query(`
      INSERT INTO telemetria (
        serial, data_registro,
        sens1, sens2, sens3, sens4, sens5, sens6, sens7, sens8,
        selecao_metais, filtro_ruido,
        tensao_5v, tensao_15v_pos, tensao_15v_neg, tensao_ac, tensao_bateria, tensao_fonte,
        anula1, anula2, anula3, anula4, anula5, anula6, anula7, anula8,
        cont_entradas, cont_saidas, cont_bloqueios, cont_desbloqueios,
        timestamp_device,
        sinal_rele, sinal_trava, tempo_pulso_rele, tempo_pulso_trava,
        modo_travamento, volume_buzzer, canal, status_pgdm
      ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    `, [
      serial, now,
      get('sens1'), get('sens2'), get('sens3'), get('sens4'),
      get('sens5'), get('sens6'), get('sens7'), get('sens8'),
      get('selecao_metais'), get('filtro_ruido'),
      get('tensao_5v'), get('tensao_15v_pos'), get('tensao_15v_neg'),
      get('tensao_ac'), get('tensao_bateria'), get('tensao_fonte'),
      get('anula1'), get('anula2'), get('anula3'), get('anula4'),
      get('anula5'), get('anula6'), get('anula7'), get('anula8'),
      get('cont_entradas'), get('cont_saidas'), get('cont_bloqueios'), get('cont_desbloqueios'),
      get('timestamp_device'),
      get('sinal_rele'), get('sinal_trava'), get('tempo_pulso_rele'), get('tempo_pulso_trava'),
      get('modo_travamento'), get('volume_buzzer'), get('canal'), get('status_pgdm')
    ]);

    if (payload.event?.length >= 3) await saveEvent(serial, payload.event);
    if (payload.audit?.length >= 6) await saveAudit(serial, payload.audit);
    if (payload.erros?.length >= 2) await saveError(serial, payload.erros);

    logger.info('Telemetria salva no MySQL', { serial });
    return result;
  });
}

async function saveEvent(serial, event) {
  const [tipo, dispositivo, ts] = event;
  await db.query(
    'INSERT INTO eventos (serial, data_registro, tipo, dispositivo, timestamp_evento) VALUES (?, NOW(), ?, ?, ?)',
    [serial, tipo, dispositivo, parseInt(ts, 10) || null]
  );
}

async function saveAudit(serial, audit) {
  const [codigo, antigo, novo, operador, dispositivo, ts] = audit;
  await db.query(
    `INSERT INTO auditoria (serial, data_registro, codigo_param, valor_antigo, valor_novo, operador, dispositivo, timestamp_alteracao) 
     VALUES (?, NOW(), ?, ?, ?, ?, ?, ?)`,
    [serial, parseInt(codigo, 10), antigo, novo, operador, dispositivo, parseInt(ts, 10) || null]
  );
}

async function saveError(serial, erros) {
  const [tipo, codigo] = erros;
  await db.query(
    'INSERT INTO erros (serial, data_registro, tipo_erro, codigo_erro) VALUES (?, NOW(), ?, ?)',
    [serial, tipo, codigo]
  );
}

async function getLastTelemetry(serial) {
  return safeQuery(async () => {
    const rows = await db.query(
      'SELECT * FROM telemetria WHERE serial = ? ORDER BY data_registro DESC LIMIT 1',
      [serial]
    );
    return rows[0] || null;
  });
}

async function getActiveDevices() {
  return safeQuery(async () => {
    return db.query(`
      SELECT serial, ultima_comunicacao, total_comunicacoes, ip_origem
      FROM devices 
      WHERE ultima_comunicacao > NOW() - INTERVAL 24 HOUR
      ORDER BY ultima_comunicacao DESC
    `);
  });
}

/**
 * Registrar alteração feita pelo usuário do front-end
 */
async function saveAlteracaoUsuario(data) {
  return safeQuery(async () => {
    const { serial, usuario_id, comando_enviado, ip_origem, user_agent } = data;

    const result = await db.query(`
      INSERT INTO alteracoes_usuario (
        serial, usuario_id, data_solicitacao, status,
        parametros_alterados, comando_enviado, ip_origem, user_agent
      ) VALUES (?, ?, NOW(), 'pendente', '{}', ?, ?, ?)
    `, [
      serial,
      usuario_id,
      JSON.stringify(comando_enviado),
      ip_origem || null,
      user_agent || null
    ]);

    return result.insertId;
  });
}

/**
 * Atualizar status da alteração
 */
async function updateAlteracaoStatus(id, status) {
  return safeQuery(async () => {
    const dataField = status === 'confirmado' ? ', data_confirmacao = NOW()' : '';
    await db.query(
      `UPDATE alteracoes_usuario SET status = ?${dataField} WHERE id = ?`,
      [status, id]
    );
  });
}

module.exports = { 
  saveTelemetry, 
  getLastTelemetry, 
  getActiveDevices,
  saveEvent,
  saveAudit,
  saveError,
  saveAlteracaoUsuario,
  updateAlteracaoStatus
};