#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "stdio.h"
//any functions you want your main to use
struct reference_tag{
  const char ** word;
  size_t n_words;
};
  typedef struct reference_tag reference_t;

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
void freeRef(reference_t *ref);
void freeCatarray(catarray_t * c);
void readFile(FILE * f);
void replaceLineStep3(char *line, catarray_t * cats, reference_t * ref);
const char *checkChoose(char * s, reference_t *ref, catarray_t * cats);
void parseLineStep3(FILE *f, catarray_t * cats, reference_t *ref);
void readFileStep3(FILE * f, FILE * w);
reference_t * createNewRef(void);
void readFileStep3(FILE * f, FILE * w);

#endif
