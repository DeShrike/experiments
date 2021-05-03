// Typescript

import { formData } from "./forms";

const form = document.querySelector("form")!;

form.addEventListener("submit", (e) => {
  e.preventDefault();
  const data = formData(form);
  console.log(data);
});

var msg:string = "Hallo Allemaal";

console.log(msg);
console.log(msg);
console.log(msg);

