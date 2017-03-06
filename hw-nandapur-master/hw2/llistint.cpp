#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
  if(loc < 0 || loc > size_){
        throw std::invalid_argument("bad location");
    }
    Item *newnode = new Item;
    newnode->val = val;
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
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  if(loc < 0 || loc >= size_){
        throw std::invalid_argument("bad location");
    }
    if (loc == 0){
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

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
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
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
