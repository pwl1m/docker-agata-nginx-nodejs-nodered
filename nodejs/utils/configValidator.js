'use strict';

/**
 * Schema de validação baseado no firmware Ágata
 * Ordem obrigatória dos 29 valores no array final
 */
const CONFIG_SCHEMA = {
  sensibilidade: { 
    min: 0, 
    max: 99, 
    length: 8,
    type: 'array',
    description: 'Sensibilidade das 8 áreas'
  },
  anulaAreas: { 
    min: 0, 
    max: 1, 
    length: 8,
    type: 'array',
    description: 'Anular áreas (0=não, 1=sim)'
  },
  canal: { 
    min: 1, 
    max: 25,
    type: 'number',
    description: 'Canal de comunicação'
  },
  filtroRuido: { 
    min: 0, 
    max: 99,
    type: 'number',
    description: 'Filtro de ruído'
  },
  sinalRele: { 
    min: 0, 
    max: 2,
    type: 'number',
    description: 'Sinal relé (0=pulso, 1=retenção, 2=desligado)'
  },
  pulsoRele: { 
    min: 1, 
    max: 99,
    type: 'number',
    description: 'Duração pulso relé (x10ms)'
  },
  sinalTrava: { 
    min: 0, 
    max: 3,
    type: 'number',
    description: 'Sinal trava (0=pulso, 1=retenção, 2=desligado, 3=inverso)'
  },
  pulsoTrava: { 
    min: 1, 
    max: 99,
    type: 'number',
    description: 'Duração pulso trava (x10ms)'
  },
  modoTravamento: { 
    min: 0, 
    max: 1,
    type: 'number',
    description: 'Modo travamento (0=automático, 1=manual)'
  },
  selecaoMetais: { 
    min: 0, 
    max: 99,
    type: 'number',
    description: 'Seleção de metais'
  },
  volumeVoz: { 
    min: 0, 
    max: 10,
    type: 'number',
    description: 'Volume da voz'
  },
  volumeBuzzer: { 
    min: 0, 
    max: 10,
    type: 'number',
    description: 'Volume do buzzer'
  },
  tomBuzzer: { 
    min: 0, 
    max: 10,
    type: 'number',
    description: 'Tom do buzzer'
  }
};

/**
 * Configuração padrão (valores seguros)
 */
const DEFAULT_CONFIG = {
  sensibilidade: [50, 50, 50, 50, 50, 50, 50, 50],
  anulaAreas: [0, 0, 0, 0, 0, 0, 0, 0],
  canal: 10,
  filtroRuido: 15,
  sinalRele: 1,
  pulsoRele: 10,
  sinalTrava: 1,
  pulsoTrava: 10,
  modoTravamento: 1,
  selecaoMetais: 50,
  volumeVoz: 5,
  volumeBuzzer: 5,
  tomBuzzer: 5
};

/**
 * Valida um campo individual
 * @param {string} fieldName - Nome do campo
 * @param {any} value - Valor a validar
 * @returns {object} { valid: boolean, error?: string }
 */
function validateField(fieldName, value) {
  const rules = CONFIG_SCHEMA[fieldName];
  
  if (!rules) {
    return { valid: false, error: `Campo desconhecido: ${fieldName}` };
  }

  // Validar tipo array
  if (rules.type === 'array') {
    if (!Array.isArray(value)) {
      return { 
        valid: false, 
        error: `${fieldName} deve ser um array` 
      };
    }

    if (value.length !== rules.length) {
      return { 
        valid: false, 
        error: `${fieldName} deve ter exatamente ${rules.length} valores` 
      };
    }

    // Validar cada valor do array
    for (let i = 0; i < value.length; i++) {
      const val = value[i];
      if (typeof val !== 'number' || val < rules.min || val > rules.max) {
        return { 
          valid: false, 
          error: `${fieldName}[${i}] deve estar entre ${rules.min} e ${rules.max}, recebido: ${val}` 
        };
      }
    }

    return { valid: true };
  }

  // Validar tipo number
  if (rules.type === 'number') {
    if (typeof value !== 'number') {
      return { 
        valid: false, 
        error: `${fieldName} deve ser um número` 
      };
    }

    if (value < rules.min || value > rules.max) {
      return { 
        valid: false, 
        error: `${fieldName} deve estar entre ${rules.min} e ${rules.max}, recebido: ${value}` 
      };
    }

    return { valid: true };
  }

  return { valid: false, error: `Tipo inválido para ${fieldName}` };
}

/**
 * Valida configuração completa
 * @param {object} config - Objeto com campos de configuração
 * @returns {object} { valid: boolean, errors?: string[] }
 */
function validateConfig(config) {
  const errors = [];

  // Verificar se todos os campos obrigatórios estão presentes
  for (const fieldName of Object.keys(CONFIG_SCHEMA)) {
    if (!(fieldName in config)) {
      errors.push(`Campo obrigatório ausente: ${fieldName}`);
      continue;
    }

    const result = validateField(fieldName, config[fieldName]);
    if (!result.valid) {
      errors.push(result.error);
    }
  }

  return {
    valid: errors.length === 0,
    errors: errors.length > 0 ? errors : undefined
  };
}

/**
 * Monta array de 29 valores na ordem correta para o firmware
 * @param {object} config - Objeto com campos validados
 * @param {number} userId - ID do usuário (opcional, padrão 1)
 * @returns {number[]} Array com 29 valores
 */
function buildConfigArray(config, userId = 1) {
  const timestamp = Math.floor(Date.now() / 1000); // Unix timestamp

  const array = [
    ...config.sensibilidade,     // [0-7]   → 8 valores
    ...config.anulaAreas,         // [8-15]  → 8 valores
    config.canal,                 // [16]    → 1 valor
    config.filtroRuido,           // [17]    → 1 valor
    config.sinalRele,             // [18]    → 1 valor
    config.pulsoRele,             // [19]    → 1 valor
    config.sinalTrava,            // [20]    → 1 valor
    config.pulsoTrava,            // [21]    → 1 valor
    config.modoTravamento,        // [22]    → 1 valor
    config.selecaoMetais,         // [23]    → 1 valor
    config.volumeVoz,             // [24]    → 1 valor
    config.volumeBuzzer,          // [25]    → 1 valor
    config.tomBuzzer,             // [26]    → 1 valor
    timestamp,                    // [27]    → gerado automaticamente
    userId                        // [28]    → passado ou default 1
  ];

  return array;
}

/**
 * Retorna configuração padrão
 * @returns {object} Objeto com valores padrão seguros
 */
function getDefaultConfig() {
  return { ...DEFAULT_CONFIG };
}

/**
 * Retorna o schema de validação (útil para documentação)
 * @returns {object} Schema completo
 */
function getSchema() {
  return { ...CONFIG_SCHEMA };
}

module.exports = {
  validateConfig,
  validateField,
  buildConfigArray,
  getDefaultConfig,
  getSchema,
  CONFIG_SCHEMA,
  DEFAULT_CONFIG
};