#include <cstdlib>
#include "assert.h"
#include "il.h"

void testList(void){
    IntList a;
  assert(a.head == NULL && a.tail == NULL && a.size == 0);

  a.addFront(1);
  assert(a[0] == 1 && a.getSize() == 1 && a.head->next == NULL && a.head->prev == NULL && a.tail == a.head && a.head->data == 1);

  a.addBack(3);
  assert(a[1] == 3 && a.getSize() ==2 && a.head->next == a.tail && a.tail->prev == a.head && a.tail->next == NULL);

  a.addBack(2);
  assert(a[2] == 2);
  //copy constructor
  IntList b(a);
  assert(b.getSize() == 3 && b[0]==1&&b[1]==3&&b[2]==2 && b.head->next->next == b.tail);
  //assignment
  IntList c = b;
  assert(b.getSize() == 3 && b[0]==1&&b[1]==3&&b[2]==2 && b.head->next->next == b.tail);
  
  //remove
  assert(a.remove(3)==1);
  assert(a[0] == 1 && a[1] == 2 && a.getSize() ==2 && a.head->next == a.tail);
  assert(a.remove(5)==false);
  a.remove(2);
  a.remove(1);
  assert(a.getSize()==0 && a.head == NULL && a.tail == NULL);

  //find
  assert(c.find(1)==0 && c.find(100) == -1 && c.find(2)==2);

  c.~IntList();
  
  //new
  
  IntList q;
  assert(q.head == NULL && q.tail == NULL && q.size == 0);
  q.addBack(10);
  assert(q.head->data==10&&q.tail->data==10&&q.size==1&&q.tail->next==NULL&&q.head->prev==NULL&&q.tail->prev==NULL&&q.head->next==NULL);
  q.addBack(3);
  assert(q.size==2);
  assert(q.head->data==10&&q.head->next->data==3);
  assert(q.tail->data==3&&q.head->next->next==NULL&&q.tail->prev->data==10);
  assert(q.head->prev==NULL&&q.tail->next==NULL&&q[1]==3);
  q.addFront(1);//1 10 3
  assert(q.size==3&&q.head->data==1&&q.head->next->data==10);
  assert(q.head->next->next->data==3&&q.head->next->next->next==NULL);
  assert(q.head->prev==NULL&&q.tail->next==NULL&&q[0]==1);
  q.addBack(5);
  q.addBack(7);//1 10 3 5 7
  //
  q.remove(10);
  assert(q.size == 4);
  assert(q.head->data == 1);
  assert(q.head->next->data == 3);
  assert(q.head->next->next->data == 5);
  assert(q.head->next->next->next->data == 7);
  assert(q.head->next->next->next->next == NULL);
  assert(q.tail->data == 7);
  assert(q.tail->prev->data == 5);
  assert(q.tail->prev->prev->data == 3);
  assert(q.tail->prev->prev->prev->data == 1);
  assert(q.tail->prev->prev->prev->prev == NULL);
  //1 3 5 7
  assert(q.getSize() == 4);
  int node5index = q.find(5);
  assert(node5index == 2);

  q.remove(5);  //1 3 7
  assert(q.head->next->data == 3);
  assert(q.tail->prev->data == 3);
  assert(q.getSize() == 3);
  assert(q[0] == 1);
  assert(q[1] == 3);
  assert(q[2] == 7);

  assert(q.find(1) == 0);

  //
  //assign
  IntList w;
  w = q;
  assert(w[0] == 1);
  assert(w[1] == 3);
  assert(w[2] == 7);
  assert(w.getSize() == 3);
  assert(w.head->prev == NULL);
  assert(w.head->data == 1);
  assert(w.head->next->data == 3);
  assert(w.head->next->next->data == 7);
  assert(w.tail->next == NULL);
  assert(w.tail->data == 7);
  assert(w.tail->prev->data == 3);
  assert(w.tail->prev->prev->data == 1);
  assert(w.tail->prev->prev->prev == NULL);
  assert(w.head->next->next == w.tail &&
         w.head->next->next->next == NULL);
  assert(w.tail->prev->prev == w.head);
  assert(w.head->next->prev == w.head);

  w.remove(3);
  assert(q.getSize() == 3);
  assert(w.remove(3) == false);

  //copy
  IntList x(q);
  assert(x[0] == 1);
  assert(x[1] == 3);
  assert(x[2] == 7);
  assert(x.getSize() == 3);
  assert(x.head->prev == NULL);
  assert(x.head->data == 1);
  assert(x.head->next->data == 3);
  assert(x.head->next->next->data == 7);
  assert(x.head->next->next->next == NULL);
  assert(x.tail->next == NULL);
  assert(x.tail->data == 7);
  assert(x.tail->prev->data == 3);
  assert(x.tail->prev->prev->data == 1);
  assert(x.tail->prev->prev->prev == NULL);
  assert(x.head->next->next == x.tail &&
         x.head->next->next->next == NULL);
  assert(x.tail->prev->prev == x.head);
  assert(x.head->next->prev == x.head);

  x.remove(3);
  assert(q.getSize() == 3);
  assert(x.head->next == x.tail);
  assert(x.tail->prev == x.head);
  assert(x.tail->prev->next == x.tail);
  x.~IntList();
 
 
}

int main(void){
  testList();
  return EXIT_SUCCESS;
}
