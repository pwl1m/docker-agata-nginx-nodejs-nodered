const fs = require('fs');
const path = require('path');

// Diretório onde os logs serão armazenados
const LOG_DIR = path.join(__dirname, '../logs');
const LOG_FILE = path.join(LOG_DIR, 'application.log');
const PROCESSED_LOG_FILE = path.join(LOG_DIR, 'processed-data.log');

// Garantir que o diretório de logs exista
if (!fs.existsSync(LOG_DIR)) {
    fs.mkdirSync(LOG_DIR, { recursive: true });
}

// Função para formatar a data/hora
function getTimestamp() {
    return new Date().toISOString();
}

// Função para gravar logs gerais
function log(level, message, meta = {}) {
    const logEntry = {
        timestamp: getTimestamp(),
        level,
        message,
        ...meta
    };

    const logLine = JSON.stringify(logEntry) + '\n';

    // Gravar no arquivo de log geral
    fs.appendFile(LOG_FILE, logLine, (err) => {
        if (err) {
            console.error('Erro ao gravar no arquivo de log:', err);
        }
    });

    // Também exibir no console
    console.log(`[${logEntry.timestamp}] [${level.toUpperCase()}] ${message}`);
}

// Função para gravar dados processados
function logProcessedData(data) {
    const logEntry = {
        timestamp: getTimestamp(),
        data
    };

    const logLine = JSON.stringify(logEntry) + '\n';

    // Gravar no arquivo de dados processados
    fs.appendFile(PROCESSED_LOG_FILE, logLine, (err) => {
        if (err) {
            console.error('Erro ao gravar no arquivo de dados processados:', err);
        }
    });

    console.log(`[${logEntry.timestamp}] [PROCESSED] Dados processados registrados.`);
}

module.exports = {
    info: (message, meta) => log('info', message, meta),
    error: (message, meta) => log('error', message, meta),
    debug: (message, meta) => log('debug', message, meta),
    logProcessedData
};