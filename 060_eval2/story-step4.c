#include "rand_story.h"
#include "stdio.h"
#include <string.h>
int main(int argc, char **argv){
  //check command line argument
  if(argc != 3 && argc != 4){
    error("invalid command line argument");
  }
  //check option -n
  char * a = "-n";
  if(argc == 4 && (strcmp(a, argv[1]) != 0)){
    error("optional command line wrong");
  }
  int option = (argc == 4)? 1 : 0; 
  FILE *f = openCheckFile(argv[1 + option]);
  FILE *w = openCheckFile(argv[2 + option]);
  //print the story
  readCatWorFun(f, w, option);
  closeCheckFile(f);
  closeCheckFile(w);
  return EXIT_SUCCESS;
}
