#include "bstmap.h"
#include "map.h"
#include <cstdlib>
#include <assert.h>
#include <cstdio>
int main(void){
  BstMap<int, int> map;
  map.add(60,1);
  assert(map.root->value==1);
  assert(map.root->key == 60);

  map.add(1,2);
  assert(map.root->left->key ==1);
  assert(map.root->left->value ==2);

  map.add(61,3);
  assert(map.root->right->key ==61);

  map.add(0,5);
  int a=map.lookup(0);
  assert(a==5);

  map.add(2,8);
  
  map.remove(60);
  assert(map.root->key == 2);
  assert(map.root->left->right==NULL);
  
  printf("succed\n");
  /*
  map.remove(0);
  assert(map.root->left->left == NULL);
  */  
return EXIT_SUCCESS;
}
