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
    int navigationCatogry;
    navigationCatogry = mypage.checkNavigation();
    mypage.printPage(navigationCatogry);
    return EXIT_SUCCESS;
  }
  catch(Failure &excp){
    cerr << excp.what();
    return(EXIT_FAILURE);
  } 
}
