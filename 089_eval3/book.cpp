#include <exception>
#include "page.h"
#include "book.h"
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

void book::readPages(string directory){
  string path1(directory);
  //path1.push_back('/');
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
      //path.push_back('/');
      path.append("/page");
      path.append(to_string(pageIndex));
      path.append(".txt");
      pageIndex++;
      p.read(path);
      p.checkNavigation();
      //test
      //cout << "after navigation\n";
      pages.push_back(p);
    }
  }
  catch(Failure &excep){
    //do nothing
  }
  //test
  //cout << pages.size() << endl;
}

void book::checkStory(){
  for(size_t i =0; i < pages.size(); i++){
    //cout << "enter \n";
    //cout << pages[i].choicePage.size() << endl;
    for(size_t j=0; j<pages[i].choicePage.size(); j++){
      //test
      //cout << pages[i].choicePage.size() << endl;
      if((unsigned)pages[i].choicePage[j] > pages.size()){
	throw Failure("page that is referenced by a choice is invalid");
	//pageReferenced.insert(pages[i].choicePage[j]);
      }
      pageReferenced.insert(pages[i].choicePage[j]);
    }
  }
  //test
  //cout << pageReferenced.size() << endl;
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
    //long number = 0;
    long number = stol(choice, &idx, 10);
    // size_t index = 0;
    //cout << number << endl;
    int flag = 0;
    while(idx < choice.size() || number <= 0 || (unsigned)number > pages[index].choicePage.size()){
      if(!flag){
	//cout << "Please enter your choice: ";
	flag = 1;
      }
      else{
	cout << "That is not a valid choice, please try again\n";
      }
      getline(cin, choice);
      
      //  number = stol(choice, &idx, 10);
      try{
	number = stol(choice, &idx, 10);
      }
      catch(invalid_argument &ie){
      //donothing
      }
    }
    //index = number - 1;
    //cout << "Page index: "<< pages[index].choicePage[number-1]-1 << endl;
    //pages[pages[index].choicePage[number-1]-1].printPage();
    //index = pages[index].choicePage[number-1]-1;
    //  cout << "Choice size is " << pages[index].choicePage.size() << endl;
    //cout << "First choice is " << pages[index].choicePage[0] << endl;
    index = pages[index].choicePage[number-1] - 1;
    //cout << "Page index: " << index << endl;
    pages[index].printPage();
    //pages[index].printPage();
    cur_cat = pages[index].navigationCatogry;
  }
  
}
