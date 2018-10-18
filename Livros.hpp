#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <string>
#include <vector>
#include <list>
#include <set>
#include <iomanip>
#include <iostream>
#include <memory>

using namespace std;
using std::string;
using std::shared_ptr;

class Livro{
  vector <string> escritores;
  list <string> capitulos;
  set <string> keywords;
  string titulo;
  string idiomaOriginal;
  int anoPublicacao;

public:

  Livro(vector <string>, list <string>, set <string>,
    const string& = "", const string& = "", const int& = 0 );
  virtual ~Livro(){}

  void setEscritores (vector <string>);
  void setCapitulos (list <string>);
  void setKeywords (set <string>);
  void setTitulo (const string& );
  void setIdioma (const string& );
  void setAnopublicacao(const int& );

  virtual vector <string> getEscritores() const;
  virtual list <string> getCapitulos() const;
  virtual set <string> getKeywords() const;
  virtual string getTitulo() const;
  virtual string getIdioma() const;
  virtual int getAnopublicacao() const;
  friend ostream& operator<<(ostream&, Livro*);

};

#endif
