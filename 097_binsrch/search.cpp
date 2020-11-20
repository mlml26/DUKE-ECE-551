#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high){
  //all negative
  /*
  if(f->invoke(high - 1) < 0){
    return high - 1;
  }
  //all positive
  if(f->invoke(low) > 0){
    return low;
  }
  if(low == high){
    return low;
  }
  //int cur = ((high - low) / 2) + low;
  */  
/*
  int cur = (hight + low - 1) / 2;
  if(f->invoke(cur) > 0){
    return binarySearchForZero(f, low, cur);
  }
  else if(f->invoke(cur) < 0){
    return binarySearchForZero(f, cur, high);
  }
  else{
    return cur;
  }
  */
  while(low+1 < high){ 
    int cur = (high + low) / 2;
    int ans = f->invoke(cur);
    if(ans == 0){
      return cur;
    }
    if(ans > 0){
      high = cur;
    }
    else{
      low = cur;
    }
  }
  return low;
}
