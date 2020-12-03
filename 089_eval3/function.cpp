#include "function.h"
#include <iostream>
using namespace std;
/*
  This function print an error message and exit failure.
 */
void error(string e){
  cerr << e << endl;
  exit(EXIT_FAILURE);
}
