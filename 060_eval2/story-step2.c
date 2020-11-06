#include "rand_story.h"
#include "stdio.h"
int main(int argc, char **argv){
   if(argc != 2){
    error("can only take one command line argument!");
    }
   else{
    FILE *f = fopen(argv[1], "r");
    if(f == NULL){
      error("open file failed");
    }
    readFile(f);
    if(fclose(f) != 0){
      error("close file failed");
    }
   }
  return EXIT_SUCCESS;
}
