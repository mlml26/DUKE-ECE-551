#include "page.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char ** argv){
  if(argc != 2){
    error("wrong input");
  }
  Page mypage;
  try{
    mypage.read(argv[1]);
    mypage.checkNavigation();
    mypage.printPage();
    return EXIT_SUCCESS;
  }
  catch(Failure &excp){
    cerr << excp.what();
    return(EXIT_FAILURE);
  }
  catch(invalid_argument &ie){
    cerr << "Out of range" << ie.what();
    return(EXIT_FAILURE);
  }
}
