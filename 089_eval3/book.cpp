#include <exception>
#include "page.h"
#include "book.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <stack>
using namespace std;

book::book(){
}

book::~book(){
}

void book::readPages(string directory){
  string path1(directory);
  path1.append("/page1.txt");
  Page p1;
  p1.read(path1);
  p1.checkNavigation();
  pages.push_back(p1);
  int pageIndex = 2;
  try{
    while(1){
      Page p;
      string path(directory);
      path.append("/page");
      path.append(to_string(pageIndex));
      path.append(".txt");
      pageIndex++;
      p.read(path);
      p.checkNavigation();
      pages.push_back(p);
    }
  }
  catch(Failure &excep){
  }
}

void book::checkStory(){
  for(size_t i =0; i < pages.size(); i++){
    for(size_t j=0; j<pages[i].choicePage.size(); j++){
      if((unsigned)pages[i].choicePage[j] > pages.size()){
	throw Failure("page that is referenced by a choice is invalid");
      }
      pageReferenced.insert(pages[i].choicePage[j]);
    }
  }
  if(pageReferenced.size() < (pages.size() -1)){
    throw Failure("Every page should be referenced by at least once");
  }
  int win = 0;
  int lose = 0;
  for(size_t i=0; i<pages.size();i++){
    if(pages[i].navigationCatogry == 1){
      win = 1;
    }
    else if(pages[i].navigationCatogry == 2){
      lose = 1;
    }
  }
  if(win != 1 || lose != 1){
    throw Failure("at least one page mush be a win and a lose");
  }
}

void book::beginStory(){
  pages[0].printPage();
  int cur_cat = 3;
  size_t index = 0;
  while(cur_cat == 3){
    string choice("-1w");
    size_t idx;
    long number = stol(choice, &idx, 10);
    int flag = 0;
    while(idx < choice.size() || number <= 0 || (unsigned)number > pages[index].choicePage.size()){
      if(!flag){
	flag = 1;
      }
      else{
	cout << "That is not a valid choice, please try again\n";
      }
      getline(cin, choice);
      
      try{
	number = stol(choice, &idx, 10);
      }
      catch(invalid_argument &ie){
      //donothing
      }
    }
    index = pages[index].choicePage[number-1] - 1;
    pages[index].printPage();
    cur_cat = pages[index].navigationCatogry;
  }
  
}

void book::generateReachable(){
  reachablePages.insert(1);
  set<long>::iterator it;
  for(it = reachablePages.begin(); it != reachablePages.end(); ++it){
    for(size_t i =0; i < pages[(size_t)*it - 1].choicePage.size(); i++){
      reachablePages.insert(pages[(size_t)*it - 1].choicePage[i]);
    }
  }
}

void book::printNonReachable(){
  for(size_t i = 1; i < pages.size() + 1; i++){
    set<long>::iterator it;
    it = reachablePages.find(long(i));
    if(it == reachablePages.end()){
      cout << "Page " << i << " is not reachable\n";
    }
  }
}

void book::findWINPage(){
  int find = 0;
  set<long>::iterator it;
  for(it = reachablePages.begin(); it != reachablePages.end(); ++it){
    if(pages[(size_t)*it - 1].navigationCatogry == 1){
      find = 1;
      winSelected = *it;
      break;
    }
  }
  if(!find){
    cout << "There is no way to win\n";
    throw FailurePrint();
  }
}

void book::dfs(){
  stack<vector<long> > todo;
  vector<long> path;
  path.push_back(1);
  todo.push(path);
  while(todo.size()!= 0){
    // vector<long> currentPath = todo.pop();
    vector<long> currentPath = todo.top();
    todo.pop();
    long currentPage = currentPath.back();
    
    if(currentPage == winSelected){
      winPath = currentPath;
      return;
    }
    for(size_t i = 0; i < pages[(size_t)currentPage - 1].choicePage.size(); i++){
      set<long>::iterator it;
      it = reachablePages.find(pages[(size_t)currentPage - 1].choicePage[i]);
      if(it != reachablePages.end()){
	currentPath.push_back(*it);
	todo.push(currentPath);
	currentPath.pop_back();
      }
    }
  }
}

void book::printWINPath(){
  for(size_t i = 0; i < winPath.size() - 1; i++){
    cout << "Page " << winPath[i] << " Choice ";
    //long choice;
    for(size_t j = 0; j < pages[winPath[i]-1].choicePage.size(); j++){
      if(winPath[i+1] == pages[winPath[i]-1].choicePage[j]){
	cout << j+1 << endl;
      }
    }
  }
  cout << "Page " << winPath.back() << " WIN\n";
}
