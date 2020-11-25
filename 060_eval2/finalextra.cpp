#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
  vector<string> file2 = getLines(argv[2]);
  vector<string> file1 = getLines(argv[1]);
  unordered_map<string, set<string>> pairs = parse(file2);
  findBlank(file1, pairs);
  for(int i = 0; i< file1.size(); i++){
    cout << file1[i];
  }
}
