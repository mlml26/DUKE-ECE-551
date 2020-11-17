#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>

class Error: public std::exception{
 public:
  virtual const char * what() const throw(){
    return "Requested item does not exist";
  }
};

template<typename T>
class LinkedList{
 private:
  class Node{
  public:
    T data;
    Node * next;
    Node * prev;
    Node(): data(0), next(NULL), prev(NULL){};
    Node(T d, Node *n, Node *p): data(d), next(n), prev(p){};
  };
  Node *head;
  Node *tail;
  int size;

 public:
  LinkedList(): head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  
  void addFront(const T &item);
  void addBack(const T &item);
  bool remove(const T &item);
  T& operator[](int index);
  const T& operator[](int index) const;
  int find(const T &item);
  int getSize() const;
  
};

//copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList &rhs): head(NULL), tail(NULL), size(rhs.size){
  Node *c = rhs.head;
  while(c != NULL){
    addBack(c->data);
    c = c->next;
  }
}

//assignment operator
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs){
  if(this!=&rhs){
    LinkedList<T> tmp(rhs);
    Node *original_head = head;
    head = tmp.head;
    tmp.head = original_head;
    Node *original_tail = tail;
    tail = tmp.tail;
    tmp.tail = original_tail;
    size = tmp.size;
  }
  return *this;
}
  
//destructor
template<typename T>
LinkedList<T>::~LinkedList(){
  while(head != NULL){
    Node *temp = head->next;
    delete head;
    head = temp;
  }
  head = NULL;
  tail = NULL;
  size = 0;
}

//addFront
template<typename T>
void LinkedList<T>::addFront(const T &item){
  head = new Node(item, head, NULL);
  size++;
  if(tail==NULL){
    tail = head;
  }
  else{
    head->next->prev = head;
  }
}

//addBack
template<typename T>
void LinkedList<T>::addBack(const T &item){
  tail = new Node(item, NULL, tail);
  size++;
  if(head ==NULL){
    head = tail;
  }
  else{
    tail->prev->next = tail;
  }
}

//remove
/*
template<typename T>
bool LinkedList<T>::remove(const T &item){
  Node **cur =&head;
  while(*cur!=NULL && (*cur)->data != item){
    cur = &(*cur)->next;
  }
  if(*cur == NULL){
    return false;
  }
  else{
    if(*cur == tail){
      tail = tail->prev; //update tail
    }
    else{
      (*cur)->next->prev = *cur; //update prev
    }
    //update next and delete
    *cur = (*cur)->next;
    delete *cur;
    size--;
  }
  return true;
}
*/

//remove new
template<typename T>
bool LinkedList<T>::remove(const T & item) {
  if (head == NULL) {
    return false;
  }
  else {
    Node * p = head;
    while (p != NULL) {
      if (p->data != item) {
        p = p->next;
      }
      else {
        if (head == tail && tail == p) {
          head = tail = NULL;
        }
        else if (tail == p) {
          tail = p->prev;
          tail->next = NULL;
        }
        else if (head == p) {
          head = p->next;
          head->prev = NULL;
        }
        else {
          p->prev->next = p->next;
          p->next->prev = p->prev;
        }
        delete p;
        size--;
        return true;
      }
    }
    return false;
  }
}

//[]
template<typename T>
T & LinkedList<T>::operator[](int index){
  if(index >= size){
    throw Error();
  }
  Node *cur = head;
  for(int i = 0; i < index;i++){
    cur = cur->next;
  }
  return cur->data;
}

//const []
template<typename T>
const T & LinkedList<T>::operator[](int index) const{
  if(index >= size){
    throw Error();
  }
  Node *cur = head;
  for(int i = 0; i < index;i++){
    cur = cur->next;
  }
  return cur->data;
}

//find
template<typename T>
int LinkedList<T>::find(const T &item){
  Node **cur = &head;
  int i = 0;
  while(*cur!=NULL && (*cur)->data!=item){
    cur = &(*cur)->next;
    i++;
  }
  if(*cur==NULL){
    return -1;
  }
  else{
    return i;
  }
}

//getSize
template<typename T>
int LinkedList<T>::getSize() const{
  return size;
}
#endif
