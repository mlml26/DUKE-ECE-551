#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

class Page{
 private:
  vector<string> navigation;
  vector<string> text;
 public:
  Page();
  //Page(vector<string> navi, vector<string> t):navigation(navi), text(t){};
  void read(string filename);
  int checkNavigation();
  void printPage(int navigationCatogry);
  ~Page();
};
