const fs = require('fs').promises;
const path = require('path');

class FileLogger {
    constructor() {
        this.baseLogDir = path.join(__dirname, '../logs');
        this.rawDataDir = path.join(this.baseLogDir, 'raw-data');
        this.processedDir = path.join(this.baseLogDir, 'processed');
        this.textLogsDir = path.join(this.baseLogDir, 'text-logs');
        this.initialized = false;
        this.writeQueue = [];
        this.writing = false;
        this.DEBUG = process.env.DEBUG === 'true';
        this.maxRecordsPerDevice = 1000; // Limite de registros por device    
    }

    log(...args) {
        if (this.DEBUG) console.log(...args);
    }

    async ensureLogDirectories() {
        if (this.initialized) return;

        try {
            await fs.mkdir(this.rawDataDir, { recursive: true });
            await fs.mkdir(this.processedDir, { recursive: true });
            await fs.mkdir(this.textLogsDir, { recursive: true });
            this.initialized = true;
            this.log('Diretórios de log criados:', {
                raw: this.rawDataDir,
                processed: this.processedDir,
                text: this.textLogsDir
            });
        } catch (error) {
            console.error('Erro ao criar diretórios de logs:', error);        
        }
    }

    enqueue(fn) {
        return new Promise((resolve, reject) => {
            this.writeQueue.push({ fn, resolve, reject });
            if (!this.writing) this.drainQueue();
        });
    }

    async drainQueue() {
        if (this.writeQueue.length === 0) {
            this.writing = false;
            return;
        }
        this.writing = true;
        const { fn, resolve, reject } = this.writeQueue.shift();
        try {
            const result = await fn();
            resolve(result);
        } catch (err) {
            reject(err);
        } finally {
            setImmediate(() => this.drainQueue());
        }
    }

    async logRawData(data, filenamePrefix = 'agata-raw') {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
                const filename = `${filenamePrefix}-${timestamp}.json`;       
                const filepath = path.join(this.rawDataDir, filename);        

                const logEntry = {
                    timestamp: new Date().toISOString(),
                    ...data
                };

                await fs.writeFile(filepath, JSON.stringify(logEntry, null, 2));
                this.log(`Raw data salvo: ${filename}`);
                return filepath;
            } catch (error) {
                console.error('Erro ao salvar raw data:', error.message);     
                return null;
            }
        });
    }

    async logDecryptedData(decryptedData, originalInfo = {}) {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
                const filename = `agata-decrypted-${timestamp}.json`;
                const filepath = path.join(this.rawDataDir, filename);        

                const logEntry = {
                    timestamp: new Date().toISOString(),
                    device_serial: decryptedData.srl || originalInfo.serial || 'unknown',
                    decrypted_data: decryptedData,
                    original_info: originalInfo,
                    processing_time: new Date().toISOString()
                };

                await fs.writeFile(filepath, JSON.stringify(logEntry, null, 2));
                this.log(`Decrypted data salvo: ${filename}`);
                return filepath;
            } catch (error) {
                console.error('Erro ao salvar decrypted data:', error.message);
                return null;
            }
        });
    }

    // Adicionado: logTextTransaction (usado no controller)
    async logTextTransaction(data, source = 'agata') {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                const date = new Date().toISOString().split('T')[0];
                const filename = `${source}-transactions-${date}.log`;
                const filepath = path.join(this.textLogsDir, filename);

                // Adaptação para pegar os campos corretos
                const sensitivities = data.sensitivities || data.monit || {};
                const voltages = data.voltages || {};
                const errors = data.errors || data.erros || {};
                const events = data.events || data.event || {};
                const audit = data.audit || {};

                const logEntry = `
Timestamp: ${new Date().toISOString()}
Device Serial: ${data.srl || data.serial || 'unknown'}
Sensitivities: ${JSON.stringify(sensitivities)}
Voltages: ${JSON.stringify(voltages)}
Errors: ${JSON.stringify(errors)}
Events: ${JSON.stringify(events)}
Audit: ${JSON.stringify(audit)}
---
`;
                await fs.appendFile(filepath, logEntry);
                this.log(`Text transaction logged: ${filename}`);
                return filepath;
            } catch (error) {
                console.error('Erro ao logar text transaction:', error.message);
                return null;
            }
        });
    }

    async saveFlatProcessedData(normalizedData, filenamePrefix = 'agata-flat') {
        return this.enqueue(async () => {
            await this.ensureLogDirectories();
            const dir = path.join(this.baseLogDir, 'processed-flat');
            await fs.mkdir(dir, { recursive: true });

            const serial = normalizedData.serial || 'unknown';
            const iso = new Date().toISOString().replace(/[:.]/g, '-');       
            const filename = `${filenamePrefix}-${serial}-${iso}.json`;       
            const filePath = path.join(dir, filename);

            await fs.writeFile(filePath, JSON.stringify(normalizedData, null, 2));
            this.log(`Flat salvo: ${filename}`);
            return filePath;
        });
    }
}

module.exports = new FileLogger();