#include<stdlib.h>
#include<stdio.h>

size_t maxSeq(int *array,size_t n){
  if(n==0){
    return 0;
  }
  else{
    int max=1;
    int cur=1;
    for(int i=1;i<n;i++){
      if(array[i]>array[i-1]){
	cur++;
      }
      else{
	max=(cur>max) ? cur:max;
	cur=0;
      }
    }
     return max;
  }
 
}
