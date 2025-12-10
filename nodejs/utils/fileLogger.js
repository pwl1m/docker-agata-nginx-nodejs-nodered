const fs = require('fs').promises;
const path = require('path');

class FileLogger {
    constructor() {
        this.baseLogDir = path.join(__dirname, '../logs');
        this.rawDataDir = path.join(this.baseLogDir, 'raw-data');
        this.processedDir = path.join(this.baseLogDir, 'processed');
        this.textLogsDir = path.join(this.baseLogDir, 'text-logs');
        this.changesDir = path.join(this.baseLogDir, 'changes');
        this.noChangesDir = path.join(this.baseLogDir, 'no-changes');
        this.initialized = false;
        this.writeQueue = [];
        this.writing = false;
        this.DEBUG = process.env.DEBUG === 'true';
        this.maxRecordsPerDevice = 1000; // Limite de registros por device
        this.changeDetector = require('./changeDetector');
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
            await fs.mkdir(this.changesDir, { recursive: true });
            await fs.mkdir(this.noChangesDir, { recursive: true });
            this.initialized = true;
            this.log('Diretórios de log criados:', {
                raw: this.rawDataDir,
                processed: this.processedDir,
                text: this.textLogsDir,
                changes: this.changesDir,
                noChanges: this.noChangesDir
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
                const date = new Date().toISOString().split('T')[0];
                const filename = `${filenamePrefix}-${date}.log`;       
                const filepath = path.join(this.rawDataDir, filename);

                const logEntry = `[${new Date().toISOString()}] ${JSON.stringify(data)}\n`;

                await fs.appendFile(filepath, logEntry);
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
                const date = new Date().toISOString().split('T')[0];
                const filename = `agata-decrypted-${date}.log`;
                const filepath = path.join(this.rawDataDir, filename);

                const logEntry = {
                    timestamp: new Date().toISOString(),
                    device_serial: decryptedData.srl || originalInfo.serial || 'unknown',
                    decrypted_data: decryptedData,
                    original_info: originalInfo,
                    processing_time: new Date().toISOString()
                };

                await fs.appendFile(filepath, JSON.stringify(logEntry) + '\n');
                this.log(`Decrypted data salvo: ${filename}`);
                return filepath;
            } catch (error) {
                console.error('Erro ao salvar decrypted data:', error.message);
                return null;
            }
        });
    }

    async logTextTransaction(data, source = 'agata') {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                const date = new Date().toISOString().split('T')[0];
                const filename = `${source}-transactions-${date}.log`;
                const filepath = path.join(this.textLogsDir, filename);

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

            const date = new Date().toISOString().split('T')[0];
            const filename = `${filenamePrefix}-${date}.log`;       
            const filePath = path.join(dir, filename);

            await fs.appendFile(filePath, JSON.stringify(normalizedData) + '\n');
            this.log(`Flat salvo: ${filename}`);
            return filePath;
        });
    }

    async saveWithChangeDetection(data, source = 'agata') {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                
                // Garantir que os diretórios de mudanças existam
                await fs.mkdir(this.changesDir, { recursive: true });
                await fs.mkdir(this.noChangesDir, { recursive: true });
                
                const serial = data.srl || data.serial || 'unknown';
                const date = new Date().toISOString().split('T')[0];
                
                // Extrair apenas os dados que queremos monitorar por mudanças
                const monitorData = {
                    sensitivities: data.sensitivities || data.monit || {},
                    voltages: data.voltages || {},
                    errors: data.errors || data.erros || {},
                    events: data.events || data.event || [],
                    audit: data.audit || {},
                    // Adicione outros campos que quiser monitorar
                    blc: data.blc || '',
                    // Campos específicos do Agata que são importantes
                    specificFields: this.extractSpecificFields(data)
                };

                // Detectar mudanças
                const changeInfo = this.changeDetector.detectChanges(serial, monitorData);
                
                // Definir em qual diretório salvar
                let targetDir, filenamePrefix;
                
                if (changeInfo.hasChanges) {
                    targetDir = this.changesDir;
                    filenamePrefix = `${source}-changed`;
                    
                    // Salvar log detalhado das mudanças
                    await this.changeDetector.logChange(changeInfo);
                    
                    // Log para debug
                    this.log(`Mudanças detectadas para ${serial}:`, changeInfo.changedFields);
                } else {
                    targetDir = this.noChangesDir;
                    filenamePrefix = `${source}-nochange`;
                    
                    this.log(`Sem mudanças para ${serial}`, {
                        timestamp: new Date().toISOString()
                    });
                }
                
                const filename = `${filenamePrefix}-${date}.log`;
                const filepath = path.join(targetDir, filename);
                
                const logEntry = {
                    timestamp: new Date().toISOString(),
                    serial,
                    hasChanges: changeInfo.hasChanges,
                    changedFields: changeInfo.changedFields,
                    data: data,
                    changeInfo: changeInfo.hasChanges ? changeInfo.fieldComparison : null
                };
                
                await fs.appendFile(filepath, JSON.stringify(logEntry) + '\n');
                
                // Também salvar em um arquivo CSV para fácil análise
                await this.saveChangeToCSV(logEntry);
                
                return {
                    filepath,
                    hasChanges: changeInfo.hasChanges,
                    changedFields: changeInfo.changedFields,
                    changeInfo
                };
                
            } catch (error) {
                console.error('Erro ao salvar com detecção de mudanças:', error.message);
                return null;
            }
        });
    }

    // Método auxiliar para extrair campos específicos
    extractSpecificFields(data) {
        const fields = {};
        
        // Exemplo: extrair valores específicos do array monit
        if (Array.isArray(data.monit)) {
            // Supondo que os primeiros 8 valores são sensores importantes
            for (let i = 0; i < Math.min(8, data.monit.length); i++) {
                fields[`sensor_${i}`] = data.monit[i];
            }
            
            // Timestamp do dispositivo (índice 28 no exemplo)
            if (data.monit.length > 28) {
                fields.device_timestamp = data.monit[28];
            }
        }
        
        // Extrair informações específicas do audit
        if (Array.isArray(data.audit) && data.audit.length >= 6) {
            fields.audit_status = data.audit[1];
            fields.audit_counter = data.audit[2];
            fields.audit_action = data.audit[3] + data.audit[4];
        }
        
        return fields;
    }

    // Método para salvar em CSV (opcional)
    async saveChangeToCSV(logEntry) {
        const csvDir = path.join(this.baseLogDir, 'changes-csv');
        await fs.mkdir(csvDir, { recursive: true });
        
        const date = new Date().toISOString().split('T')[0];
        const filename = `changes-${date}.csv`;
        const filepath = path.join(csvDir, filename);
        
        // Cabeçalho do CSV (criar se arquivo não existe)
        let csvLine = '';
        try {
            const stats = await fs.stat(filepath);
            if (stats.size === 0) {
                csvLine = 'timestamp,serial,hasChanges,changedFieldsCount,changedFields\n';
            }
        } catch (error) {
            // Arquivo não existe, adicionar cabeçalho
            csvLine = 'timestamp,serial,hasChanges,changedFieldsCount,changedFields\n';
        }
        
        csvLine += `${logEntry.timestamp},${logEntry.serial},${logEntry.hasChanges},${logEntry.changedFields?.length || 0},"${logEntry.changedFields?.join('|') || ''}"\n`;
        
        await fs.appendFile(filepath, csvLine);
    }
}

module.exports = new FileLogger();
