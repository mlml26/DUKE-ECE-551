#include <assert.h>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include "function.h"

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

int binarySearchForZero(Function<int, int> * f, int low, int high);
class RealFunction: public Function<int, int>{
public:
  virtual int invoke(int arg){
    return arg;
  }
  
};

void check(Function<int,int> * f,
           int low,
	   int high,
	   int expected_ans,
	   const char * mesg){
  int max;
  if(high >low){
    max = log2(high - low) + 1;
  }
  else{
    max = 1;
  }
  CountedIntFn * w = new CountedIntFn(max, f, mesg);
  int ans = binarySearchForZero(w, low, high);
  assert(ans == expected_ans);
  delete w;
}

int main(void){
  RealFunction *a = new RealFunction();
  check(a, -2, 5, 0, "normal\n");
  check(a, -4, -1, -2, "All negative\n");
  check(a, 2, 5, 2, "All positive\n");
  check(a, -9, 0, -1, "exclusive 0\n");
  check(a, 0, 2, 0, "inclusive 0");
  delete a;
  return EXIT_SUCCESS;
  
}

