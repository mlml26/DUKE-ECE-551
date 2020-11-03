#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

void sortLines(std::istream &stream){
  std::string s;
  std::vector<std::string> lines;
  if(stream.good()!=1 && stream.eof()!=1){
    std::cerr << "error occurs when read the input" << std::endl;
    exit(EXIT_FAILURE);
  }
  while(getline(stream, s)){
    lines.push_back(s);
  }
  std::sort(lines.begin(),lines.end());
  std::vector<std::string>::iterator it = lines.begin();
  while(it != lines.end()){
    std::cout << *it << std::endl;
    ++it;
  }
}
void sortFiles(int argc, char ** argv){
  for(int i =1; i< argc; i++){
    std::ifstream ifs(argv[i], std::ifstream::in);
    if(!ifs.is_open()){
      std::cerr << "annot open file!" << std::endl;
      exit(EXIT_FAILURE);
    }
    sortLines(ifs);
    ifs.close();
  }
}
int main(int argc, char ** argv){
  if(argc ==1){
    sortLines(std::cin);
  }
  else{
    sortFiles(argc, argv);
  }
  return EXIT_SUCCESS;
}
