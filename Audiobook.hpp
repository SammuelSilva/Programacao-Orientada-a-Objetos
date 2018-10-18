#ifndef AUDIOBOOK_HPP
#define AUDIOBOOK_HPP

#include "Livros.hpp"

using namespace std;
using std::string;

class AudioBook : public Livro{
  float duracao;
  string formato;
public:

  AudioBook(vector <string>, list <string>, set <string>, const string& = "",
   const string& = "", const string& = "", const float& = 0.0, const int& = 0);
  ~AudioBook(){}

  //setters
  void setDuracao(const float& );
  void setFormato(const string&);

  //getters
  virtual float getDuracao();
  virtual string getFormato();
  friend ostream& operator<<(ostream&, AudioBook*);
};

#endif
