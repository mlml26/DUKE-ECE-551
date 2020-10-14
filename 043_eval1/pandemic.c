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
  size_t n_avg = n_days - 6;
  double sum;
  for(size_t i=0; i < n_avg; i++){
     sum = 0;
    for(size_t j = i; j < i + 7; j++){
      sum =(double) data[j] + sum;
    }
    avg[i] =(double) sum / (double) 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  /*
  double per_num = 100000.0;
  for(size_t i = 0; i < n_days; i++){
    double num_per_people = (double)data[i] / (double) pop;
    cum[i] = num_per_people * (double) per_num;
    //cum[i] = ((double) data[i] * per_num) / (double) pop; 
  }
  */
  double per_num = 100000.0;
  double sum = 0;
  for(size_t i =0; i < n_days; i++){
    sum = (double) data[i] + sum;
    cum[i] = (sum * per_num) / (double) pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  size_t max_country_index = 0;
  unsigned max_data[n_countries];
  unsigned max_number = 0;
  for(size_t c = 0; c < n_countries; c++){
    max_data[c] = data[c][0];
    for(size_t d = 1; d < n_days; d++){
      if(data[c][d] > max_data[c]){
	max_data[c] = data[c][d];
      }
    }
    if(max_data[c] > max_number){
      max_number = max_data[c];
      max_country_index = c;
    }
  }

  printf("%s has the most daily cases with %u\n", countries[max_country_index].name, max_number);
  
}
