#include "rand_story.h"
#include <string.h>
#include <stdio.h>
int error(char *s){
  perror(s);
  exit(EXIT_FAILURE);
}

int checkLine(char *line){
  size_t i = 0;
  size_t num = 0;
  while(line[i] != '\n'){
    if(line[i] == '_'){
      num++;
    }
    i++;
  }
  if((num % 2) != 0){
    error("invalid input file: each blank must begin and end with an underscore '_' on the same line");
  }
  return EXIT_SUCCESS;
}

char *replace(char *s, char *s1,const char *s2){
  char *f = strstr(s,s1);
  if(f != NULL){
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if(len1 != len2){
      memmove(f + len2, f + len1, strlen(f) + 1 - len1);
    }
    memcpy(f, s2, len2);
  }
  return s;
}

void replaceLine(char *line){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
  //char *cur;
  //cur = strchr(line,'_');
  while(line[i] != '\n'){
    if(line[i] == '_' && flag == 0){
      s = i;
      flag = 1;
      i++;
    }
    else if(line[i] == '_' && flag == 1){
      e = i;
      flag = 0;
      char s1[e - s + 1 + 1];
      //char *s1 = malloc((e - s + 1 ) * sizeof(char));
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      //     memset(s1, '\0', e - s + 1 + 1);
      const char *s2 = chooseWord("verb",NULL);
      line = replace(line, s1, s2);
      i = s + strlen(s2);
      //free(s1);
    }
    else{
      i++;
    }
  }
}

void freeLines(char **lines, size_t i){
  for(size_t j = 0; j < i; j++){
    free(lines[j]);
  }
  free(lines);
}

void parseLine(FILE *f){
  char **lines  = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    lines = realloc(lines, (i+1) * sizeof(*lines));
    checkLine(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  for(size_t j = 0; j < i; j++){
    replaceLine(lines[j]);
    printf("%s",lines[j]);
  }
  freeLines(lines, i);
}
