#include "page.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

book::book(){
}

book::~book(){
}

void book::addPage(Page &p){
  
}

void book::readPages(string directory){
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

void book::checkStory(){
  for(size_t i =0; i < pages.size(); i++){
    for(size_t j=0; j<pages[i].choicePage.size(); j++){
      if(pages[i].choicePage[j] > pages.size()){
	throw Failure("page that is referenced by a choice is invalid");
	pageReferenced.insert(pages[i].choicePage[j]);
      }
    }
  }
  if(pageReferenced.size() < (pages.size() -1)){
    throw Failure("Every page should be referenced by at least once");
  }
  int win = 0;
  int lose = 0;
  for(size_t i=0; i<pages.size();i++){
    if(pages[i].checkNavigation() == 1){
      win = 1;
    }
    else if(pages[i].checkNavigation() == 2){
      lose = 1;
    }
  }
  if(win != 1 || lose != 1){
    throw Failure("at least one page mush be a win and a lose");
  }
}

void book::beginStory(){
  pages[0].printPage
}
