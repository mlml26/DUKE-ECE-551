#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "page.h"
#include<set>
using namespace std;

class book{
 private:
  vector<Page> pages;
  set<long> pageReferenced;
 public:
  book();
  ~book();
  //void addPage(Page &p);
  void readPages(string directory);
  void checkStory();
  void beginStory();
}
