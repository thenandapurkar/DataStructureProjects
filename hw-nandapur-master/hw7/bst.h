/**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */
#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for Red-Black-Trees,
     we'll want to use Red-Black nodes, and for those, the 
     getParent, getLeft, and getRight functions should return 
     Red-Black nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () { root = NULL; }

  /**
   * Destructor
   */
  ~BinarySearchTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  //Add a function to support printing for test file
  void makeTree(Node<KeyType,ValueType> *top) {
      root=top;
  }
    
  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node<KeyType,ValueType>* ptr){
      curr=ptr;
      //curr->setParent(NULL);
      //std::cout << curr->getLeft()->getKey() << std::endl;
      while(curr!= NULL && curr->getLeft()!=NULL){

        curr=curr->getLeft();
      }
      //std::cout << "Key #" << curr->getKey() << std::endl;

    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const{
      // std::cout << "MAde it inside the ==" << std::endl;
      if(curr==NULL && rhs.curr==NULL){
        return true;
      }
      else if(curr==NULL||rhs.curr==NULL){
        return false;
      }
      else{
        // std::cout << "Condition comparison" << curr->getKey() << std::endl;
        return curr->getKey()==rhs.curr->getKey();
      }//return (this->getKey() == rhs->getKey() && this->getValue()==rhs->getValue());
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const{
      if(curr==NULL && rhs.curr==NULL){
        return false;
      }
      else if(curr==NULL || rhs.curr==NULL){
        return true;
      }
      else{
        return curr->getKey()!=rhs.curr->getKey();
      }
     //return (this->getKey()!=rhs->getKey() && 
      //  this->getValue()!=rhs->getValue());
    }
    
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    
    iterator& operator++(){
      getSuccessor();
      //std::cout << "Got Past successor" << std::endl;
      return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;
    //you are welcome to add any necessary variables and helper functions here.
    void getSuccessor(){
      //Check for curr->getRight() if exists set curr to getRight()
      //getLeft and then getRight
      //Check for parent
      std::cout << "Inside successor" << std::endl;
      Node<KeyType, ValueType>* g = NULL;

      std::cout << "Curr->Key: " << curr->getKey() << std::endl;
      //std::cout << "Parent->left->key" << curr->getParent()->getLeft()->getKey() << std::endl;
      // if(curr->getKey() == curr->getParent()->getLeft()->getKey()){
      //   std::cout << "They were equal" << std::endl;
      // }
      
      if(curr->getRight()!=NULL){
         //std::cout << "First case" << std::endl;
        curr=curr->getRight();
        while(curr->getLeft()!=NULL){
          curr = curr->getLeft();
        }
        //std::cout << curr->getKey() << std::endl;
      }
      else if(curr->getParent() != NULL && curr->getRight()==NULL){
        if(curr->getRight()==NULL && curr->getKey() == curr->getParent()->getLeft()->getKey()){
           //std::cout << "Entered else if" << curr->getKey() << std::endl;
          curr = curr->getParent();
        }
        else{
          //std::cout << "in else" << std::endl;
          //as to not change the value of root 
          // std::cout << "Curr->Parent" << curr->getParent()->getKey() << std::endl;
          // std::cout << "Curr->Parent-> Right" << curr->getParent()->getRight()->getKey() << std::endl;
          while(curr->getParent()!=NULL && curr->getKey()==curr->getParent()->getRight()->getKey()){
            //std::cout << "Entered inner while for successor" << std::endl;
            curr=curr->getParent();
            g=curr->getParent(); 
          }
         // std::cout << "Made it out of inner while loop for successor" << std::endl;
          // if(g==NULL){
          // //  std::cout << "g made it to NULL" << std::endl;
          // }
          curr = g;
          // if(curr==NULL){
          //  // std::cout << "curr made it to NULL" << std::endl;
          // }

          //std::cout <<"After Else Statement in Successor"  << std::endl;
        }
      }
      //curr=g;

      }
  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin(){
    iterator start(root);
    //std::cout << "Returning Start " << start->first << std::endl;
    return start;
  } 

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end(){
    iterator finish(NULL);
    //std::cout << "Returning End" << std::endl; 
    return finish;
  } 

  /**
   * Returns an iterator to the item with the given key, k
   * or the end iterator if k does not exist in the tree
   */
  iterator find (const KeyType & k) const 
  {
    Node<KeyType, ValueType> *curr = internalFind(k);
    iterator it(curr);
    return it;
  }
  
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }
};

/* Feel free to add member function definitions here if you need */

#endif
