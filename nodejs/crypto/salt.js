const { scryptSync, randomBytes, timingSafeEqual } = require("crypto");

var users = [];

function signup(email, password)
{
    const salt = randomBytes(16).toString("hex");
    const hashedPw = scryptSync(password, salt, 64).toString("hex");

    const user = { email, password: salt + ":" + hashedPw };

    users.push(user);

    return user;
}

function login(email, password)
{
    const user = users.find(v => v.email === email);

    const [salt, key] = user.password.split(":");
    const hashedBuffer = scryptSync(password, salt, 64);

    const keyBuffer = Buffer.from(key, "hex");
    const match = timingSafeEqual(hashedBuffer, keyBuffer);

    return match;
}

const u = signup("Jan", "secret");
console.log(u);

const ok = login("Jan", "secret");
console.log(ok);

