#include "Eletronico.hpp"

Eletronico::Eletronico(vector <string> escritor, list <string> capitulo,
 set <string> keyword, const string& titulo, const string& idioma,
 const string& url, const string& formato, const int& ano) :
 Livro(escritor,capitulo,keyword,titulo,idioma,ano), url(url), formato(formato){}

void Eletronico::setUrl(const string& url){
  this->url = url;
}

void Eletronico::setFormato(const string& formato){
  this->formato = formato;
}

string Eletronico::getUrl(){
  return url;
}

string Eletronico::getFormato(){
  return formato;
}

ostream& operator<<(ostream& out, Eletronico* livros){
  out << dynamic_cast <Livro*> (livros);
  if(livros->formato.length() > 10)
    out << livros->formato.substr(0,10) << " | ";
      else
        out << livros->formato << " | ";

  return out;
}
