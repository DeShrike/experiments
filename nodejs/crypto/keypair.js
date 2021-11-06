const { generateKeyPairSync } = require("crypto");

const { privateKey, publicKey } = generateKeyPairSync("rsa", {
    modulusLength: 2048, // length of the key in bits
    publicKeyEncoding: {
        type: "spki",   // recommended
        format: "pem",  // PEM = Privacy Enhanced Mail
    },
    privateKeyEncoding: {
        type: "pkcs8",  // recommended
        format: "pem",  // PEM = Privacy Enhanced Mail
        // cipher: "azs-256-cbc",
        // passphrase: "top secret",
    },
});

console.log(publicKey);
console.log(privateKey);

module.exports = {
    privateKey, publicKey
}
