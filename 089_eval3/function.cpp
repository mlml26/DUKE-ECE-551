#include "function.h"
#include <iostream>
using namespace std;

void error(string e){
  cerr << e << endl;
  exit(EXIT_FAILURE);
}
/*
void readEachPage(vector<Page> pages, string directory){
  string path1(directory);
  path1.append("\1.txt");
  Page p1;
  p1.read(path1);
  pages.push_back(p1);
  int pageIndex = 2;
  try{
    while(1){
      Page p;
      string path(directory);
      path.push_back('\\');
      path.append(to_string(pageIndex));
      path.append(".txt");
      pageIndex++;
      p.read(path);
      pages.push_back(p);
    }
  }
  catch(Failure &excep){
    //do nothing
  }
}

void checkStory(vector<Page> pages){
  for(size_t i=0; i< pages.size();i++){
    for(size_t j=0; j<pages[i].choicePage.size(); j++){
      if()
    }
  }
}
*/
