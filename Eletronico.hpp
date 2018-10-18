#ifndef ELETRONICO_HPP
#define ELETRONICO_HPP

#include <string>
#include <vector>
#include "Livros.hpp"

using namespace std;
using std::string;

class Eletronico : public Livro{
  string url;
  string formato;
public:

  Eletronico(vector <string>, list <string>, set <string>, const string& = "",
   const string& = "", const string& = "", const string& = "", const int& = 0);
  ~Eletronico(){}

  //setters
  void setUrl(const string& );
  void setFormato(const string&);

  //getters
  virtual string getUrl();
  virtual string getFormato();
  friend ostream& operator<<(ostream&, Eletronico*);
};

#endif
