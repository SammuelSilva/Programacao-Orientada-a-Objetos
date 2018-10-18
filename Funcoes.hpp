#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <map>
#include <fstream>
#include <memory>
#include <algorithm>
#include <exception>
#include "Livros.hpp"
#include "Impressao.hpp"
#include "Eletronico.hpp"
#include "Audiobook.hpp"
#define MAXARQ 4

using std::cout;

enum {TImpresso, TEletronico, TAudioBook};

vector <string> retorna_livro_idioma(string idioma, vector <Livro*> livros);
map <int,string> retorna_livro_formato(int formato, vector <Livro*> livros);
bool possui_audiobook(string escritor, vector <Livro*> livros);
vector <Livro*> colecao_livros(string titulo, vector <Livro*> livros);
set <string> retorna_keywords(vector <Livro*> livros);
int quantidade_livros(string keyword, vector <Livro*> livro);
map <string,string> quantidade_capitulos(const int quant, vector <Livro*> livros);
vector <string> retorno_livro_livraria(int& qnt, vector <Livro*> livros);
void escreve(string saida, vector <Livro*> livros);
void LeituraArquivo(vector <Livro*>& livros);
vector<string> split(const string& str, char delim = ' ');
#endif
