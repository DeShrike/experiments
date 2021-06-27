
let a = function() {

    let aa = {
        text1: "Hello",
        num1: 32,
        text2: "Yo",
        num2: 42,
        uu: "UUUUUUUUU"
    };

    return aa;
};


let b = () => { return [10, 20] };
let c = () => { return [10, 20] };

let d = ({ name, data: { age } }) => { return "Hello " + name + " " + age; }

let person = {
	code: 12,
	name: "John",
	data: { email: "john@home.com", age: 54, cb: b },
};

let customer = {
	customername: "Klant",
	data: { customeremail: "klant@home.com", revenue: 54 },
};



const { name, ...rest } = person;
console.log(rest);

const personcust = { ...person, ...customer };
console.log("Person+Customer=");
console.log(personcust);

console.log(d(person));

const { text2, text1, num1 } = a();
const [ num11, num22 ] = b();

console.log(text1);
console.log(text2);
console.log(num1);

console.log(num11);
console.log(num22);

const xx = ({ uu }) => ({ oo: "sdfsdf" + uu, sdfsdf:"fsdf" } );

const uuu  = {uu: 12222 , yy: 12};

console.log(xx( uuu ));
console.log(xx( {uu: 4244 , yy: 42} ));
console.log(xx( a() ));

const zz = xx( { ehllo:"hello", uu: " dit" } );
console.log(zz);

