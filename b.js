const queryString = require('querystring');

const originalString = 'Hello, World! How are you?';
const escapedString = queryString.escape(originalString);

console.log('Original String:', originalString);
console.log('Escaped String:', escapedString);