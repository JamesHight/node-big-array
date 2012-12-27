var assert = require('assert'),
	bigArray = require('../build/Release/big_array'),
	ba, i;

ba = new bigArray.UnsignedChar(1, 10);

assert(ba.getSize() == 10, "Initial allocation of size");
assert(ba.getBlockSize() == 10, "Initial allocation of block size");

for(i = 0; i < 100; i++) {
	ba.push(i);
}

assert(ba.getIndex() == 100, "Push 100 elements into array");
assert(ba.getSize() == 100, "Check size after push");

for(i = 0; i < 98; i++) {
	ba.pop();
}

assert(ba.getIndex() == 2, "Pop 98 elements off array");

ba.setIndex(10);
for(i = 0; i < 50; i++) {
	ba.push(i);
}

assert(ba.getIndex() == 60, "Set index 10, push 50");
assert(ba.get(59) == 49, "Check 60th element value");

ba.inc(59);
assert(ba.get(59) == 50, "Check inc");
ba.dec(59);
assert(ba.get(59) == 49, "Check dec");

ba.resize(11);
assert(ba.getSize() == 20, "Check size after resize");
assert(ba.get(59) == 0, "Check 60th element after resize");