#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include "CFG.h"

using namespace std;

CFG::CFG(char* streamName)
  : CFG(streamName, 0)
{}

CFG::CFG(char* streamName, int n)
  : nrMax(n)
{
    cout << endl << "Numar maxim de litere: " << nrMax << endl;

    ifstream fi(streamName);
    int nrNeterminale, nrProductii;
    string auxNeterminale, temp;
    vector <string> auxProductii;

    fi >> nrNeterminale;

    for(int i = 0; i < nrNeterminale; ++i) {
      fi >> auxNeterminale;
      fi >> nrProductii;
      for(int j = 0; j < nrProductii; ++j) {
        fi >> temp;
        auxProductii.push_back(temp);
      }
      data.insert(pair <string, vector <string> >(auxNeterminale, auxProductii));
      auxProductii.clear();
    }

    fi.close();
}

void CFG::printData() {
  cout << "Date citite: \n";

  map <string, vector<string> >::iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cout << "Nonterminala: " << it->first << endl << "Reguli de productie: ";
    vector <string>::iterator it_st = it->second.begin();
    for(; it_st != it->second.end(); ++it_st)
      cout << *it_st << " ";
    cout << endl;
  }
}

void CFG::generateStrings() {
  recursiv("S");
}

bool CFG::cuvFinal(string cuvant) {
  bool hasLambda = false;
  for(int i = 0; i < cuvant.size(); ++i) {
    if(cuvant[i] == '#')
      hasLambda = true;
    if(isupper(cuvant[i]))
      return false;
  }
  return hasLambda;
}

void CFG::recursiv(string cuvant) {

  if(cuvant.size() > nrMax+1)
    return;
  if(cuvFinal(cuvant)) {
    strings.push_back(cuvant);
    return;
  }

  for(int i = 0; i < cuvant.size(); ++i) {
    if(isupper(cuvant[i])) {
      string aux = cuvant;
      string index = ""; index += cuvant[i];
      for(int j = 0; j < data[index].size(); ++j) {
        aux.replace(i, i+1, data[index][j]);
        recursiv(aux);
        aux = cuvant;
      }
    }
  }
}

void CFG::printStrings() {
  list <string>::iterator it = strings.begin();
  cout << endl << "Cuvinte din gramatica: \n";
  for(; it != strings.end(); ++it) {
    it->erase(it->size()-1); // sterge #
    cout << *it << "; ";
  }
  cout << endl;
}
