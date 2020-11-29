#include "page.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

Page::Page(){
}

void Page::read(string filename){
  string line;
  ifstream myfile(filename);
  int flag = 0;
  //int flag_cur = 0;
  if(myfile.is_open()){
    while(getline(myfile, line)){
      if(line[0] == '#' && !flag){
	flag = 1;
      }
      else if(!flag){
	navigation.push_back(line);
      }
      else{
	text.push_back(line);
      }
    }
    if(!flag){
      error("invalid input page(No # sign)");
    }
    myfile.close();
  }
  else{
    //cerr << "Cannot open file" << endl;
    //exit(EXIT_FAILURE);
    error("Cannot open file");
  }
}

int Page::checkNavigation(){
  if(navigation.size()==1 && navigation[0].compare("WIN\n")){
    return 1;
  }
  else if(navigation.size()==1 && navigation[0].compare("LOSE\n")){
    return 2;
  }
  else{
    for(size_t i = 0; i < navigation.size(); i++){
      size_t found = navigation[i].find(':');
      if(found != string::npos){
	size_t idx;
	long number = stol(navigation[i], &idx, 10);
	if(idx < found && number > 0){
	  error("page number must be a positive integer");
	}
      }
      else{
	error("each line must have a colon");
      }
    }
    return 3;
  }
  //return;
}

void Page::printPage(int navigationCatogry){
  for(size_t i =0; i < text.size(); i++){
    cout << text[i] << endl;
  }
  cout << endl;
  if(navigationCatogry == 3){
    cout << "What would you like to do?" << endl;
    cout << endl;
    for(size_t i =0; i<navigation.size();i++){
      size_t found = navigation[i].find(':');
      cout << navigation[i].substr(0,found);
      cout << ". ";
      cout << navigation[i].substr(found+1);
    }
  }
  else if(navigationCatogry == 1){
    cout << "Congratulations! You have won. Hooray!\n";
  }
  else if(navigationCatogry == 2){
    cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else{
    error("wrong input");
  }
}

Page::~Page(){
}
