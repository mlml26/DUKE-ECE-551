#include "page.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

//default constructor
Page::Page(){
}

/* The "read" method takes the name of one single page as input
   and store the page information into the navigation, text
   field. It also throw an exception if the page do not
   have a signle line that starts with a # sign.
*/
void Page::read(string filename){
  string line;
  ifstream myfile(filename);
  int flag = 0;
  if(myfile.is_open()){
    while(getline(myfile, line)){
      if(line[0] == '#' && !flag){
	flag = 1;
      }
      //store each line before # line into navigation field
      else if(!flag){
	navigation.push_back(line);
      }
      //store each line after # line into text field
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
     throw Failure("Cannot open file");
  }
}

/*
  The "checkNavigation" method assign 1 to the navigationCatogry
  if it is a valid "WIN", 2 for "LOSE" and 3 for choice. If it is
  3, it also store each line of choice and store it into choicePage
  field. It also throws an exception if the choice line is invalid.
 */
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
	//read the number
	long number = stol(navigation[i], &idx, 10);
	if(idx < found || number <= 0){
	  throw Failure("page number must be a positive integer");
	}
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

/*
  The "printPage" method print a page with choices for what to do
  or a page with win and lose information.
 */
void Page::printPage(){
  //print text
  for(size_t i =0; i < text.size(); i++){
    cout << text[i] << endl;
  }
  cout << endl;
  if(navigationCatogry == 3){
    cout << "What would you like to do?" << endl;
    cout << endl;
    //print choice with specified format
    for(size_t i =0; i<navigation.size();i++){
      size_t found = navigation[i].find(':');
      cout << " ";
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

//destructor
Page::~Page(){
}
