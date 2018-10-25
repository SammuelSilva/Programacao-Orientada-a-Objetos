#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <map>
#include <fstream>
#include <algorithm>
#include <exception>
#include "Livros.hpp"
#include "Impressao.hpp"
#include "Eletronico.hpp"
#include "Audiobook.hpp"
#define MAXARQ 16

using std::cout;

enum {TImpresso, TEletronico, TAudioBook};

vector <Livro*> retorna_livro_idioma(const string&, vector <Livro*>&);
map <int,Livro*> retorna_livro_formato(vector <Livro*>&);
bool possui_audiobook(const string&, vector <Livro*>&);
vector <Livro*> colecao_livros(const string&, vector <Livro*>&);
set <string> retorna_keywords(vector <Livro*>&);
int quantidade_livros(const string&, vector <Livro*>&);
multimap <string,Livro*> quantidade_capitulos(const int&, vector <Livro*>&);
vector <string> retorno_livro_livraria(int&, vector <Livro*>&);
void escreve(const string&, vector <Livro*>&);
bool retorna_iterador(const string&,vector <Livro*>&, vector <Livro*>::iterator&,string);
void LeituraArquivo(vector <Livro*>&);
void retorna_mapeamento(vector <Livro*>&, const map <string,string>&);
vector<string> split(const string& , char delim = ' ');
#endif
