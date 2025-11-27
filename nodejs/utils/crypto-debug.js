const crypto = require('crypto');

class AgataCryptoDebug {
  static decrypt(key, ciphertext) {
    console.log('\n=== DEBUG MODE ===');
    console.log('Input key:', JSON.stringify(key));
    console.log('Key length:', key.length);
    console.log('Ciphertext length:', ciphertext.length);
    console.log('Ciphertext (first 50):', ciphertext.substring(0, 50));

    const algorithm = 'aes-128-ecb'; // modelo crip padrão do agata
    const adjustedKey = (key + key + key).substring(0, 16); // Garante 16 bytes

    console.log('Algorithm:', algorithm);
    console.log('Adjusted key:', JSON.stringify(adjustedKey));
    console.log('Key length:', adjustedKey.length);

    try {
      const chiperRaw = Buffer.from(ciphertext, 'base64');
      const decipher = crypto.createDecipheriv(algorithm, adjustedKey, null);
      let decrypted = decipher.update(chiperRaw, null, 'utf8');
      decrypted += decipher.final('utf8');

      console.log('✅ SUCCESS! Decrypted:', decrypted);
      return decrypted;
    } catch (e) {
      console.log('❌ Failed:', e.message);
      return null;
    }
  }
}

module.exports = AgataCryptoDebug;