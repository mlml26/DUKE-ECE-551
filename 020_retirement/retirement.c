#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculate(int startAge,double initial,retire_info wOr){
  int age=startAge/12;
  int month=startAge%12;
  if(month==0){
    month=12;
    age--;
  }
  double startMonthBalance=initial;
  double interestIncrease;
  double endMonth;
  for(int i=0;i<wOr.months;i++){
  printf("Age %3d month %2d you have $%.2lf\n",age,month,startMonthBalance);
  interestIncrease=startMonthBalance*wOr.rate_of_return;
  endMonth=interestIncrease+wOr.contribution+startMonthBalance;
  startMonthBalance=endMonth;
  month++;
  if(month==13){
    month=month%12;
    age++;
  }
  }
  return startMonthBalance;
}

void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired){ //info about being retired
  double initialr;
 
  initialr=calculate(startAge,initial,working);
  calculate(startAge+working.months,initialr,retired);
}



int main(void){
  retire_info work,retire;
  work.months=489;
  work.contribution=1000;
  work.rate_of_return=0.045/12;
  retire.months=384;
  retire.contribution=-4000;
  retire.rate_of_return=0.01/12;
  retirement(327,21345,work,retire);
  return 0;

}
  
  



