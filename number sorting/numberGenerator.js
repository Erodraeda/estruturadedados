const fs = require('fs');

let numbers = ''

const arraysize = process.argv[2]

const filename = process.argv[3]

console.log(arraysize, filename)

for (let i = 1; i <= arraysize; i++) {
    numbers += (`${between(1, 100000)}`);
    (i != arraysize) ? numbers += `,` : '';
}

function between(min, max) {  
    return Math.floor(
      Math.random() * (max - min) + min
    )
}

fs.writeFileSync(`./${filename}.txt`, numbers, err => {
    if (err) console.error('duh')
})
