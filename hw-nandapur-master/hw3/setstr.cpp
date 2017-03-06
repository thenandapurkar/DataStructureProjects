#include "setstr.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>


/**
* Default constructor 
*/
SetStr::SetStr(){
	LListStr list_;
}

/**
* Destructor
*/
SetStr::~SetStr(){
	list_.~LListStr();
}

/**
* Returns the current number of items in the list 
*/
int SetStr::size() const{
	return list_.size();
}

/**
* Returns true if the list is empty, false otherwise
*/
bool SetStr::empty() const{
	return list_.empty();
}

/**
* Inserts val into the set, do nothing if val already exists
*/
void SetStr::insert(const std::string& val){
	if(exists(val)){}
	else{
		list_.push_back(val);
	}
}

/**
* Removes the value from the set, do nothing if it doesn't exist
*/
void SetStr::remove(const std::string& val){
	if(!exists(val)){}
	else{
		for(int i=0; i<list_.size(); i++){
  		if(val==list_.get(i)){
  			list_.remove(i);
  		}
		}
	}
}

/**
* Returns true if the item is in the set
*/
bool SetStr::exists(const std::string& val) const{
	for(int i=0; i<list_.size(); i++){
		if(val==list_.get(i)){
			return true;
		}
	}
	return false;
}

SetStr::SetStr(const SetStr& other){
	this->list_ = LListStr(other.list_);
}

SetStr& SetStr::operator=(const SetStr& other){
	this->list_=other.list_;
	return *this;
}





/**
* Return a pointer to the first item
*  and support future calls to next()
*/
std::string const* SetStr::first(){
	curr=0;
	if(empty()){
		return NULL;
	}

	return &(list_.get(0));	
}

/**
* Return a pointer to the next item
*  after the previous call to next
*  and NULL if you reach the end
*/
std::string const* SetStr::next(){
	if(curr==size()-1){
		return NULL;
	}
	return &(list_.get(++curr));
}

/**
* Returns another (new) set that contains
* the union of this set and "other"
*/
SetStr SetStr::setUnion(const SetStr& other) const{
	SetStr final = SetStr(*this);
	for(int i=0; i<other.list_.size(); i++){
		final.insert(other.list_.get(i));
	}
	return final;
}

/**
* Returns another (new) set that contains
* the intersection of this set and "other"
*/
SetStr SetStr::setIntersection(const SetStr& other) const{
	SetStr final = SetStr();
	for(int i=0; i<other.list_.size(); i++){
		if(this->exists(other.list_.get(i))){
			final.insert(other.list_.get(i));
		}
	}
	return final;
}


//same as union
SetStr SetStr::operator|(const SetStr& other) const{
	return this->setUnion(other);
}

//same a intersection
SetStr SetStr::operator&(const SetStr& other) const{
	return this->setIntersection(other);
}
