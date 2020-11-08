#include "rand_story.h"
#include <string.h>
#include <stdio.h>

/*
error function print error message and exit with a failure status.
 */
int error(char *s){
  perror(s);
  exit(EXIT_FAILURE);
}

/*
checkComLinArg function takes argc and number of command line argument as input.
It exit with a failure status if second input does not match the first. It do
nothing if they match.
 */
void checkComLinArg(int argc, int num){
  if(argc != num + 1){
    error("invalid number of command line argument!");
  }
}

/*
openCheckFile function takes a name of file as input. It open this file and return
it. If open failed, it exit with a failure status.
 */ 
FILE * openCheckFile(char * s){
  FILE *f = fopen(s, "r");
  if(f == NULL){
    error("open file failed");
  }
  return f;
}

/*
closeCheckFile function takes a FILE as input. It close this FILE. If close failed,
it exit with a failure status.
 */
void closeCheckFile(FILE *f){
  if(fclose(f) != 0){
    error("close file failed");
  }
}

/*
checkLine function takes a string as input and checks if each blank begin and end
with an underscore '_' on this line. If check correctly, it return sucessfully.
Otherwise, it print error message and exit with a failure status.
 */
int checkLine(char *line){
  size_t i = 0;
  size_t num = 0;
  //count the number of underscore '_'.
  while(line[i] != '\n'){
    if(line[i] == '_'){
      num++;
    }
    i++;
  }
  //check if the number is an even.
  if((num % 2) != 0){
    error("invalid input file: each blank must begin and end with an underscore '_' on the same line");
  }
  return EXIT_SUCCESS;
}

/*
replace function takes three string as input. The first input is the string to be changed.
The second input is the substring of first input, which is exactly to be replaced. The third
input is the string to insert. This function return the first input after being partly or
wholely replaced.
 */
char *replace(char *s, char *s1,char *s2){
  char *f = strstr(s,s1);
  if(f != NULL){
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    //replace
    if(len1 != len2){
      memmove(f + len2, f + len1, strlen(f) + 1 - len1);
    }
    memcpy(f, s2, len2);
  }
  return s;
}

/*
replaceLine function replaces every blanks with the word "cat" for the input string. 
 */

void replaceLine(char *line){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
  while(line[i] != '\n'){
    //detect the '_' before blank.
    if(line[i] == '_' && flag == 0){
      s = i;
      flag = 1;
      i++;
    }
    //detect the '_' after blank replace the blank with "cat".
    else if(line[i] == '_' && flag == 1){
      e = i;
      flag = 0;
      char s1[e - s + 1 + 1];
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      char *s2 =strdup(chooseWord("verb",NULL));
      line = replace(line, s1, s2);
      i = s + strlen(s2);
      free(s2);
    }
    else{
      i++;
    }
  }
}

/*
freeLines function frees allocated memory for an array of string.
 */
void freeLines(char **lines, size_t i){
  for(size_t j = 0; j < i; j++){
    free(lines[j]);
  }
  free(lines);
}

/*
parseTemplate function takes an FILE as input. This function parse the story template
by printing the story and replacing blanks with the word "cat".
 */

