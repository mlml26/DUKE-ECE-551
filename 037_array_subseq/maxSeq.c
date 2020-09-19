#include<stdlib.h>
#include<stdio.h>

size_t maxSeq(int *array,size_t n){
  if(n==0){
    return 0;
  }
  else{
    size_t max=1;
    size_t cur=1;
    for(size_t i=1;i<n;i++){
      if(array[i]>array[i-1]){
	cur++;
      }
      else{
	max=(cur>max) ? cur:max;
	cur=1;
      }
    }
     return max;
  }
 
}
