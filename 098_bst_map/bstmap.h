#include "map.h"
#include <exception>
#include <cstdlib>

template<typename K, typename V>
class BstMap: public Map<K, V>{
 public:
  class Node{
  public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node():left(NULL), right(NULL){};
    Node(K k, V v): key(k), value(v), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstMap(): root(NULL){};
  BstMap(const BstMap & rhs);
  BstMap & operator=(const BstMap & rhs);
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K& key) const throw (std::invalid_argument);
  virtual void remove(const K& key);
  //Node *copy(Node *current);
  Node *copy(Node * cur);
  virtual ~BstMap();
  void destroy(Node *cur);
  Node *addnode(Node* current, const K &key, const V &value);
};
//copy constructor
template<typename K, typename V>
BstMap<K,V>::BstMap(const BstMap & rhs){
  root = copy(rhs.root);
}

//copy constructor helper function
template<typename K, typename V>
typename BstMap<K,V>::Node * BstMap<K,V>::copy(Node * cur){
  if(cur != NULL){
    Node * myNode = new Node(cur->key,cur->value);
    myNode->left = copy(cur->left);
    myNode->right = copy(cur->right);
    return myNode;
  }
  return NULL;
}
/*
//copy constructor
template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap & rhs) {
  root = copy(rhs.root);
}
//copy helper function
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::copy(Node * current) {
  if (current == NULL) {
    return NULL;
  }
  Node * mynode = new Node(current->key, current->value);
  mynode->left = copy(current->left);
  mynode->right = copy(current->right);
  return mynode;
}
*/

//assignment operator
template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap & rhs) {
  if (this != &rhs) {
    BstMap<K, V> tmp(rhs);
    std::swap(root, tmp.root);
  }
  return *this;
}


//add
template<typename K, typename V>
void BstMap<K,V>::add(const K & key, const V & value){
  Node ** cur = &root;
  while(*cur != NULL){
    if(key < (*cur)->key){
      cur = &(*cur)->left;
    }
    else if(key == (*cur)->key){
      (*cur)->value = value;
      return;
    }
    else{
      cur = &(*cur)->right;
    }
  }
  *cur = new Node(key, value);
}

//lookup
template<typename K, typename V>
const V & BstMap<K,V>::lookup(const K& key) const throw (std::invalid_argument){
  Node *cur = root;
  while(cur != NULL){
    if(cur->key == key){
      return cur->value;
    }
    else if(key < cur->key){
      cur = cur->left;
    }
    else{
      cur = cur->right;
    }
  }
  throw std::invalid_argument("key not find\n");
}


//remove
template<typename K, typename V>
void BstMap<K,V>::remove(const K& key){
  Node ** cur = &root;
  while(*cur != NULL){
    if(key < (*cur)->key){
      cur = &(*cur)->left;
    }
    else if(key > (*cur)->key){
      cur = &(*cur)->right;
    }
    else{
      if((*cur)->right == NULL){
	Node * temp = *cur;
	*cur = (*cur)->left;
	delete temp;
      }
      else if((*cur)->left == NULL){
	Node *temp = *cur;
	*cur = (*cur)->right;
	delete temp;
      }
      else{
	Node * app = (*cur)->left;
	while(app->right != NULL){
	  app = app->right;
	}
	K appkey = app->key;
	V appvalue = app->value;
	remove(appkey);
	(*cur)->key = appkey;
	(*cur)->value = appvalue;
      }
      break;
    }
  }
}


//destructor
template<typename K, typename V>
BstMap<K,V>::~BstMap(){
  destroy(root);
}

//destructor helper function
template<typename K,typename V>
void BstMap<K,V>::destroy(Node *cur){
  if(cur != NULL){
    destroy(cur->left);
    destroy(cur->right);
    delete cur;
  }
}
