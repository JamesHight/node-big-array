#ifndef big_array_hpp
#define big_array_hpp

#include <vector>
#include <node.h>
#include <v8.h>

using namespace v8;
using namespace std;


using namespace std;

template<typename DataType>
class BigArray : public node::ObjectWrap {
private:
	long unsigned int blockSize_;
	long unsigned int index_;
	vector< vector<DataType> > data;

	void grow_(long unsigned int size) {
		if (size > data.size()) {
			data.resize(size, vector<DataType>(this->blockSize_));
		}
	}


public:

	// ************************
	// v8 entry point for class
	// ************************

	static void Init(const char *name, Handle<Object> target){
		// Prepare constructor template
		Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
		tpl->SetClassName(String::NewSymbol(name));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);
		
		// Prototype
		tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
		FunctionTemplate::New(get)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("set"),
		FunctionTemplate::New(set)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("inc"),
		FunctionTemplate::New(inc)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("dec"),
		FunctionTemplate::New(dec)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("push"),
		FunctionTemplate::New(push)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("pop"),
		FunctionTemplate::New(pop)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("getIndex"),
		FunctionTemplate::New(get_index)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("setIndex"),
		FunctionTemplate::New(set_index)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("resize"),
		FunctionTemplate::New(resize)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("getSize"),
		FunctionTemplate::New(get_size)->GetFunction());

		tpl->PrototypeTemplate()->Set(String::NewSymbol("getBlockSize"),
		FunctionTemplate::New(get_block_size)->GetFunction());

		Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
		target->Set(String::NewSymbol(name), constructor);
	}

	static Handle<Value> New(const Arguments& args){
	    HandleScope scope;
	    BigArray<DataType> *ba;

	    long unsigned int size = 1;
	    long unsigned int blockSize = 1048576;

	    if (args.Length() > 0) {
	    	size = args[0]->NumberValue();
	    }

	    if (args.Length() > 1) {
	    	blockSize = args[1]->NumberValue();
	    }

	    ba = new BigArray<DataType>(size, blockSize);
	    ba->Wrap(args.This());

	    return args.This();
	}

	// ****************************
	// Static v8 wrappers for class
	// ****************************

	static Handle<Value> get(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int index = args[0]->NumberValue();

		try {
			return scope.Close(Number::New(that->get(index)));
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}
	}

	static Handle<Value> set(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int index = args[0]->NumberValue();

		if (!args[1]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("Second argument must be a number")));
		}
		DataType value = args[1]->NumberValue();

		try {
			that->set(index, value);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> inc(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());

		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int index = args[0]->NumberValue();
		
		try {
			that->inc(index);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> dec(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());

		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int index = args[0]->NumberValue();
		
		try {
			that->dec(index);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> push(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());

		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		DataType value = args[0]->NumberValue();
		
		try {
			that->push(value);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> pop(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		try {
			return scope.Close(Number::New(that->pop()));
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}
	}

	static Handle<Value> get_index(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		try {
			return scope.Close(Number::New(that->get_index()));
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}
	}

	static Handle<Value> set_index(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());

		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int index = args[0]->NumberValue();
		
		try {
			that->set_index(index);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> resize(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());

		if (!args[0]->IsNumber()) {
			return ThrowException(Exception::TypeError(String::New("First argument must be a number")));
		}
		long unsigned int size = args[0]->NumberValue();
		
		try {
			that->resize(size);
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}

		return scope.Close(Undefined());
	}

	static Handle<Value> get_size(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		try {
			return scope.Close(Number::New(that->get_size()));
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}
	}

	static Handle<Value> get_block_size(const Arguments& args) {
		HandleScope scope;

		BigArray<DataType>* that = ObjectWrap::Unwrap< BigArray<DataType> >(args.This());
		
		try {
			return scope.Close(Number::New(that->get_block_size()));
		}
		catch (bad_alloc& exc) {
			return ThrowException(Exception::TypeError(String::New("Cannot allocate more memory")));
		}
	}


	// *********************
	// Regular class members
	// *********************

	BigArray(long unsigned int size, long unsigned int blockSize) {	
		this->index_ = 0;
		this->blockSize_ = blockSize;
		this->resize(size);
	}

	DataType get(long unsigned int index) {
		long unsigned int i = index / this->blockSize_;
		long unsigned int j = index % this->blockSize_;
		
		// grow if out of range
		this->grow_(i + 1);			

		return data[i][j];
	}

	void set(long unsigned int index, DataType value) {
		long unsigned int i = index / this->blockSize_;
		long unsigned int j = index % this->blockSize_;

		// grow if out of range
		this->grow_(i + 1);

		data[i][j] = value;		
	}

	void inc(long unsigned int index) {
		long unsigned int i = index / this->blockSize_;
		long unsigned int j = index % this->blockSize_;

		// grow if out of range
		this->grow_(i + 1);

		data[i][j]++;
	}

	void dec(long unsigned int index) {
		long unsigned int i = index / this->blockSize_;
		long unsigned int j = index % this->blockSize_;

		// grow if out of range
		this->grow_(i + 1);

		data[i][j]--;
	}

	void push(DataType value) {
		this->set(this->index_, value);
		this->index_++;
	}

	DataType pop() {
		if (this->index_ > 0) {
			this->index_--;
		}

		DataType value = this->get(this->index_);

		this->set(this->index_, 0); // clear data
		this->resize(this->index_); // shrink if we can

		return value;
	}

	void set_index(long unsigned int index) {
		this->index_ = index;
	}

	long unsigned int get_index() {
		return this->index_;
	}

	void resize(long unsigned int size) {
		long unsigned int count = (size / this->blockSize_) + 1;
		
		data.resize(count, vector<DataType>(this->blockSize_));		
	}

	unsigned int get_size() {
		return data.size() * this->blockSize_;
	}

	unsigned int get_block_size() {
		return this->blockSize_;
	}

};

#endif