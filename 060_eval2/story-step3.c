#include "rand_story.h"
#include "stdio.h"
int main(int argc, char **argv){
  if(argc != 3){
    error("can only take two command line argument!");
    }
  else{
    FILE *f = fopen(argv[1], "r");
    if(f == NULL){
      error("open file failed");
    }
    FILE *w = fopen(argv[2], "r");
    if(w == NULL){
      error("open file failed");
    }
    readFileStep3(f, w);
    if(fclose(f) != 0){
      error("close file failed");
    }
    //parseLineStep3(w,);
    if(fclose(w) != 0){
      error("close file failed");
    }
  }
  return EXIT_SUCCESS;
}
