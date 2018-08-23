#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;  // the number of months it is applicable to 
  double contribution; // how may dollars are contributed from the account per month
  double rate_of_return;// the rate of returns
};
  typedef struct _retire_info retire_info;
void retirement(int startAge, double initial, retire_info working, retire_info retired) {

  int total = working.months + retired.months;
  int i = 0;
  int age_in_months = startAge;
  double balance_up_to_date = initial;
  
  while( i < total ) {
    if(i < working.months) {
      
      int age_in_years = age_in_months / 12;
      int rest_months = age_in_months % 12;
      printf("Age %3d month %2d you have $%.2f\n", age_in_years, rest_months, balance_up_to_date );
      
      balance_up_to_date = balance_up_to_date * (1 + working.rate_of_return) + working.contribution;
      
      age_in_months ++;
      i++;
    }
    else {

      int age_in_years = age_in_months / 12;
      int rest_months = age_in_months %12;
      printf("Age %3d month %2d you have $%.2f\n", age_in_years, rest_months, balance_up_to_date );

      balance_up_to_date = balance_up_to_date * (1 + retired.rate_of_return) + retired.contribution;

      age_in_months ++;
      i++;
    }
  }
    

}


int main(void) {

  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  int startAge = 327;
  double savings =21345;

  retirement( startAge, savings, working, retired );
  return 0;
}
