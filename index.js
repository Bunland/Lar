// var {rs} = require('modulo.js');


const arr = [
    {
        id: 1,
        name: "lucas",
        email: "lucas@gmail.com"
    },
    {
        id: 2,
        name: "martin",
        email: "martin@gmail.com"
    }
];

const mappedArray = arr.map(item => {
    return {
        ...item,
        uppercaseName: item.name.toUpperCase()
    };
});

// Utiliza JSON.stringify para imprimir los objetos de manera legible
console.log(JSON.stringify(mappedArray, null, 2));



// console.log(JSON.stringify(arr)); 


// let objec = []

// let person;

// for (let index = 0; index < 10; index++) {
//     person = {
//         id: index,
//         name: "lucas",
//         age: Add(2, 26)
//     }
//     objec.push(person)
// }

// JSON.stringify(objec)

// // Mult(2); 
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", 1+2)
// console.log("albv", Mult(2, 2))
// console.log("some", JSON.stringify(objec))