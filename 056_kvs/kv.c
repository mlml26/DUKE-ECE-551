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
kvpair_t *splitOnepair( char *str){
  char *a = str;
  char *b = str;
  a = strchr(a,'=');
  b = strchr(str,'\n');
  kvpair_t *p = malloc(sizeof(*p));
    
  if((a == NULL)||( b == NULL)){
    perror("Invalid first type of input file");
    exit(EXIT_FAILURE);
   }
  
  size_t key_len = a- str +1;
  p->key =malloc(key_len * sizeof(*p->key));
  strncpy(p->key, str, key_len-1);
  p->key[key_len-1]='\0';
  size_t value_len = b-a;
  p->value = malloc(value_len* sizeof(*p->value));
  strncpy(p->value, a+1,value_len-1);
  p->value[value_len-1]='\0';
  return p;
}
void addpairs( char * str, kvarray_t *kvarray){
  kvpair_t * a = NULL;
  a=splitOnepair(str);
  kvarray->pairs=realloc(kvarray->pairs,(kvarray->numPairs+1) * sizeof(*kvarray->pairs));
  kvarray->pairs[kvarray->numPairs]=a;
  kvarray->numPairs++;
  a=NULL;
}/*
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
}*/
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t *kva=malloc(sizeof(*kva));
  kva->pairs=NULL;
  kva->numPairs=0;
  FILE *f = fopen(fname, "r");
  if(f == NULL){
    perror("Cannot open file");
    return NULL;
  }
  char *line =NULL;
  size_t size=0;
  //size_t len=0;
  while(getline(&line,&size,f)>=0){
    //printf("%s\n",line);
    addpairs(line,kva);
    // line=NULL;
  }
  free(line);
  if(fclose(f)!=0){
    printf("Failed to close the file");
    perror("cannot close file");
    return NULL;
  }
  return kva;
}

void freeKVs(kvarray_t * p) {
  //WRITE ME
  for(int i=0; i<p->numPairs;i++){
    free(p->pairs[i]->key);
    free(p->pairs[i]->value);
    free(p->pairs[i]);
  }
  free(p->pairs);
  free(p);
}

void printKVs(kvarray_t * p) {
  //WRITE ME
  for(int i=0; i<p->numPairs;i++){
    printf("key = '%s' value = '%s'\n",p->pairs[i]->key,p->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * p, const char * key) {
  //WRITE ME
  for(int i=0;i<p->numPairs;i++){
    if(strcmp(p->pairs[i]->key,key)==0){
      return p->pairs[i]->value;
    }
  }
  return NULL;
}
