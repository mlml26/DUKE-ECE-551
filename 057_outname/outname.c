#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char *result=malloc((strlen(inputName)+8)*sizeof(*result));
  strcpy(result,inputName);
  //result =inputName;
  strcat(result,".counts");
  return result;
}
