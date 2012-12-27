Big Array
---------

A resizable array using non-sequential block memory allocation. 
Growing or shrinking the array does not require reallocation of the entire array. 
Useful when you need to track a few trillion data points.

Note: For best results a 64-bit system and enough RAM to hold your data is recommended. If your data set grows slowly over time, paging to virtual memory may be acceptable.

````bash
	npm install big-array
````

Usage: bigArray.Char(numberOfInitialElements, sizeOfElementBlocks)

* numberOfInitialElements: Number of array elements to initially allocate, rounds up to the nearest number divisible by sizeOfElementBlocks. default is 1
* sizeOfElementBlocks: Number of elements to allocate in each memory block. If this number is too small it will drastically increase the overhead memory usage for large arrays. default is 1048576 (1 MB for char)

````javascript
	var bigArray = require('big-array'),
		ba, val;

	// Numeric array types
	ba = new bigArray.Char(10, 100);
	ba = new bigArray.UnsignedChar();

	ba = new bigArray.Int();
	ba = new bigArray.UnsignedInt();

	ba = new bigArray.ShortInt();
	ba = new bigArray.ShortUnsignedInt();

	ba = new bigArray.LongInt();
	ba = new bigArray.LongUnsignedInt();

	ba = new bigArray.Float();

	ba = new bigArray.Double();

````

````javascript
	var bigArray = require('big-array'),
		trillion = 1000 * 1000 * 1000 * 1000,
		ba, i;

	ba = bigArray.UnsignedChar();
	// Unlike JavaScript, setting or getting a high index will result in the array allocating all elements before that index
	ba.set(trillion, 5);

````

Tip: When testing on Linux, use "ulimit -v" to limit the maximum memory consumption.

````bash
	# Limit memory usage to 10GB
	ulimit -v 10485760
````

Common methods

````javascript
	set(index, value)
	get(index)

	// inc/dec by 1
	inc(index)
	dec(index)

	push(value)
	pop()
	// modify push/pop index
	setIndex(index)
	getIndex()

	// resize array to [size]
	resize(size)
````
