#include "Livros.hpp"

Livro::Livro(vector <string> escritor, list <string> capitulo, set <string> keywords,
  const string& titulo,
  const string& idioma,
  const int& ano): titulo(titulo), idiomaOriginal(idioma), anoPublicacao(ano){
    setEscritores(escritor); setKeywords(keywords); setCapitulos(capitulo);
  }


//Setters
void Livro::setEscritores(vector <string> escritor){
  escritores.insert(escritores.begin(),escritor.begin(),escritor.end());
}

void Livro::setKeywords(set <string> keyword){
  for(auto aux:keyword)
    keywords.insert(aux);
}

void Livro::setCapitulos(list <string> capitulo){
  capitulos.insert(capitulos.begin(),capitulo.begin(),capitulo.end());
}

void Livro::setTitulo(const string& titulo){
  this->titulo=titulo;
}

void Livro::setIdioma(const string& idiomaOriginal){
  this->idiomaOriginal=idiomaOriginal;
}

void Livro::setAnopublicacao(const int& anoPublicacao){
  this->anoPublicacao=anoPublicacao;
}

//getters
vector <string> Livro::getEscritores() const{
  return escritores;
}

list <string> Livro::getCapitulos() const{
  return capitulos;
}

set <string> Livro::getKeywords() const{
  return keywords;
}

string Livro::getTitulo() const{
  return titulo;
}

string Livro::getIdioma() const{
  return idiomaOriginal;
}

int Livro::getAnopublicacao() const{
  return anoPublicacao;
}

ostream& operator<<(ostream& out, Livro* livros){

  if(livros->titulo.length() > 30)
    out << setw(30) << std::left << livros->titulo.substr(0,30) << " | ";
    else
      out << setw(30) << std::left << livros->titulo << " | ";

  if(livros->escritores[0].length() > 30)
    out << setw(30) << std::right << livros->escritores[0].substr(0,30) << " | ";
    else
      out << setw(30) << std::right <<  livros->escritores[0] << " | ";

  if(livros->idiomaOriginal.length() > 10)
    out << setw(10) << std::left << livros->idiomaOriginal.substr(0,10) << " | ";
    else
      out << setw(10) << std::left << livros->idiomaOriginal << " | ";

  if(livros->capitulos.size() < 10)
    out << "00"<<livros->capitulos.size() << " | ";
    else if(livros->capitulos.size() < 100)
      out << "0" << livros->capitulos.size() << " | ";
      else
        out << livros->capitulos.size() << " | ";

  if(livros->keywords.size() < 10)
    out << "00"<<livros->keywords.size() << " | ";
    else if(livros->keywords.size() < 100)
      out << "0" << livros->keywords.size() << " | ";
        else
          out << livros->keywords.size() << " | ";

  return out;
}
