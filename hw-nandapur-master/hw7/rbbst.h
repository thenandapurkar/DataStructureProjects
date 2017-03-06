/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }

  //added accessors for ease of access made virtual so can be accessed by the tree  
  virtual RedBlackNode<KeyType, ValueType> *getGrandparent() const{
    if (this->getParent() == NULL){
      return NULL;
    }
    else{
      return (RedBlackNode<KeyType, ValueType>*) this->getParent()->getParent();
    }
  }

  //Get Aunt/Uncle
  virtual RedBlackNode<KeyType, ValueType> *getAunt() const{
    if (this->getGrandparent() == NULL){
      return NULL;
    }
    if (this->getParent() == this->getGrandparent()->getRight()){
      return (RedBlackNode<KeyType, ValueType>*) this->getGrandparent()->getLeft();
    }
    else{
      return (RedBlackNode<KeyType, ValueType>*) this->getGrandparent()->getRight();
    }
  }
  
 protected:
  Color color;
  //Get Grandparent
  

};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item){
    //in order to pass the node through fixTree operations must return it
    insertNode((RedBlackNode<KeyType, ValueType>*)(this->root), NULL, new_item);
    //Trigger for all cases
    //set a red black node to the inserted one that was searched for
    RedBlackNode<KeyType, ValueType>* go = (RedBlackNode<KeyType, ValueType>*)(this->internalFind(new_item.first));
    treeFix(go);
  }
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */

  //1. Insert node into normal BST location (at a leaf location) and color it RED
     
  

private:
  void insertNode(RedBlackNode<KeyType, ValueType>* root, 
                  RedBlackNode<KeyType, ValueType>* parent, 
                  const std::pair<const KeyType, ValueType>& new_item){
    RedBlackNode<KeyType, ValueType>* first = NULL;
    if(root==NULL && parent==NULL){
      //if BST is empty
      first = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      this->root=first;
      
    }
    else if(root==NULL && parent!=NULL){
      //this represents you on a null leaf currently
      first = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, parent);
      first->setParent(parent);
      if(first->getKey()<parent->getKey()){
        parent->setLeft(first);
      }
      else{
        parent->setRight(first);
      }
      
    }
    else if(new_item.first<root->getKey()){
      //insert to left side
      insertNode(root->getLeft(),root, new_item);
    }
    else if(new_item.first > root->getKey()){
      //insert to right side
      insertNode(root->getRight(),root, new_item);
    }
    else{
      //if equal
      root->setValue(new_item.second);
    }
    
  }

  
  //if this node is the root
  void treeFix(RedBlackNode<KeyType, ValueType>* node){
    
    //if just root, set it to black
    if (node->getParent() == NULL) {
      node->setColor(black);
    } 
    else {
      //Set family variables for ease of access
      RedBlackNode<KeyType, ValueType>* parent = node->getParent();
      RedBlackNode<KeyType, ValueType>* aunt = node->getAunt();
      RedBlackNode<KeyType, ValueType>* grandma = node->getGrandparent();
      if (parent->getColor() == black){
        return; // if parent is already black nothing to be done except break
      }
      else{
        if (aunt!=NULL && aunt->getColor() == red){
          parent->setColor(black);
          aunt->setColor(black);
          grandma->setColor(red);
          //**3rd case where we have to go back and recolor root 
          treeFix(grandma);
        } 
        else {
          if(node==parent->getRight() && parent==grandma->getLeft()){
            leftRotation(parent);
            node = node->getLeft();
          } 
          else if(node==parent->getLeft() && parent==grandma->getRight()){
            rightRotation(parent);
            node = node->getRight();
          }
          //both children of every red node are not black yet

          //RESET Variables as node was modified!!
          RedBlackNode<KeyType, ValueType>* new_parent = node->getParent();
          RedBlackNode<KeyType, ValueType>* new_grandma = node->getGrandparent();

          //Appropriately change coloring
          new_parent->setColor(black);
          new_grandma->setColor(red);

          //perform the necessary rotation
          if(node==new_parent->getLeft()){
            rightRotation(new_grandma);
          }
          else{
            leftRotation(new_grandma);
          }
        }
      }
    }
  }
  void leftRotation(RedBlackNode<KeyType, ValueType>* node) {
    //set necessary variables 
    RedBlackNode<KeyType, ValueType>* toRight = node->getRight();
    RedBlackNode<KeyType, ValueType>* parent = node->getParent();

    //manipulate the values here
    node->setRight(toRight->getLeft());
    if (toRight->getLeft()!=NULL) {
        toRight->getLeft()->setParent(node);
    }
    toRight->setParent(parent);
    if (parent== NULL) {
      this->root=toRight;
    } 
    else{
      if(node==parent->getLeft()){
        parent->setLeft(toRight);
      }
      else{
        parent->setRight(toRight);
      }
    }
    toRight->setLeft(node);
    node->setParent(toRight);
  }
  void rightRotation(RedBlackNode<KeyType, ValueType>* node){
    //set necessary variables 
    RedBlackNode<KeyType, ValueType>* toLeft = node->getLeft();
    RedBlackNode<KeyType, ValueType>* parent = node->getParent();

    //manipulate the values here
    node->setLeft(toLeft->getRight());
    if(toLeft->getRight()!=NULL){
      toLeft->getRight()->setParent(node);
    }
    toLeft->setParent(parent);
    if(parent==NULL){
      this->root = toLeft;
    }
    else{
      if(node==parent->getLeft()){
        parent->setLeft(toLeft);
      } 
      else{
        parent->setRight(toLeft);
      }
    }
    toLeft->setRight(node);
    node->setParent(toLeft);
  }
};
#endif
