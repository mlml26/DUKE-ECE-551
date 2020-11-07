#include "rand_story.h"
#include "stdio.h"
int main(int argc, char **argv){
  checkComLinArg(argc, 2);
  FILE *f = openCheckFile(argv[1]);
  FILE *w = openCheckFile(argv[2]);
  readCatWorFun(f, w, 0);
  closeCheckFile(f);
  closeCheckFile(w);
  return EXIT_SUCCESS;
}
