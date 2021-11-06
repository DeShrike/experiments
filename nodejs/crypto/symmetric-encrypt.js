const { createCipheriv, randomBytes, createDecipheriv } = require("crypto");

/// Cipher

const message = "I'm using Node JS";

const key = randomBytes(32);
const iv = randomBytes(16);

const cipher = createCipheriv("aes256", key, iv);

console.log("Original Message");
console.log(message);

/// Encrypt

const encryptedMessage = cipher.update(message, "utf8", "hex")
                            + cipher.final("hex");

console.log("Encrpted");
console.log(encryptedMessage);

/// Decrypt

const decipher = createDecipheriv("aes256", key, iv);
const decryptedMessage = decipher.update(encryptedMessage, "hex", "utf-8") 
                        + decipher.final("utf8");

console.log("Decrypted");
console.log(decryptedMessage);
