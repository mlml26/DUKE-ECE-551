#include "node.h"
#include<stdio.h>
#include<cstdio>
Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for(int i =0; i<257;i++){
    if(counts[i] !=0){
      pq.push(new Node(i, counts[i]));
    }
  }
  while(pq.size()!=1){
    Node * nodeOne = pq.top();
    pq.pop();
    Node * nodeTwo = pq.top();
    pq.pop();
    Node * combine = new Node(nodeOne, nodeTwo);
    pq.push(combine);
  }
  Node * root = pq.top();
  pq.pop();
  return root;
}  
