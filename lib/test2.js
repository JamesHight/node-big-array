var v = new Int8Array(10000000000);

for (var i = 0; i < 1000000000; i++) {
	v[i] = 0;
}

console.log(v.length);