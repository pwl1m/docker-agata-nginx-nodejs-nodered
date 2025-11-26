const crypto = require('crypto');

class AgataCryptoDebug {
  static decrypt(key, ciphertext) {
    console.log('\n=== DEBUG MODE ===');
    console.log('Input key:', JSON.stringify(key));
    console.log('Key length:', key.length);
    console.log('Ciphertext length:', ciphertext.length);
    console.log('Ciphertext (first 50):', ciphertext.substring(0, 50));

    // Tentar todas as variações possíveis
    const variations = [
      { name: 'AES-128-ECB', algorithm: 'aes-128-ecb', key: key + key + key },
      { name: 'AES-128-ECB-pad', algorithm: 'aes-128-ecb', key: (key + key + key).substring(0, 16) },
      { name: 'AES-256-ECB', algorithm: 'aes-256-ecb', key: (key + key + key + key).substring(0, 32) },
    ];

    for (let variation of variations) {
      console.log(`\nTrying: ${variation.name}`);
      console.log('Algorithm:', variation.algorithm);
      console.log('Key:', JSON.stringify(variation.key));
      console.log('Key length:', variation.key.length);

      try {
        const chiperRaw = Buffer.from(ciphertext, 'base64');
        const decipher = crypto.createDecipheriv(variation.algorithm, variation.key, null);
        let decrypted = decipher.update(chiperRaw, null, 'utf8');
        decrypted += decipher.final('utf8');

        console.log('✅ SUCCESS! Decrypted:', decrypted);
        return decrypted;
      } catch (e) {
        console.log('❌ Failed:', e.message);
      }
    }

    return null;
  }
}

module.exports = AgataCryptoDebug;