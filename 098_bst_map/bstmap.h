#include "map.h"
#include <exception>
#include <cstdlib>
template<typename K, typename V>
class BstMap: public Map<K, V>{
 private:
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
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K& key) const throw (std::invalid_argument);
  virtual void remove(const K& key);
  virtual ~BstMap<K,V>();
  void destroy(Node *cur);
};

//add
template<typename K, typename V>
void BstMap<K,V>::add(const K & key, const V & value){
  Node ** cur = &root;
  while(*cur != NULL){
    if(key < (*cur)->key){
      cur = &(*cur)->left;
    }
    else if(key == (*cur)->key){
      (*cur)->value = key;
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
