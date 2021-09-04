// Call python script

const  { spawn } = require("child_process")
const py = spawn("python3", ["script.py", "John Doe"])

py.stdout.on("data", (data) => {
    console.log(data);
    console.log(data.toString());
});

py.on("close", (code) => {
    console.log("Exit code:", code);
});
