const crypto = require('crypto');

class AgataCrypto {
  // Descriptografar exatamente como no PHP legado
  static decrypt(key, ciphertext) {
    try {
      // Gerar chave igual ao PHP
      const password = key.repeat(3).substring(0, 16); // Ajuste para AES-128 

      console.log('Serial recebido:', key);
      console.log('Chave AES gerada:', password);
      console.log('Tamanho da chave:', password.length);

      // Decodificar base64
      const chiperRaw = Buffer.from(ciphertext, 'base64');
      console.log('Dados decodificados (base64 -> raw), tamanho:', chiperRaw.length);

      // Descriptografar com AES-128-ECB
      const decipher = crypto.createDecipheriv('aes-128-ecb', password, null);
      decipher.setAutoPadding(true);

      let decrypted = decipher.update(chiperRaw, null, 'utf8');
      decrypted += decipher.final('utf8');

      console.log('Descriptografia bem-sucedida!');
      console.log('Dados descriptografados:', decrypted);

      return decrypted;
    } catch (error) {
      console.error('Erro na descriptografia:', error.message);
      return null;
    }
  }

  static encrypt(key, plaintext) {
    try {
      const password = key.repeat(3).substring(0, 16);
      const cipher = crypto.createCipheriv('aes-128-ecb', password, null);    
      cipher.setAutoPadding(true);
      let encrypted = cipher.update(plaintext, 'utf8');
      encrypted = Buffer.concat([encrypted, cipher.final()]);
      return encrypted.toString('base64');
    } catch (error) {
      console.error('Erro na criptografia:', error.message);
      return null;
    }
  }
}

module.exports = AgataCrypto;