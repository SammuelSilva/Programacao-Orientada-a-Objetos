#include "Audiobook.hpp"

AudioBook::AudioBook(vector <string> escritor, list <string> capitulo,
 set <string> keyword, const string& titulo, const string& idioma,
 const string& formato,const float& duracao, const int& ano) :
 Livro(escritor,capitulo,keyword,titulo,idioma,ano), duracao(duracao), formato(formato){}

 void AudioBook::setDuracao(const float& duracao){
  this->duracao = duracao;
}

void AudioBook::setFormato(const string& formato){
  this->formato = formato;
}

float AudioBook::getDuracao(){
  return duracao;
}

string AudioBook::getFormato(){
  return formato;
}

ostream& operator<<(ostream& out, AudioBook* livros){
  out << dynamic_cast <Livro*> (livros);
  out << setprecision(2) << livros->getDuracao() << " | ";

  return out;
}
