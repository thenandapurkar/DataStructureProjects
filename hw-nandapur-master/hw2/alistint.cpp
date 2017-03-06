#include "alistint.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
AListInt::AListInt() {
    _size=0;
    _capacity=10;
    int* temp = new int[_capacity];
    data = temp;
}

AListInt::AListInt(int cap) {
    _capacity = cap;
    _size=0;
    int* temp = new int[_capacity];
    data=temp;
}

AListInt::~AListInt() {
    delete[] data;
    _size=0;
    _capacity=10;
    data=NULL;

}

int AListInt::size() const {
   return _size;
}

bool AListInt::empty() const {
    return _size == 0;
}

void AListInt::set (int position, const int& val) {
    if(position < 0 || position >= _size){
        throw std::invalid_argument("bad location");
    }
    data[position] = val;
}

int& AListInt::get (int position) {
    if(position < 0 || position >= _size){
        throw std::invalid_argument("bad location");
    }

    return data[position];
}

// this is the CONST version of get()
int const & AListInt::get (int position) const {
    if(position < 0 || position >= _size){
        throw std::invalid_argument("bad location");
    }
    return data[position];
}
//

void AListInt::insert (int pos, const int& val) {
    if(pos < 0 || pos > _size){
        throw std::invalid_argument("bad location");
    }
    if(_size >= _capacity){
        resize();
    }
    for(int i=pos+1; i<=_size; i++){
        data[i]=data[pos];
    }
    data[pos]=val;
    _size++;
}

void AListInt::remove (int pos) {
    if(pos < 0 || pos >= _size){
        throw std::invalid_argument("bad location");
    }
    for (int i=pos; i<_size; i++) {
        data[i] = data[i+1];
    }
    _size--;
}

void AListInt::resize() {
    if (_size < _capacity) { return; }
    int *tmp;
    tmp = new int[_capacity*2]; 
    for (int i=0; i<_size; i++) {
        tmp[i] = data[i];
    }
    if (data != NULL) { delete [] data; }
    _capacity = _capacity*2;
    data = tmp;
}

