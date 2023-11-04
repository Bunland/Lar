let objec = []

let person;

for (let index = 0; index < 100; index++) {
    person = {
        id: Add(2, index),
        name: "lucas",
        age: Mult(2, index)
    }
    objec.push(person)
}

JSON.stringify(person);