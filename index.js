const obj = require("./module.js");


console.log("Hello world")
console.log(lar.exists("some.json"))
console.log(lar.readFile("some.json"))
lar.write('file.txt', JSON.stringify(obj.file));
lar.remove("file.txt")

