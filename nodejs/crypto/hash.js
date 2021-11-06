
const { createHash } = require("crypto");

function hash(input)
{
    return createHash("sha256").update(input).digest("hex"); // or base64
}

let password = "Top secret !";
const hash1 = hash(password);
console.log(password);
console.log(hash1);
