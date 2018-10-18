#ifndef IMPRESSO_HPP
#define IMPRESSO_HPP

#include "Livros.hpp"

using namespace std;
using std::string;

class Impresso : public Livro{
  vector <string> livrarias;
  int colunas;
public:

  Impresso(vector <string>, vector <string>, list <string>, set <string>,
    const string& = "", const string& = "", const int& = 0, const int& = 0);
  ~Impresso(){}

  //setters
  void setLivrarias(vector <string> );
  void setColunas(const int&);

  //getters
  virtual vector <string> getLivrarias();
  virtual int getColunas();
  friend ostream& operator<<(ostream&, Impresso*);
};

#endif
