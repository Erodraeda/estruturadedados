const fs = require('fs');

const lastNumber = 30333

let numbers = ''

for (let i = 1; i <= lastNumber; i++) {
    numbers += (`${between(1, 100000)}`);
    (i != lastNumber) ? numbers += `,` : '';
}

function between(min, max) {  
    return Math.floor(
      Math.random() * (max - min) + min
    )
}

fs.writeFileSync('./numb.txt', numbers, err => {
    if (err) console.error('duh')
})
