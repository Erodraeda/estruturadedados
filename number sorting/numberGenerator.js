const fs = require('fs');

let numbers = ''

for (let i = 0; i < 32768; i++) {
    numbers += (`${between(1, 100000)},`);
}

function between(min, max) {  
    return Math.floor(
      Math.random() * (max - min) + min
    )
}

fs.writeFileSync('./numb.txt', numbers, err => {
    if (err) console.error('duh')
})