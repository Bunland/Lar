const result = require("./module.js");

console.log("Hello world")
console.log(lar.exists("some.json"))
console.log(lar.readFile("some.json"))
lar.write('file.txt', JSON.stringify(result));
lar.remove("file.txt")

const decode = lar.querystring.decode("id=1&name=lucas");
console.log(decode.id);  
console.log(decode.name); 
console.log(JSON.stringify(decode))

const obj = {
    id: 1,
    name: "lucas",
    email: "vital@gmail.com"
}

const encode = lar.querystring.encode(obj);
console.log(encode)

const escape = lar.querystring.escape("Hello, World! How are you?");
console.log(escape);

const unescape = lar.querystring.unescape(escape);
console.log(unescape);
