var bigArray = require('../build/Release/big_array');

var ba = new bigArray.UnsignedChar();

ba.set(1, 5);
ba.inc(1);
ba.dec(1);
ba.dec(1);
ba[1] = 1;
console.log(ba.get(1));