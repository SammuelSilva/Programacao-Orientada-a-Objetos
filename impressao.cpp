#include "Impressao.hpp"

Impresso::Impresso(vector <string> livrarias, vector <string> escritor,
  list <string> capitulo, set <string> keyword, const string& titulo,
  const string& idioma, const int& ano, const int& colunas) :
  Livro(escritor,capitulo,keyword,titulo,idioma,ano), colunas(colunas){
    setLivrarias(livrarias);
  }

//Setters
void Impresso::setLivrarias(vector <string> ent_livrarias){
  livrarias.insert(livrarias.begin(),ent_livrarias.begin(),ent_livrarias.end());
}

void Impresso::setColunas(const int& colunas){
  this->colunas=colunas;
}

//getters
vector <string> Impresso::getLivrarias(){
  return livrarias;
}

int Impresso::getColunas(){
  return colunas;
}

ostream& operator<<(ostream& out, Impresso* livros){
  out << dynamic_cast <Livro*> (livros);
  if(livros->livrarias[0].length() > 10)
    out << setw(10) << std::setfill(' ') <<  livros->livrarias[0].substr(0,10) << " | ";
    else if (livros->livrarias.size()==0)
      out << setw(10) << std::setfill(' ') <<  "Nenhuma | ";
      else
        out << setw(10) << std::setfill(' ') << livros->livrarias[0] << " | ";

  return out;
}
