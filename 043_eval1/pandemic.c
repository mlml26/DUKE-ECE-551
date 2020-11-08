#include "pandemic.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<ctype.h>

/*
"parseLine" function takes a string in the form:
country name,population
and put the country name part into the the name
field of a struct called country_t, and put the
population into the population field of the struct.

The return is this struct.
*/
country_t parseLine(char * line) {
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
  char pop[21];
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
  pop[j] = '\0';
  if(line[i] != '\n'){
    perror("Illegal input: population is not number");
    exit(EXIT_FAILURE);
    }

  //Convert pop string to 64-bit unsigned integer
   uint64_t pop_num = strtoul(pop, NULL, 10);
  // uint64_t pop_num = 0;
  // pop_num = strtoul(pop, NULL, 10);
    if(errno==ERANGE){
    perror("population out of range");
    exit(EXIT_FAILURE);
    }

  ans.population = pop_num;
  
  return ans;
}

/*
calcRunningAvg function calculates the seven-day running average of case data.
It takes an array of daily case data, the number of days over which the data
is measured, and an array of doubles "avg", whose length is n_days-6, which will
hold the result of calculation.
*/
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  size_t n_avg = n_days - 6; //length of "avg"
  double sum;
  for(size_t i=0; i < n_avg; i++){
    sum = 0; //initialize
    for(size_t j = i; j < i + 7; j++){
      sum =(double) data[j] + sum;
    }
    avg[i] =(double) sum / (double) 7;
  }
}

/*
clacCumulative function calculates the cumulative number of cases that day
per 100000 people. It takes an array of daily case data, the number of days
over which data is measured, the population for the country, and an array
of doubles "cum", which will hold the result of calculation.
*/
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double per_num = 100000.0; //100,000people
  double sum = 0;
  for(size_t i =0; i < n_days; i++){
    sum = (double) data[i] + sum; //cumulative data
    cum[i] = (sum * per_num) / (double) pop;
  }
}

/*
printCountryWithMax function finds the maximum number of daily cases of all
countries represented in data, over the entire time period and print the answer in the form:
printf("%s has the most daily cases with %u\n", country_name, number_cases);
It takes an array of country_t struct, number of countries, 2-D array of data,
with each country's data representing a row, and number of days.
*/
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  size_t max_country_index = 0; //index of country with max number of daily cases.
  unsigned max_data[n_countries];//array to store each country's max cases.
  unsigned max_number = 0;//max number of daily cases of all countries.

  //loop through all countries one by one
  for(size_t c = 0; c < n_countries; c++){
    max_data[c] = data[c][0];
    //find certain country's max cases
    for(size_t d = 1; d < n_days; d++){
      if(data[c][d] > max_data[c]){
	max_data[c] = data[c][d];
      }
    }
    //update the max number of daily cases so far
    if(max_data[c] > max_number){
      max_number = max_data[c];
      max_country_index = c;
    }
  }

  printf("%s has the most daily cases with %u\n", countries[max_country_index].name, max_number);
  
}
