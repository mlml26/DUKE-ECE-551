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
      throw Failure("invalid input page(No # sign)");
    }
    myfile.close();
  }
  else{
    //error("Cannot open file");
     throw Failure("Cannot open file");
  }
}

void Page::checkNavigation(){
  if(navigation.size()==1 && navigation[0].compare("WIN")==0){
    navigationCatogry = 1;
    return;
  }
  else if(navigation.size()==1 && navigation[0].compare("LOSE")==0){
    navigationCatogry = 2;
    return;
  }
  else{
    for(size_t i = 0; i < navigation.size(); i++){
      size_t found = navigation[i].find(':');
      if(found != string::npos){
	size_t idx;
	long number = stol(navigation[i], &idx, 10);
	if(idx < found || number <= 0){
	  throw Failure("page number must be a positive integer");
	}
	//add
	choicePage.push_back(number);
      }
      else{
	throw Failure("each line must have a colon");
      }
    }
    navigationCatogry = 3;
    return;
  }
}

void Page::printPage(){
  for(size_t i =0; i < text.size(); i++){
    cout << text[i] << endl;
  }
  cout << endl;
  if(navigationCatogry == 3){
    cout << "What would you like to do?" << endl;
    cout << endl;
    for(size_t i =0; i<navigation.size();i++){
      size_t found = navigation[i].find(':');
      cout << " ";
      //cout << navigation[i].substr(0,found);
      cout << i+1;
      cout << ". ";
      cout << navigation[i].substr(found+1) << endl;
    }
  }
  else if(navigationCatogry == 1){
    cout << "Congratulations! You have won. Hooray!\n";
  }
  else if(navigationCatogry == 2){
    cout << "Sorry, you have lost. Better luck next time!\n";
  }
}

Page::~Page(){
}
