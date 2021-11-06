const { publicEncrypt, privateDecrypt } = require("crypto");
const { publicKey, privateKey } = require("./keypair");

const message = "This cake is a lie !!!";

const encryptedData = publicEncrypt(
        publicKey,
        Buffer.from(message),
    );

console.log("Encrypted");
console.log(encryptedData.toString("hex"));

const decryptedData = privateDecrypt(
        privateKey,
        encryptedData
    );

console.log("Decrypted");
console.log(decryptedData.toString("utf-8"));

