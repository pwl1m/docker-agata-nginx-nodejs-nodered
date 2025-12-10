const validator = require('./utils/configValidator');

// Teste 1: Config válida
console.log('\n=== TESTE 1: Config Válida ===');
const configValida = validator.getDefaultConfig();
const result1 = validator.validateConfig(configValida);
console.log('Validação:', result1);

const array1 = validator.buildConfigArray(configValida, 1);
console.log('Array gerado:', array1);
console.log('Tamanho:', array1.length, '(esperado: 29)');

// Teste 2: Config inválida (canal fora do range)
console.log('\n=== TESTE 2: Canal Inválido ===');
const configInvalida = {
  ...configValida,
  canal: 99 // Máximo é 25
};
const result2 = validator.validateConfig(configInvalida);
console.log('Validação:', result2);

// Teste 3: Config incompleta
console.log('\n=== TESTE 3: Config Incompleta ===');
const configIncompleta = {
  sensibilidade: [50, 50, 50, 50, 50, 50, 50, 50]
  // Faltam campos
};
const result3 = validator.validateConfig(configIncompleta);
console.log('Validação:', result3);

// Teste 4: Array com tamanho errado
console.log('\n=== TESTE 4: Array Sensibilidade Errado ===');
const configArrayErrado = {
  ...configValida,
  sensibilidade: [50, 50, 50] // Deveria ter 8 valores
};
const result4 = validator.validateConfig(configArrayErrado);
console.log('Validação:', result4);

// Teste 5: Ver schema
console.log('\n=== TESTE 5: Schema ===');
console.log(JSON.stringify(validator.getSchema(), null, 2));