#include "lliststr.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

//Constructor
LListStr::LListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

//Destructor
LListStr::~LListStr()
{
  clear();
}

bool LListStr::empty() const
{
  return size_ == 0;
}

int LListStr::size() const
{
  return size_;
}

/**
 * insert
 */
void LListStr::insert(int loc, const string& val)
{
  if(loc < 0 || loc > size_){
        throw std::invalid_argument("bad location");
    }
    Item *newnode = new Item;
    newnode->val = val;

    //check all cases
    if (head_ == NULL){
        newnode->next = NULL;
        newnode->prev = NULL;
        head_ = newnode;
        tail_ = newnode;
    }
    else if (loc == 0){
        newnode->next = head_;
        newnode->prev = NULL;
        head_->prev = newnode;
        head_ = newnode;
    }
    else if (loc == size_){
        newnode->next = NULL;
        newnode->prev = tail_;
        tail_->next = newnode;
        tail_ = newnode;
    }
    else {
        Item *thisloc = getNodeAt(loc);
        Item *prevloc = getNodeAt(loc-1);
        thisloc->prev = newnode;
        newnode->next = thisloc;
        newnode->prev = prevloc;
        prevloc->next = newnode;
    }
    size_++;
}

/**
 *
 */
void LListStr::remove(int loc)
{
    if(loc < 0 || loc >= size_){
        throw std::invalid_argument("bad location");
    }
    if (loc==0 && size_ == 1){
      delete head_;
      head_=NULL;
      tail_=NULL;
    }
   else if (loc == 0){
        Item *temp = head_->next;
        delete head_;
        head_ = temp;
    }
    else if (loc == size_-1){
        Item *temp = tail_->prev;
        delete tail_;
        tail_ = temp;
    }
    else {
        Item *thisloc = getNodeAt(loc);
        Item *prevloc = getNodeAt(loc-1);
        Item *nextloc = getNodeAt(loc+1);
        delete thisloc;
        prevloc->next = nextloc;
        nextloc->prev = prevloc;
    }
    size_--;
}

void LListStr::set(int loc, const string& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

string& LListStr::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

string const & LListStr::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListStr::Item* LListStr::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    return NULL;
  }
}

void LListStr::push_back(const string& val){
  Item *newnode = new Item;
  newnode->val = val;

  //add if at the beginning
  if(size_ == 0){
    newnode->prev = tail_; // Since tail == nullptr, newNode->prev will be = to nullptr as well
    head_ = newnode;
    tail_ = newnode;
  }

  //add to the end
  else{
    newnode->next = NULL;
    newnode->prev = tail_;
    tail_->next = newnode;
    tail_ = newnode;
  }
  size_++;
}

//copy constructor
LListStr::LListStr(const LListStr& other){
  size_ = 0;
  head_ = NULL;
  tail_ = NULL;
  Item *temp=other.head_;
  while(temp!=NULL){
    push_back(temp->val);
    temp=temp->next;
}}

  /**
   * Assignment Operator
   */
LListStr& LListStr::operator=(const LListStr& other){
  clear();
  Item *temp=other.head_;

  while(temp!=NULL){
    push_back(temp->val);
    temp=temp->next;
  }
  return *this;
}
