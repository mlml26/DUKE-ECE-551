#include <cstdlib>

#include <iostream>

#include <string>

void read(std::string &sen, std::string &w){
  //std::string tem;
	std::cout << "Please enter the sentence: ";
	std::getline(std::cin,sen);
	std::cout << "Please enter the word: ";
	std::cin >> w;
	//std::getline(std::cin,w);
	//std::cout << "Finish ";
}
void print(std::string &sen, std::string &w){
	std::size_t num = 0;
	std::size_t pos = 0;
	pos = sen.find(w, pos);
	while(pos!=std::string::npos){
		++num;
		pos = sen.find(w, pos);
	}
	std::cout << num << std::endl;
}
void replace(std::string &sen, std::string &w){

	std::size_t pos = 0;
	pos = sen.find(w, pos);
	while(pos!=std::string::npos){
		sen.replace(pos,w.length(),"WAS_HERE");
		pos = sen.find(w, pos);
	}
	std::cout << sen << std::endl;
}
int main(void){
	std::string sen, w;
	read(sen,w);
	print(sen,w);
	replace(sen,w);
	return 0;
}
