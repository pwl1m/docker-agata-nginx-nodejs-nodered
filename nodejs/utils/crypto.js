const crypto = require('crypto');

class AgataCrypto {
  // Gerar bloco de senha igual ao PHP legado
  static gerarBlocoSenha(key) {
    const novaSenha = key + key + key;
    return novaSenha.substring(0, 16);
  }

  // Descriptografar exatamente como no PHP legado
  static decrypt(key, ciphertext) {
    try {
        console.log('🔐 Iniciando descriptografia...');
        console.log('Chave recebida:', key);
        console.log('Dados criptografados (início):', ciphertext.substring(0, 50));

        // Gerar chave igual ao PHP
        const password = key.repeat(3).substring(0, 16); // Ajuste para AES-128
        console.log('Chave AES gerada:', password);

        // Decodificar base64
        const chiperRaw = Buffer.from(ciphertext, 'base64');
        console.log('Dados decodificados (base64 -> raw), tamanho:', chiperRaw.length);

        // Descriptografar com AES-128-ECB
        const decipher = crypto.createDecipheriv('aes-128-ecb', password, null);
        decipher.setAutoPadding(true);

        let decrypted = decipher.update(chiperRaw, null, 'utf8');
        decrypted += decipher.final('utf8');

        console.log('✅ Descriptografia bem-sucedida!');
        return decrypted;

    } catch (error) {
        console.error('❌ Erro na descriptografia:', error.message);
        return null;
    }
  }

  // Analisar dados criptografados
  static analyzeEncryptedData(data) {
    if (!data || data.length < 6) {
      return { error: 'Dados muito curtos' };
    }

    const key = data.substring(0, 6);
    const encrypted = data.substring(6);

    console.log('🔍 Análise dos dados:');
    console.log('  - Chave (primeiros 6 dígitos):', key);
    console.log('  - Tamanho dados criptografados:', encrypted.length);
    console.log('  - É base64 válido?', this.isBase64(encrypted));

    if (this.isBase64(encrypted)) {
      const rawData = Buffer.from(encrypted, 'base64');
      console.log('  - Tamanho após decode base64:', rawData.length);
      console.log('  - Primeiros bytes (hex):', rawData.subarray(0, 16).toString('hex'));
    }

    return { key, encrypted };
  }

  // Verificar se é base64 válido
  static isBase64(str) {
    try {
      return Buffer.from(str, 'base64').toString('base64') === str;
    } catch (e) {
      return false;
    }
  }
}

module.exports = AgataCrypto;