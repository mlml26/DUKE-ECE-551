#include "rand_story.h"
#include "stdio.h"
int main(int argc, char **argv){
  checkComLinArg(argc, 1);
  FILE *f = openCheckFile(argv[1]);
  //print words
  readCatWorFile(f);
  closeCheckFile(f);
  return EXIT_SUCCESS;
}
