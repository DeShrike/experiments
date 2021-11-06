const { createHmac } = require("crypto");

const key = "Super -Secret";

const message = "BooBo";

const hmac = createHmac("sha256", key).update(message).digest("hex");

console.log(hmac);

const key2 = "Other Secret";
const hmac2 = createHmac("sha256", key2).update(message).digest("hex");

console.log(hmac2);


