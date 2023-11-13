const obj = require("./module.js");

if (obj.file && typeof obj.file == "object") {
    file.map((e) => {
    console.log(JSON.stringify(e.id));
  });
}

lar.write('file.txt', JSON.stringify(obj.file));
lar.remove("file.txt")
