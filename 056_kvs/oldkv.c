#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include <ctype.h>
void stripNewline(char *str){
  char *p=strchr(str,'\n');
  if(p!=NULL){
    *p='\0';
  }
}
kvpair_t *splitOnepair(char *str){
  kvpair_t *p = malloc(sizeof(*p));
  char *f = strtok(str, "=");
  if(f == NULL){
    perror("Invalid first type of input file");
    return NULL;
  }
  p->key =malloc((strlen(f)+1)* sizeof(*p->key));
  p->key = f;
  char *l = strtok(NULL,"\0");
  p->value = malloc((strlen(l)+1)* sizeof(*p->value));
  p->value = l;
  return p;
}
kvarray_t *splitAllpairs(char **a, size_t length){
  kvarray_t *kva = malloc(sizeof(*kva));
  kva->pairs = malloc(length * sizeof(*kva->pairs));
  for(size_t i=0; i<length;i++){
    kva->pairs[i]=splitOnepair(a[i]);
    // free(a[i]);
  }
  kva->numPairs = length;
  return kva;
}
kvarray_t *readFile(FILE *f){
  kvarray_t *kva;
  char **lines = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i =0;
  // kvarray_t *a = malloc(sizeof(*a));
  while(getline(&cur, &sz, f)>=0){
    lines = realloc(lines, (i+1)*sizeof(*lines));
    stripNewline(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  kva=splitAllpairs(lines, i);
  for(int j=0; j<i; j++){
    free(lines[j]);
  }
  free(lines);
  return kva;
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t *kva;
  FILE *f = fopen(fname, "r");
  if(f == NULL){
    return NULL;
  }
  kva=readFile(f);
  if(fclose(f)!=0){
    printf("Failed to close the file");
    return NULL;
  }
  return kva;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0; i<pairs->numPairs;i++){
    free(pairs->pairs[i]);
  }
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0; i<pairs->numPairs;i++){
    printf("key = '%s' value = '%s'\n",pairs->pairs[i]->key,pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(int i=0;i<pairs->numPairs;i++){
    if(pairs->pairs[i]->key==key){
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