void parseTemplate(FILE *f){
  char **lines  = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i = 0;
  //read each line
  while(getline(&cur, &sz, f) >= 0){
    lines = realloc(lines, (i+1) * sizeof(*lines));
    checkLine(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  //replace and print
  for(size_t j = 0; j < i; j++){
    replaceLine(lines[j]);
    printf("%s",lines[j]);
  }
  //free allocated memory
  freeLines(lines, i);
}

/*
stripNewline functions delete the '\n' character in the input string.
 */
void stripNewline(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }
}

/*
createCatarray function creates and mallocs memory for a catarray_t structure.
It sets arr to NULL and n to zero and return this created structure.  
 */
catarray_t * createCatarray(void){
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  return catarray;
}

/*
addNewCategory function add and realloc a new category name to existing catarray_t structure 
with a word string.
 */
void addNewCategory(catarray_t * c, char * name, char * word){
  c->n++;
  c->arr = realloc(c->arr, c->n * sizeof(*c->arr));
  c->arr[c->n - 1].name = strdup(name);
  c->arr[c->n - 1].words = malloc(sizeof(*c->arr[c->n - 1].words));
  c->arr[c->n - 1].words[0] = strdup(word);
  c->arr[c->n - 1].n_words = 1;
}

/*
addWord function check if the second input category name exist in first input catarray_t
structure. If not exist, it call addNewCategory function to add a new category with the word
string. If exist, it just realloc the words array and add the word string to it.
 */
void addWord(catarray_t * c, char * name, char * word){
  size_t flag = 1;
  for(size_t i = 0; i < c->n; i++){
    if(strcmp(name,c->arr[i].name) == 0){
      c->arr[i].n_words++;
      c->arr[i].words = realloc(c->arr[i].words, c->arr[i].n_words * sizeof(*c->arr[i].words));
      c->arr[i].words[c->arr[i].n_words - 1] = strdup(word);
      flag = 0;
      break;
    }
  }
  if(flag){
    addNewCategory(c, name, word);
  }
}

/*
removeWord function takes three input. The first is a catarray_t structure. The second is
a category string. The third is a word string. It removes the word from a catarray_t structure.
*/
void removeWord(catarray_t * c, char * name,const char * word){
  int flag = 0;
  for(size_t i = 0; i < c->n; i++){
    //find the category
    if(!strcmp(name,c->arr[i].name)){
      for(size_t j = 0; j < c->arr[i].n_words; j++){
	//find the word
	if(!strcmp(word,c->arr[i].words[j])){
	  //update the number of words(minus 1)
	  c->arr[i].n_words--;
	  //if this category only have one word, just free the word.
	  if(c->arr[i].n_words == 0){
	    free(c->arr[i].words[0]);
	  }
	  // if this category have more than one word, copy the category except the word and
	  // free the original category.
	  else{
	    //malloc memory for the new category.
	    char ** temp = malloc(c->arr[i].n_words * sizeof(*temp));
	    //copy the words before the index of the removed word. 
	    if(j != 0){
	      for(size_t s =0; s < j; s++){
		temp[s] = strdup(c->arr[i].words[s]);
	      }
	    }
	    //copy the words after the index of the removed word.
	    if(j != c->arr[i].n_words){
	      for(size_t s = j; s < c->arr[i].n_words; s++){
		temp[s] = strdup(c->arr[i].words[s+1]);
	      }
	    }
	    //free original words
	    for(size_t x = 0; x < c->arr[i].n_words + 1; x++){
	      free(c->arr[i].words[x]);
	    }
	    free(c->arr[i].words);
	    //assign the new words
	    c->arr[i].words = temp;
	    }
	  flag = 1;
	  break;
	}
      }
      if(flag){
	break;
      }
    }
  }
}

/*
freeCatarray function free all allocated memory for the input catarray_t.
 */
void freeCatarray(catarray_t * c){
  for(size_t i = 0; i < c->n; i++){
    for(size_t j = 0; j < c->arr[i].n_words; j++){
      free(c->arr[i].words[j]);
    }
    free(c->arr[i].name);
    free(c->arr[i].words);
  }
  free(c->arr);
  free(c);
}

/*
readCatWorFile function read from the input FILE and store the words into a catarray_t and
print them using the provided function printWords.
 */

void readCatWorFile(FILE * f){
  catarray_t *ans = createCatarray();
  char *cur = NULL;
  size_t sz;
  while(getline(&cur, &sz, f) >= 0){
    //each line must have a colon.
    char * p = strchr(cur,':');
    if(p == NULL){
      error("Each line of the input file must have a colon!");
    }
    //find the category string
    char s1[p - cur + 1];
    strncpy(s1, cur, p - cur);
    s1[p - cur] = '\0';
    //find the word string
    char s2[strlen(p + 1)];
    strcpy(s2, p + 1);
    stripNewline(s2);
    //add the word to catarray_t.
    addWord(ans, s1, s2);
  }
  free(cur);
  printWords(ans);
  freeCatarray(ans);
}


/*
createNewRef function create and malloc memory for references to previously used words.
It set word to NULL and n_word to zero. It return the created reference_t structure.
 */
reference_t * createNewRef(void){
  reference_t *ref = malloc(sizeof(*ref));
  ref->word = NULL;
  ref->n_words = 0;
  return ref;
}

/*
addRefWord function add and realloc memory for a new word.
 */
void addRefWord(reference_t * ref, char* word){
  ref->n_words++;
  ref->word = realloc(ref->word, ref->n_words * sizeof(*ref->word));
  ref->word[ref->n_words - 1] = strdup(word);
}

/*
freeRef function free all allocated memory for the input reference_t structure.
 */
void freeRef(reference_t *ref){
  for(size_t i =0; i < ref->n_words; i++){
    free(ref->word[i]);
  }
  free(ref->word);
  free(ref);
}

/*
checkChoose function check if the category name is a valid integer of at least
one or a category name in the catarray_t. If it is the former, this function return
the provided used words string. If it is the latter and the forth input option is 0,
this function return a random choice from that category. If option is 1, this function
return a choice that has not already been used.
 */
char *checkChoose(char *s, reference_t *ref, catarray_t * cats, int option){
  //delete the two underscore "_"
  char c[strlen(s) - 1];
  strncpy(c, s + 1, strlen(s) - 2);
  c[strlen(s) - 2] = '\0';
  //check if the category name is valid integer of at least one
  char * e;
  long int num = strtol(c, &e, 10);
  if((e - c) == (strlen(c))){
    if(num <= 0){
      error("category name invalid: integer of at least one");
    }
    else if(num <= ref->n_words){
      char * ans = strdup(ref->word[ref->n_words - num]);
      return ans;
    }
    else{
      error("reference number too large");
    }
  }
  //not a integer
  char * ans = strdup(chooseWord(c, cats));
  if(option == 1){
    removeWord(cats, c, ans);
  }
  return ans;
}

/*
replaceLineFun function replaces every blanks with the word returned from
checkChoose function for the input string.
 */
void replaceLineFun(char *line, catarray_t * cats, reference_t * ref, int option){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
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
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      char *s2 = checkChoose(s1, ref, cats, option);
      line = replace(line, s1, s2);
      //add chosen word to reference
      addRefWord(ref, s2);
      i = s + strlen(s2);
      free(s2);
    }
    else{
      i++;
    }
  }
}

