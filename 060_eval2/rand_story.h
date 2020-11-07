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
void checkComLinArg(int argc, int num);
FILE * openCheckFile(char *s);
void closeCheckFile(FILE *f);
int checkLine(char *line);
char *replace(char *s, char *s1, const char *s2);
void replaceLine(char *line);
void freeLines(char **lines, size_t i);
void parseTemplate(FILE *f);
void stripNewline(char * str);
catarray_t * createCatarray(void);
void addNewCategory(catarray_t * c, char * name, char * word);
void addWord(catarray_t * c, char * name, char * word);
void removeWord(catarray_t * c, char * name, const char * word);
void freeRef(reference_t *ref);
void freeCatarray(catarray_t * c);
void readCatWorFile(FILE * f);
void replaceLineFun(char *line, catarray_t * cats, reference_t * ref, int option);
const char *checkChoose(char * s, reference_t *ref, catarray_t * cats, int option);
void parseTempFun(FILE *f, catarray_t * cats, reference_t *ref, int option);
void readCatWorFun(FILE * f, FILE * w, int option);
reference_t * createNewRef(void);

#endif
