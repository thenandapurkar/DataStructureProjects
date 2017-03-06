#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
template <typename T, typename PComp, typename KComp >
class Heap
{
 public:
   /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComp c = PComp(), KComp k = KComp());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  /// updates the key to a "better" priority
  void updated_key(const T& item, const T& new_val);

  bool contains_key(const T& item);

  int getSize();

  

  

 private:
  /// Add whatever helper functions and data members you need below
  
  std::vector<T> _store;
  int _m;
  PComp _c;
  KComp _k;

  void trickleUp(int loc);
  void heapify(int idx);
  

  
};

template <typename T, typename PComp, typename KComp>
  Heap<T,PComp,KComp>::Heap(int m, PComp c, KComp k) : 
    _store(),
    _m(m),
    _c(c),
    _k(k)
{
  
}

template <typename T, typename PComp, typename KComp>
Heap<T,PComp,KComp>::~Heap()
{
  
}

template <typename T, typename PComp, typename KComp>
int Heap<T,PComp,KComp>::getSize(){
  return _store.size();
}

/// child at p @ m*p + 1 to m*p + m
/// parent at (c-1)/m
template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::push(const T& item)
{ 
  // std::cout << "Heap: Size Updated Before push-back: " << _store.size() << std::endl;
  _store.push_back(item);
  //std::cout << "Heap: Size Updated after push-back: " << _store.size() << std::endl;
  //trickle up with the new value
  trickleUp(_store.size()-1);
  //std::cout << "Heap: Size Updated after trickleup: " << _store.size() << std::endl;
}

template <typename T, typename PComp, typename KComp>
bool Heap<T,PComp,KComp>::contains_key(const T& item){
  bool istrue = false;
  for(int i=0; i<_store.size(); i++){
    if(!_k(_store[i],item) && !_k(item,_store[i])){
      istrue = true;
      return istrue;
    }
  }
  return istrue;
}

template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::updated_key(const T& item, const T& new_val){
  for(int i=0; i<_store.size(); i++){
    if(!_k(_store[i],item) && !_k(item,_store[i])){
      _store[i]=new_val;
      trickleUp(i);
    }
  }
}

template <typename T, typename PComp, typename KComp>
T const & Heap<T,PComp,KComp>::top() const{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _store[0];
}

/// Removes the top element
template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::pop(){
  //std::cout<<"Heap Size before pop: " << _store.size() << std::endl;
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  // complete the code here

  _store[0] = _store[_store.size()-1];
  _store.pop_back();
  heapify(0);
}
/// returns true if the heap is empty
template <typename T, typename PComp, typename KComp>
bool Heap<T,PComp,KComp>::empty() const{
  return _store.empty();
}

template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::trickleUp(int loc){
  int parent = (loc-1)/_m;
  while(parent >= 0 && _c(_store[loc],_store[parent])){
   std::swap(_store[parent],_store[loc]);
   loc = parent;
   parent = loc/2;
  }
}

template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::heapify(int idx){
  if(idx>((_store.size()/2)+1) && idx < _store.size()){ //leaf node
    return;
  }
  if ((_store.size()> _m*idx+1)){
    int smallerChild = _m * idx+1; //start w/ left
    for (int i=2; i<= _m; i++){ //optimize for multiple m sizes then run algorithm
      if (_m*idx + i<_store.size()){
        int rChild=_m*idx+i;
        if (_c(_store[rChild], _store[smallerChild])){
          smallerChild = rChild;
        }
      }
    }

    if (_c(_store[smallerChild],_store[idx]))
    {
      std::swap(_store[idx], _store[smallerChild]);
      heapify(smallerChild);

    }

  }
}



#endif

