#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;

// This function reads the data from the file, store each line into a vector and return this vector.
vector<string> getLines(const char ** argv) {
    vector<string> lines;
    string sin = argv[1];
    ifstream in(sin);
    string str;
    if(in.is_open()){
        while(getline(in, str)) {
            lines.push_back(str);
        }
        in.close();
    }
    else{
        cerr << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    return lines;
}

// This function find the first colon in one string and return its index. If there is no colon in this string, it returns -1.
int findColon(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ':') {
            return i;
        }
    }
    return -1;
}

// This functions parses each line into names and words, while the names are strings and the words are store in sets of strings. This function returns an unordered map.
unordered_map<string, set<string>> parse(vector<string> lines) {
    unordered_map<string, set<string>> pairs;
    vector<string> all_words, all_names;
    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        int colon_index = findColon(line);
        // Throw an exception if there is no colon in one string
        if (colon_index == -1) {
            cerr << "Invalid line" << endl;
            exit(EXIT_FAILURE);
        }
        // Use the colon in the string to parse each line into two parts: name and word
        string name = line.substr(0, colon_index);
        string word = line.substr(colon_index + 1, line.size() - name.size() - 1);
        all_names.push_back(name);
        all_words.push_back(word);
    }
    // Words cannot be duplicated, so use a set to avoid duplication
    set<string> words;
    for (int i = 0; i < all_names.size(); i++) {
        words.insert(all_names[i]);
    }
    // Each name has a corresponding set of words
    for (string w : words) {
        set<string> n;
        pairs[w] = n;
    }
    // Insert words into the corresponding set
    for (int i = 0; i < all_names.size(); i++) {
        string name = all_names[i];
        string word = all_words[i];
        pairs[word].insert(name);
    }
    return pairs;
}

// This functions returns 1 if this line has underscore and the number of underscores is valid, returns 0 if the number if invalid and returns -1 if there is no underscore at all
int checkUnderscore(string line) {
    int count = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '_') {
            count++;
        }
    }
    if (count == 0) {
        return -1;
    }
    return count % 2 == 0;
}


// This function replace the blanks with the words corresponding to the name
void replace(string line, unordered_map<string, set<string>> pairs) {
    size_t head;
    size_t tail;
    head = line.find("_");
    while (head){
        tail = line.find("_", head+1);
        line.replace(head, tail-head+1, *(pairs[line.substr(head+1, tail-head-1)].begin()));
        head = line.find("_", tail+1);
    }
}

// This function find all blanks in each line and replace them
void findBlank(vector<string> lines, unordered_map<string, set<string>> pairs) {
    for (string line : lines) {
        if (checkUnderscore(line) == 0) {
            cerr << "Invalid underscore" << endl;
            exit(EXIT_FAILURE);
        }
        while (checkUnderscore(line) != -1) {
            replace(line, pairs);
        }
    }
}

int main(int argc, char **argv){
  vector<string> file2 = getLines(argv[2]);
  vector<string> file1 = getLines(argv[1]);
  unordered_map<string, set<string>> pairs = parse(file2);
  findBlank(file1, pairs);
  for(int i = 0; i< file1.size(); i++){
    cout << file1[i];
  }
}
