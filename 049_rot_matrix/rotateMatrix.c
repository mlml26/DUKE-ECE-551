#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define LINE_SIZE 12
#define ROWS 10

void error(const char* m){
  fprintf(stderr,"%s\n",m);
  exit(EXIT_FAILURE);
}

void read(char line[ROWS][LINE_SIZE],FILE *f){
  int count=0;
  while(fgets(line[count],LINE_SIZE,f)!=NULL){
    if(strchr(line[count],'\n')==NULL){
      error("line too long");
    }
    if(line[count][9]=='\0'){
      error("line too short");
    }
    count++;
    if(count==10)
      return;
  }
  if(count<10){
    error("too few lines");
  }
  
}

void rotate_print(char line[ROWS][LINE_SIZE]){
  for(int c=0;c<10;c++){
    for(int r=9;r>=0;r--){
      printf("%c",line[r][c]);
    }
    printf("\n");
  }
  return;
}
int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"Usage:command line argument");
    return EXIT_FAILURE;
  }
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    perror("Failed to open the input file!");
    return(EXIT_FAILURE);
  }
  char array[ROWS][LINE_SIZE];
  read(array,f);
  
  char a[LINE_SIZE];
  if(fgets(a,LINE_SIZE,f)!=NULL){
    error("too many lines");
  }
  rotate_print(array);
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
  
}
