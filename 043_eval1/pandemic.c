#include "pandemic.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<ctype.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  //Initialize
  for(size_t k=0; k < MAX_NAME_LEN; k++){
    ans.name[k]='\0';
  }
  uint64_t i = 0;
  //Read country name
  while(line[i] != ','){
    if(i == MAX_NAME_LEN-1){
    perror("Country Name exceeds the maximum length");
    exit(EXIT_FAILURE);
    }
    if(line[i] == '\n'){
    perror("Illegal input: no comma");
    exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
    i++;
  }
  i++;

  //Read population
  //Since the maximum value of 64-bit unsigned int is 18446744073709551615,
  //I creat an array with length 20.
  char pop[20];
  uint64_t j = 0;
  while(isdigit(line[i]) != 0){
    if(j ==20){
    perror("population out of range");
    exit(EXIT_FAILURE);
    }
    pop[j] = line[i];
    j++;
    i++;
    }
  
  if(line[i] != '\n'){
    perror("Illegal input: population is not number");
    exit(EXIT_FAILURE);
    }

  //Convert pop string to 64-bit unsigned integer
  uint64_t pop_num = strtoul(pop, NULL, 10);
    if(errno==ERANGE){
    perror("population out of range");
    exit(EXIT_FAILURE);
    }

  ans.population = pop_num;
  
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
