#include "book.h"
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
  book mybook;
  try{
    mybook.readPages(argv[1]);
    //test
    //cout << mybook.pages.size() << endl;
    mybook.checkStory();
    mybook.beginStory();
    return EXIT_SUCCESS;
  }
  catch(Failure &excp){
    cerr << excp.what();
    return(EXIT_FAILURE);
  } 
}
