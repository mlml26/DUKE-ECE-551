#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t *myCounts = malloc(sizeof(*myCounts));
  myCounts->sizeArray = 0;
  myCounts->unknown = 0;
  myCounts->array = NULL;
  return myCounts;
}
void add(counts_t * c, const char * name) {
  //WRITE ME
  c->sizeArray++;
  c->array = realloc(c->array,c->sizeArray*sizeof(*c->array));
  c->array[c->sizeArray -1] = malloc(sizeof(*c->array[c->sizeArray -1]));
  c->array[c->sizeArray-1]->string = malloc((strlen(name)+1)*sizeof(*c->array[c->sizeArray-1]->string));
  strcpy(c->array[c->sizeArray-1]->string,name);
  c->array[c->sizeArray- 1]->numTimes = 1;
}
void addCount(counts_t * c, const char * name){
  size_t flag=0;
  if(name==NULL){
    c->unknown++;
    return;
    }
  
  for(size_t i=0; i<c->sizeArray;i++){
    if(strcmp(c->array[i]->string, name)==0){
      c->array[i]->numTimes++;
      flag = 1;
      break;
    }
  }
  if(flag == 0){
    add(c, name);
  }
  
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i=0; i< c->sizeArray;i++){
    fprintf(outFile,"%s: %zd\n",c->array[i]->string,c->array[i]->numTimes);
  }
  if(c->unknown >0){
    fprintf(outFile,"<unknown> : %zd\n",c->unknown);
  }
  
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0; i<c->sizeArray;i++){
    free(c->array[i]->string);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
