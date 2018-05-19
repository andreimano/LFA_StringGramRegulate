#include <iostream>
#include <cstring>
#include "CFG.h"

using namespace std;

/*
this is me just messing around:
*/
template<class T>
T get(istream& is) {
  T result;
  is >> result;
  return result;
}

int main(int argc, char** argv) {
  char* filename;
  if(argc > 2) {
    filename = new char[strlen(argv[1])];
    strcpy(filename, argv[1]);
  } else {
    filename = new char[7];
    strcpy(filename, (char*)"data.in");
    filename[7] = '\0';
  }

  cout << "Datele au fost citite din: " << filename << endl;

  CFG* gramatica;
  if(argc > 1) {
    gramatica = new CFG(filename, atoi(argv[1]));
  } else {
    cout << "Introdu numarul maxim de litere: ";
    gramatica = new CFG(filename, get<int>(std::cin));
  }
  gramatica->printData();
  gramatica->generateStrings();
  gramatica->printStrings();
}
