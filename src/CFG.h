#pragma once
#include <map>
#include <string>
#include <vector>
#include <list>

using namespace std;

class CFG {
public:
  CFG(char*, int);
  CFG(char*);
  void printData();
  void printStrings();
  void generateStrings();
private:
  void recursiv(string);
  bool cuvFinal(string);
  map <string, vector <string> > data;
  int nrMax;
  list <string> strings;
};
