#include "stackint.h"
#include <cstdlib>
#include <stdexcept>
 
 
StackInt::StackInt() {
    LListInt list_;
}
 
StackInt::~StackInt() {  
    list_.~LListInt(); 
}
 
bool StackInt::empty() const {
    return list_.empty();
}
 
void StackInt::push(const int& val) {
    list_.insert(list_.size(),val);
}
 
int const & StackInt::top() const {
    return list_.get(list_.size()-1);
}
 
void StackInt::pop() {
    list_.remove(list_.size()-1);
}