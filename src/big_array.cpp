#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include <node.h>
#include "big_array.hpp"

using namespace v8;

void InitAll(Handle<Object> target) {
	// char types
	BigArray<char>::Init("Char", target);
	BigArray<unsigned char>::Init("UnsignedChar", target);

	// int types
	BigArray<int>::Init("Int", target);
	BigArray<unsigned int>::Init("UnsignedInt", target);

	BigArray<short int>::Init("ShortInt", target);
	BigArray<short unsigned int>::Init("ShortUnsignedInt", target);

	BigArray<long int>::Init("LongInt", target);
	BigArray<long unsigned int>::Init("LongUnsignedInt", target);

	// float type
	BigArray<float>::Init("Float", target);

	// double type
	BigArray<double>::Init("Double", target);
}

NODE_MODULE(big_array, InitAll)


