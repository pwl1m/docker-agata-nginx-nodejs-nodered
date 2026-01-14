'use strict';

module.exports = {
  injectTimestamp(source, opts = {}) {
    const unit = (opts.unit || process.env.AGATA_TIMESTAMP_UNIT || 's').toLowerCase();
    const idx = Number(opts.index ?? process.env.AGATA_TIMESTAMP_INDEX ?? 28);
    const field = opts.field || process.env.AGATA_TIMESTAMP_FIELD || 'server_timestamp';
    const ts = unit === 's' ? Math.floor(Date.now() / 1000) : Date.now();

    if (Array.isArray(source)) {
      const copy = source.slice();
      if (Number.isInteger(idx) && idx >= 0) {
        for (let i = copy.length; i <= idx; i++) copy.push(0);
        copy[idx] = ts;
      }
      return copy;
    }

    if (source && typeof source === 'object') {
      return { ...source, [field]: ts };
    }

    return source;
  },

  normalizeForSignature(source, opts = {}) {
    const idx = Number(opts.index ?? process.env.AGATA_TIMESTAMP_INDEX ?? 28);
    const field = opts.field || process.env.AGATA_TIMESTAMP_FIELD || 'server_timestamp';

    try {
      if (Array.isArray(source)) {
        const copy = source.slice();
        if (Number.isInteger(idx) && idx >= 0 && idx < copy.length) copy[idx] = 0;
        return JSON.stringify(copy);
      }

      if (source && typeof source === 'object') {
        const copy = { ...source };
        if (field in copy) copy[field] = 0;
        return JSON.stringify(copy);
      }

      return JSON.stringify(source);
    } catch (e) {
      return JSON.stringify(source);
    }
  }
};