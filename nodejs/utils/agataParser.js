function toInt(x) {
  if (x === null || x === undefined || x === '') return null;
  const n = parseInt(x, 10);
  return Number.isFinite(n) ? n : null;
}

function mysqlNow() { return new Date().toISOString().replace('T', ' ').substring(0, 19); }

const REQUIRED_SERIAL_REGEX = /^\d{6}$/;

// helper para marcar faltantes
function finalize(record) {
  const faltantes = [];
  for (const [k, v] of Object.entries(record)) {
    if (v === null) faltantes.push(k);
  }
  record._faltantes = faltantes;
  record._has_missing = faltantes.length > 0;
  // timestamp de ingestão como metadado, sem alterar campos de domínio
  record._ingest_at = mysqlNow();
  return record;
}

function isLegacy(obj) {
  return obj && typeof obj === 'object' && Array.isArray(obj.monit) && obj.blc === '#ea';
}

function processLegacyAgataData(legacyData, ip) {
  const m = legacyData.monit || [];
  const get = (i) => toInt(m[i]);
  const rawSerial = legacyData.srl;
  if (!REQUIRED_SERIAL_REGEX.test(rawSerial || '')) {
    throw new Error(`Serial vazio ou inválido (legacy): ${rawSerial}`);
  }

  const rec = {
    id: legacyData.id ? String(legacyData.id) : null,
    // não inventar data_registro se o legado não envia
    data_registro: legacyData.data_registro ?? null,
    sensibilidade1: get(0), sensibilidade2: get(1), sensibilidade3: get(2), sensibilidade4: get(3),
    sensibilidade5: get(4), sensibilidade6: get(5), sensibilidade7: get(6), sensibilidade8: get(7),
    metais: get(8), ruidos: get(9),
    tensaocinco: get(10), tensao_quinze: get(11), tensao_menos_quinze: get(12), tensao_rede: get(13),
    tensao_bateria1: get(14), tensao_bateria2: get(15),
    anula1: get(16), anula2: get(17), anula3: get(18), anula4: get(19),
    anula5: get(20), anula6: get(21), anula7: get(22), anula8: get(23),
    cont_entrada1: get(24), cont_entrada2: null, cont_entrada3: null, cont_entrada4: null,
    cont_saida1: get(25), cont_saida2: null, cont_saida3: null, cont_saida4: null,
    cont_bloqueio1: get(26), cont_bloqueio2: null, cont_bloqueio3: null, cont_bloqueio4: null,
    cont_des_bloqueio1: get(27), cont_des_bloqueio2: null, cont_des_bloqueio3: null, cont_des_bloqueio4: null,
    cal_dia: null, cal_minuto: null, cal_ano1: null, cal_ano2: null,
    sinal_rele: get(29), sinal_trava: get(30), sinal_pulso_rele: get(31), sinal_pulso_trava: get(32),
    modo_travamento: get(33), volume_buzzer: get(34), volume_voz: get(35), canal: get(36),
    serial: rawSerial,
    id_sincronizador: null,
    // manter tipo original se vier; se não, null
    aberto: (m[37] !== undefined) ? m[37] : null,
    // não assumir ok=true no legado
    ok: legacyData.ok ?? null,
    _source_ip: ip,
    _source: 'legacy'
  };
  return finalize(rec);
}

