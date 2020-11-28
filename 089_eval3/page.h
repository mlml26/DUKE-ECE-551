class Page{
 private:
  vector<string> navigation;
  string secondSection;
  vector<string> text;
 public:
 Page(vector<string> navi, string secS, vector<string> t):navigation(navi), secondSection(secS), text(t){};
}
