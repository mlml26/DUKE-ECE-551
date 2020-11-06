#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "stdio.h"
//any functions you want your main to use
int error(char *s);

int checkLine(char *line);

char *replace(char *s, char *s1, const char *s2);

void replaceLine(char *line);
void freeLines(char **lines, size_t i);
void parseLine(FILE *f);

void stripNewline(char * str);
catarray_t * createCatarray(void);
void addNewCategory(catarray_t * c, char * name, char * word);
void addWord(catarray_t * c, char * name, char * word);
void freeCatarray(catarray_t * c);
void readFile(FILE * f);
#endif
