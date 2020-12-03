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

//default constructor
book::book(){
}

//destructor
book::~book(){
}

/*
  The "readPages" method takes an director as input and read each
  page in the directory and sotre it into pages field.
 */
void book::readPages(string directory){
  string path1(directory);
  path1.append("/page1.txt");
  Page p1;
  //always read first page 
  p1.read(path1);
  p1.checkNavigation();
  pages.push_back(p1);
  int pageIndex = 2;
  //repeatly read next page until there is no such page
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
  //it is not an error for some pageN.txt (N > 1) to not exit.
  //catch it and we have read all the pages in the story.
  catch(Failure &excep){
  }
}

/*
  The "checkStory" method throw an exception if the following
  conditions are not met:
  1. Every page that is referenced by a choice is valid.
  2. Every page (except page 1) is referenced by at least one
     other page's choices.
  3. At least one page must be WIN page and at least one page
     must be LOSE page.
 */
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

/*
  The "beginStory" method begin the story on page 1 and repeatly display the current
  page and read a valid number from the user for their choice until the current page
  is WIN or LOSE.
 */
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
      //user input for choice
      getline(cin, choice);
      //the input might cause "stol" function throw an invalid_argument exception
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

/*
  The "generateReachable" method generate the set of  reachable pages and store 
  it into reachablePages field.
 */
void book::generateReachable(){
  reachablePages.insert(1);
  set<long>::iterator it;
  for(it = reachablePages.begin(); it != reachablePages.end(); ++it){
    for(size_t i =0; i < pages[(size_t)*it - 1].choicePage.size(); i++){
      reachablePages.insert(pages[(size_t)*it - 1].choicePage[i]);
    }
  }
}
/*
  The "printNonReachable" method print out every unreachable pages.
*/
void book::printNonReachable(){
  for(size_t i = 1; i < pages.size() + 1; i++){
    set<long>::iterator it;
    it = reachablePages.find(long(i));
    if(it == reachablePages.end()){
      cout << "Page " << i << " is not reachable\n";
    }
  }
}

/*
  The "findWINPage" method find a WIN page that is reachable and store
  it into the winSelected field. If there is no WIN page that is reachable,
  it will print "There is no way to win" and throw a FailurePrint exception.
 */
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

/*
  The "findWINPath" method use depth first search algorithm to find
  a win path from page1 and store this path vector to winPath field.
 */
void book::findWINPath(){
  stack<vector<long> > todo;
  vector<long> path;
  path.push_back(1);
  todo.push(path);
  while(todo.size()!= 0){
    vector<long> currentPath = todo.top();
    todo.pop();
    long currentPage = currentPath.back();
    //find it
    if(currentPage == winSelected){
      winPath = currentPath;
      return;
    }
    //loop each page adjacent to currentPage
    for(size_t i = 0; i < pages[(size_t)currentPage - 1].choicePage.size(); i++){
      set<long>::iterator it;
      //check if it is a reachable page
      it = reachablePages.find(pages[(size_t)currentPage - 1].choicePage[i]);
      if(it != reachablePages.end()){
	currentPath.push_back(*it);
	todo.push(currentPath);
	currentPath.pop_back();
      }
    }
  }
}

/*
  The "printWINPath" method print the win path in the specified format.
 */
void book::printWINPath(){
  //print the win path except for the last page
  for(size_t i = 0; i < winPath.size() - 1; i++){
    cout << "Page " << winPath[i] << " Choice ";
    for(size_t j = 0; j < pages[winPath[i]-1].choicePage.size(); j++){
      if(winPath[i+1] == pages[winPath[i]-1].choicePage[j]){
	cout << j+1 << endl;
      }
    }
  }
  //last win page
  cout << "Page " << winPath.back() << " WIN\n";
}
