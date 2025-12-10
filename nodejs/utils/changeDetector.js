// file: utils/changeDetector.js
const path = require('path');
const fs = require('fs').promises;

class ChangeDetector {
    constructor() {
        this.lastValues = new Map(); // Map<serial, Map<field, value>>
        this.changesDir = path.join(__dirname, '../logs/changes');
    }

    async initialize() {
        await fs.mkdir(this.changesDir, { recursive: true });
    }

    /**
     * Detecta quais campos mudaram em relação ao último registro
     * @param {Object} data - Dados atuais
     * @returns {Object} { hasChanges: boolean, changedFields: Array, previousValues: Object, currentValues: Object }
     */
    detectChanges(serial, currentData) {
        const serialStr = String(serial);
        const currentMap = this.lastValues.get(serialStr);
        const changedFields = [];
        const fieldComparison = {};

        if (!currentMap) {
            // Primeiro registro para este serial
            this.lastValues.set(serialStr, new Map());
            this.updateLastValues(serialStr, currentData);
            return {
                hasChanges: true,
                changedFields: Object.keys(currentData),
                previousValues: {},
                currentValues: currentData,
                isFirst: true
            };
        }

        // Compara cada campo
        for (const [field, currentValue] of Object.entries(currentData)) {
            const previousValue = currentMap.get(field);
            const hasChanged = !this.areValuesEqual(previousValue, currentValue);

            if (hasChanged) {
                changedFields.push(field);
                fieldComparison[field] = {
                    previous: previousValue,
                    current: currentValue,
                    timestamp: new Date().toISOString()
                };
            }
        }

        // Atualiza os últimos valores
        this.updateLastValues(serialStr, currentData);

        return {
            hasChanges: changedFields.length > 0,
            changedFields,
            previousValues: Object.fromEntries(currentMap),
            currentValues: currentData,
            fieldComparison,
            serial: serialStr,
            timestamp: new Date().toISOString()
        };
    }

    /**
     * Compara valores, tratando arrays e objetos
     */
    areValuesEqual(a, b) {
        if (a === b) return true;
        if (a == null || b == null) return a == b;
        
        if (Array.isArray(a) && Array.isArray(b)) {
            if (a.length !== b.length) return false;
            return a.every((val, idx) => this.areValuesEqual(val, b[idx]));
        }
        
        if (typeof a === 'object' && typeof b === 'object') {
            const aKeys = Object.keys(a);
            const bKeys = Object.keys(b);
            if (aKeys.length !== bKeys.length) return false;
            return aKeys.every(key => this.areValuesEqual(a[key], b[key]));
        }
        
        return false;
    }

    updateLastValues(serial, data) {
        const map = this.lastValues.get(serial) || new Map();
        for (const [field, value] of Object.entries(data)) {
            map.set(field, value);
        }
        this.lastValues.set(serial, map);
    }

    /**
     * Salva log detalhado das mudanças
     */
    async logChange(changeInfo) {
        if (!changeInfo.hasChanges) return null;

        const date = new Date().toISOString().split('T')[0];
        const filename = `agata-changes-${date}.log`;
        const filepath = path.join(this.changesDir, filename);

        const logEntry = {
            timestamp: new Date().toISOString(),
            serial: changeInfo.serial,
            changedFields: changeInfo.changedFields,
            fieldComparison: changeInfo.fieldComparison,
            fullData: changeInfo.currentValues
        };

        await fs.appendFile(filepath, JSON.stringify(logEntry) + '\n');
        return filepath;
    }

    /**
     * Obtém histórico de mudanças para um serial específico
     */
    getChangeHistory(serial, limit = 10) {
        const map = this.lastValues.get(String(serial));
        if (!map) return [];
        
        // Em produção, você buscaria de um banco de dados
        return Array.from(map.entries()).slice(-limit);
    }

    /**
     * Reseta os valores para um serial (útil para testes)
     */
    resetSerial(serial) {
        this.lastValues.delete(String(serial));
    }
}

module.exports = new ChangeDetector();