/*
parseTempFun function ss an updated version of pareTemplate. It takes an FILE
as input. This function parse the story template by printing the story and 
replacing blanks with the appropriate word.
 */
void parseTempFun(FILE *f, catarray_t * cats, reference_t *ref, int option){
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
    //replace
    replaceLineFun(lines[j], cats, ref, option);
    printf("%s",lines[j]);
  }
  freeLines(lines, i);
}

/*
readCatWorFun function read from the first input FILE and store the words into a catarray_t.
It also read form the second input FILE and parse the story by printing the story and
replaceing blanks with an approproate word by using parseTempFun function.
 */
void readCatWorFun(FILE * f, FILE * w, int option){
  reference_t *ref = createNewRef();
  catarray_t *ans = createCatarray();
  char *cur = NULL;
  size_t sz;
  while(getline(&cur, &sz, f) >= 0){
    char * p = strchr(cur,':');
    if(p == NULL){
      error("Each line of the input file must have a colon!");
    }
    char s1[p - cur + 1];
    strncpy(s1, cur, p - cur);
    s1[p - cur] = '\0';
      
    char s2[strlen(p + 1)];
    strcpy(s2, p + 1);
    stripNewline(s2);
    addWord(ans, s1, s2);
  }
  free(cur);
  //print story after replaced
  parseTempFun(w, ans, ref, option);
  freeCatarray(ans);
  freeRef(ref);
}
