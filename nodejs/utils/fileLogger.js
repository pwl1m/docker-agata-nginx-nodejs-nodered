const fs = require('fs').promises;
const path = require('path');

class FileLogger {
    constructor() {
        this.baseLogDir = path.join(__dirname, '../logs');
        this.rawDataDir = path.join(this.baseLogDir, 'raw-data');
        this.processedDir = path.join(this.baseLogDir, 'processed'); // ← NOVO
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
            await fs.mkdir(this.processedDir, { recursive: true }); // ← NOVO
            await fs.mkdir(this.textLogsDir, { recursive: true });
            this.initialized = true;
            this.log('📁 Diretórios de log criados:', {
                raw: this.rawDataDir,
                processed: this.processedDir,
                text: this.textLogsDir
            });
        } catch (error) {
            console.error('Erro ao criar diretórios de logs:', error);
            try {
                this.baseLogDir = '/tmp/logs';
                this.rawDataDir = path.join(this.baseLogDir, 'raw-data');
                this.processedDir = path.join(this.baseLogDir, 'processed');
                this.textLogsDir = path.join(this.baseLogDir, 'text-logs');
                await fs.mkdir(this.rawDataDir, { recursive: true });
                await fs.mkdir(this.processedDir, { recursive: true });
                await fs.mkdir(this.textLogsDir, { recursive: true });
                this.initialized = true;
                this.log('📁 Usando diretório temporário:', this.baseLogDir);
            } catch (fallbackError) {
                console.error('❌ Erro crítico: não foi possível criar diretórios de log');
            }
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
                this.log(`📁 Raw data salvo: ${filename}`);
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
                this.log(`🔓 Decrypted data salvo: ${filename}`);
                return filepath;
            } catch (error) {
                console.error('Erro ao salvar decrypted data:', error.message);
                return null;
            }
        });
    }

    // ← NOVO: Salvar dados processados (formato amigável)
    async saveProcessedData(normalizedData) {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();

                const serial = normalizedData.serial || 'unknown';
                const deviceFile = path.join(this.processedDir, `device-${serial}.json`);

                let history = [];

                // Ler histórico existente
                try {
                    const existing = await fs.readFile(deviceFile, 'utf8');
                    history = JSON.parse(existing);
                    if (!Array.isArray(history)) history = [];
                } catch (err) {
                    // Arquivo não existe, criar novo
                    history = [];
                }

                // Adicionar novo registro
                history.push({
                    ...normalizedData,
                    received_at: new Date().toISOString()
                });

                // Limitar registros (manter últimos N)
                if (history.length > this.maxRecordsPerDevice) {
                    history = history.slice(-this.maxRecordsPerDevice);
                }

                // Salvar histórico atualizado
                await fs.writeFile(deviceFile, JSON.stringify(history, null, 2));

                this.log(`✅ Processed data salvo: device-${serial}.json (${history.length} registros)`);

                // Atualizar resumo geral
                await this.updateDeviceSummary(serial, normalizedData);

                return deviceFile;
            } catch (error) {
                console.error('Erro ao salvar processed data:', error.message);
                return null;
            }
        });
    }

    // ← NOVO: Atualizar resumo de devices
    async updateDeviceSummary(serial, latestData) {
        try {
            const summaryFile = path.join(this.processedDir, 'device-summary.json');
            let summary = {};

            try {
                const existing = await fs.readFile(summaryFile, 'utf8');
                summary = JSON.parse(existing);
            } catch (err) {
                summary = {};
            }

            summary[serial] = {
                serial: serial,
                last_update: new Date().toISOString(),
                last_data: {
                    id: latestData.id,
                    data_registro: latestData.data_registro,
                    tensao_rede: latestData.tensao_rede,
                    tensao_bateria1: latestData.tensao_bateria1,
                    metais: latestData.metais,
                    ruidos: latestData.ruidos,
                    aberto: latestData.aberto,
                    ok: latestData.ok
                },
                total_records: summary[serial]?.total_records ? summary[serial].total_records + 1 : 1
            };

            await fs.writeFile(summaryFile, JSON.stringify(summary, null, 2));
        } catch (error) {
            console.error('Erro ao atualizar summary:', error.message);
        }
    }

    async logTextTransaction(data, source = 'agata') {
        return this.enqueue(async () => {
            try {
                await this.ensureLogDirectories();
                const date = new Date();
                const dateString = date.toISOString().split('T')[0];
                const filename = `${source}-transactions-${dateString}.log`;
                const filepath = path.join(this.textLogsDir, filename);

                const monit = data.monit || [];
                const logEntry = `
=== ${source.toUpperCase()} DATA TRANSACTION ===
Timestamp: ${date.toISOString()}
Device Serial: ${data.srl || 'unknown'}
Data Length: ${JSON.stringify(data).length}
Sensitivities: ${monit.slice(0, 8).join(', ')}
Voltages: ${monit[10]}, ${monit[11]}, ${monit[12]}, ${monit[13]}, ${monit[14]}
Errors: ${data.erros ? data.erros.join(', ') : 'none'}
Events: ${data.event ? data.event.length : 0}
Audit: ${data.audit ? data.audit.join(', ') : 'none'}
================================
                `.trim();

                await fs.appendFile(filepath, logEntry + '\n\n');
                this.log(`📝 Transaction log salvo: ${filename}`);
            } catch (error) {
                console.error('Erro ao salvar transaction log:', error.message);
            }
        });
    }

    async debugDirectories() {
        console.log('🔍 Debug - Diretórios de log:');
        console.log('  - Base:', this.baseLogDir);
        console.log('  - Raw Data:', this.rawDataDir);
        console.log('  - Processed:', this.processedDir);
        console.log('  - Text Logs:', this.textLogsDir);

        try {
            const baseExists = await fs.access(this.baseLogDir).then(() => true).catch(() => false);
            const rawExists = await fs.access(this.rawDataDir).then(() => true).catch(() => false);
            const processedExists = await fs.access(this.processedDir).then(() => true).catch(() => false);
            const textExists = await fs.access(this.textLogsDir).then(() => true).catch(() => false);

            console.log('  - Base existe:', baseExists);
            console.log('  - Raw Data existe:', rawExists);
            console.log('  - Processed existe:', processedExists);
            console.log('  - Text Logs existe:', textExists);
        } catch (error) {
            console.log('  - Erro ao verificar diretórios:', error.message);
        }
    }

    logRaw(data) {
        return this.logRawData(data);
    }

    // Compatível com agataController.js
    async saveAllDevicesData(serial, data) {
        await this.ensureLogDirectories();
        const allDevicesFile = path.join(this.processedDir, 'all-devices.json');
        let allData = {};

        // Ler o arquivo existente
        try {
            const existing = await fs.readFile(allDevicesFile, 'utf8');
            allData = JSON.parse(existing);
        } catch (err) {
            allData = {};
        }

        // Adicionar novo registro ao serial
        if (!allData[serial]) allData[serial] = [];
        allData[serial].push({
            timestamp: new Date().toISOString(),
            dados: data
        });

        // Salvar arquivo atualizado
        await fs.writeFile(allDevicesFile, JSON.stringify(allData, null, 2));
    }

    async saveFlatProcessedData(normalizedData, filenamePrefix = 'agata-flat') {
        return this.enqueue(async () => {
            await this.ensureLogDirectories();
            const dir = path.join(this.baseLogDir, 'processed-flat');
            await fs.mkdir(dir, { recursive: true });

            const serial = normalizedData.serial || 'unknown';
            const iso = new Date().toISOString().replace(/[:.]/g, '-'); // igual ao raw-data
            const filename = `${filenamePrefix}-${serial}-${iso}.json`;
            const filePath = path.join(dir, filename);

            await fs.writeFile(filePath, JSON.stringify(normalizedData, null, 2));
            this.log(`🗂️ Flat salvo: ${filename}`);
            return filePath;
        });
    }
}

module.exports = new FileLogger();