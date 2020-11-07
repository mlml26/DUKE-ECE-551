#include "rand_story.h"
#include "stdio.h"
#include <string.h>
int main(int argc, char **argv){
  if(argc != 3 && argc != 4){
    error("invalid command line argument");
  }
  char * a = "-n";
  if(argc == 4 && (strcmp(a, argv[1]) != 0)){
    error("optional command line wrong");
  }
  int option = (argc == 4)? 1 : 0; 
  FILE *f = openCheckFile(argv[1 + option]);
  FILE *w = openCheckFile(argv[2 + option]);
  readCatWorFun(f, w, option);
  closeCheckFile(f);
  closeCheckFile(w);
  return EXIT_SUCCESS;
}
