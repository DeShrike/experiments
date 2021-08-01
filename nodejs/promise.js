let p = new Promise((resolve, reject) => {

    let a = 1 + 1;
    if (a == 2)
    {
        resolve("Success");
    }
    else
    {
        recect("Fail");
    }
});


p.then((message) => {
    console.log("In .then " + message);
}).catch((message) => {
    console.log("In .catch " + message);
});