function coerceFlat(obj, ip) {
  const rawSerial = obj.serial;
  if (!REQUIRED_SERIAL_REGEX.test(rawSerial || '')) {
    throw new Error(`Serial vazio ou inválido (flat): ${rawSerial}`);
  }

  const rec = {
    id: obj.id ? String(obj.id) : null,
    // não inventar data_registro; se precisar, use _ingest_at
    data_registro: obj.data_registro ?? null,
    sensibilidade1: toInt(obj.sensibilidade1), sensibilidade2: toInt(obj.sensibilidade2),
    sensibilidade3: toInt(obj.sensibilidade3), sensibilidade4: toInt(obj.sensibilidade4),
    sensibilidade5: toInt(obj.sensibilidade5), sensibilidade6: toInt(obj.sensibilidade6),
    sensibilidade7: toInt(obj.sensibilidade7), sensibilidade8: toInt(obj.sensibilidade8),
    metais: toInt(obj.metais), ruidos: toInt(obj.ruidos),
    tensaocinco: toInt(obj.tensaocinco), tensao_quinze: toInt(obj.tensao_quinze),
    tensao_menos_quinze: toInt(obj.tensao_menos_quinze), tensao_rede: toInt(obj.tensao_rede),
    tensao_bateria1: toInt(obj.tensao_bateria1), tensao_bateria2: toInt(obj.tensao_bateria2),
    anula1: toInt(obj.anula1), anula2: toInt(obj.anula2), anula3: toInt(obj.anula3), anula4: toInt(obj.anula4),
    anula5: toInt(obj.anula5), anula6: toInt(obj.anula6), anula7: toInt(obj.anula7), anula8: toInt(obj.anula8),
    cont_entrada1: toInt(obj.cont_entrada1), cont_entrada2: toInt(obj.cont_entrada2),
    cont_entrada3: toInt(obj.cont_entrada3), cont_entrada4: toInt(obj.cont_entrada4),
    cont_saida1: toInt(obj.cont_saida1), cont_saida2: toInt(obj.cont_saida2),
    cont_saida3: toInt(obj.cont_saida3), cont_saida4: toInt(obj.cont_saida4),
    cont_bloqueio1: toInt(obj.cont_bloqueio1), cont_bloqueio2: toInt(obj.cont_bloqueio2),
    cont_bloqueio3: toInt(obj.cont_bloqueio3), cont_bloqueio4: toInt(obj.cont_bloqueio4),
    cont_des_bloqueio1: toInt(obj.cont_des_bloqueio1), cont_des_bloqueio2: toInt(obj.cont_des_bloqueio2),
    cont_des_bloqueio3: toInt(obj.cont_des_bloqueio3), cont_des_bloqueio4: toInt(obj.cont_des_bloqueio4),
    cal_dia: obj.cal_dia ?? null, cal_minuto: obj.cal_minuto ?? null,
    cal_ano1: obj.cal_ano1 ?? null, cal_ano2: obj.cal_ano2 ?? null,
    sinal_rele: toInt(obj.sinal_rele), sinal_trava: toInt(obj.sinal_trava),
    sinal_pulso_rele: toInt(obj.sinal_pulso_rele), sinal_pulso_trava: toInt(obj.sinal_pulso_trava),
    modo_travamento: toInt(obj.modo_travamento), volume_buzzer: toInt(obj.volume_buzzer),
    volume_voz: toInt(obj.volume_voz), canal: toInt(obj.canal),
    serial: rawSerial,
    id_sincronizador: obj.id_sincronizador ?? null,
    // manter como veio se existir; senão, null
    aberto: (obj.aberto !== undefined) ? obj.aberto : null,
    // não forçar boolean
    ok: (obj.ok !== undefined) ? obj.ok : null,
    _source_ip: ip,
    _source: 'flat'
  };
  return finalize(rec);
}

function normalizeToFlat(input, ip) {
  if (input === null || input === undefined) {
    throw new Error('Input nulo ou indefinido');
  }
  if (Array.isArray(input)) {
    return input.map(x => {
      if (isLegacy(x)) return processLegacyAgataData(x, ip);
      if (typeof x === 'object') return coerceFlat(x, ip);
      throw new Error('Item do array inválido');
    });
  }
  if (isLegacy(input)) return [processLegacyAgataData(input, ip)];
  if (typeof input === 'object') return [coerceFlat(input, ip)];
  throw new Error(`Formato não suportado: ${typeof input}`);
}

module.exports = { normalizeToFlat, processLegacyAgataData };