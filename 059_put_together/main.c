#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"
/*
void stripNewline(char *str){
  char *p=strchr(str,'\n');
  if(p!=NULL){
    *p='\0';
  }
}
*/
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t *c = createCounts();
  char *line =NULL;
  size_t sz=0;
  ssize_t len  = 0;
  FILE *f = fopen(filename,"r");
  while((len = getline(&line,&sz,f))>=0){
    stripNewline(line);
    addCount(c, lookupValue(kvPairs,line));
    line = NULL;
    /*
     char *p = strchr(line,'\n');
    size_t len = p - line;
    char *value = malloc((len+1)*sizeof(*value));
    strncpy(value,line,p-line);
    value[len]='\0';
    addCount(c,lookupValue(kvPairs,value));
    free(value);
    */
    line =NULL;
  }
  free(line);
  if(fclose(f)!=0){
    perror("Cannot close the file!");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc<3){
    perror("You should have 2 different types of input files");
    exit(EXIT_FAILURE);
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for(int i =2; i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t *c = countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE *f =fopen(outName,"w");
    
    //print the counts from c into the FILE f
    printCounts(c,f);
    
    //close f
    if(fclose(f)!=0){
      perror("Cannot close the file!");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
