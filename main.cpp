#include "Funcoes.hpp"
#include <cstdio>

struct Inv_Argument : exception { //Struct que herda exception, responsavel por imprimir um determinado erro.
  const char* what() const noexcept {return "Argumento invalido!";}
};

template < typename T >
void checagem(T valor, const int& argc);
void liberarMemoria(vector< Livro*>& livros);
void associar_valor(int& auxNum, char const* argv[], vector<Livro*>& livros);
void concatenar(string& dado, char const* argv[], const int& argc);

int main(int argc, char const *argv[]) {
  vector <Livro*> livros;
  livros.reserve(16); //Reservando 16 espaços na memoria, a fim de evitar copias
  vector <Livro*> auxVLivros;
  vector <Livro*> vAuxiliar;
  vector <string> auxiliar;
  short pesquisa;
  string dadoI;


  //função de verificação dos argumentos
  checagem(argv, argc);

  //Converte o primeiro argumento passado para short. Se a conversão der 0, o valor passado é invalido
  try{
    pesquisa = atoi(argv[1]);
    if(pesquisa==0)
      throw Inv_Argument(); //chama a struct herdeira da classe exception
  }catch(exception& e){
    cerr << e.what() << " O primeiro argumento deve ser numeral" << '\n';
    exit(1);
  }

  LeituraArquivo(livros); //função de leitura dos arquivos de entrada

  //Realização da pesquisa
  switch(pesquisa){
    case 1://Retorna os livros relacionados a um determinado idioma
      {
        concatenar(dadoI,argv,argc-1);
        vAuxiliar=retorna_livro_idioma(dadoI,livros);
        if(vAuxiliar.empty()==1)
          cout << "Livro com o idioma solicitado não encotrado" << endl;
        else{
          cout << "Livros com o idioma: " << dadoI << endl;
          for(auto aux:vAuxiliar)
            cout << aux << endl;
        }
      }
    break;
    case 2: //Retorna os livros relacionados a um determinado formato e ordenados pelo ano de publicacao
      {
        map <int,Livro*> retornados =retorna_livro_formato(livros);
        if(retornados.empty()==1)
          cout << "Não encontrado" << endl;
        else{
          cout << "Livros com o formato especificado: " << retornados.size() << endl;
          for(map<int,Livro*>::iterator aux=retornados.begin(); aux!=retornados.end(); ++aux)
            cout << aux->second << endl;
        }
      }
    break;
    case 3: //
      {
        int auxNum;
        associar_valor(auxNum,argv,livros);
        auxiliar=retorno_livro_livraria(auxNum,livros);
        if(auxNum!=0){
          cout << "Quantidade de livros existentes: " << auxNum <<"\n";
          for(auto aux:auxiliar)
            cout << aux << endl;
        }else{
          cout << "Não encontrado" << endl;
        }
      }
    break;
    case 4: //Verifica se um autor tem ou nao audiobooks
      concatenar(dadoI,argv,argc-1);
      if(possui_audiobook(dadoI,livros))
        cout << "Possui" << endl;
      else
        cout << "Não Possui" << endl;
    break;
    case 5: //Dado um titulo retorna todos os livros independente do formato
      concatenar(dadoI,argv,argc-1);
      auxVLivros = colecao_livros(dadoI,livros);
      if(auxVLivros.empty()==1)
        cout << "Livro não encontrado" << endl;
      else
        for(auto aux:auxVLivros){
          if(typeid(*aux).name()==typeid(Impresso).name())
            cout <<dynamic_cast<Impresso*> (aux) << endl;

          if(typeid(*aux).name()==typeid(Eletronico).name())
            cout <<dynamic_cast<Eletronico*> (aux) << endl;

          if(typeid(*aux).name()==typeid(AudioBook).name())
            cout <<dynamic_cast<AudioBook*> (aux) << endl;
        }
    break;
    case 6: //Retorna todas as keywords disponiveis sem repeticao
      {
        set <string> keywords = retorna_keywords(livros);
        if(keywords.empty()==1)
          cout << "Nenhum keyword encontrado" << endl;
        else{
          cout << "Keywords: " << endl;
          int i = 1;
          for(auto aux:keywords)
            cout << i++ << ". " << aux << endl;
        }
      }
    break;
    case 7: //Retorna todos os livros com a quantidade de capitulos menor ou igual a digitada
      {
        int auxNum;
        associar_valor(auxNum,argv,livros);
        multimap <string,Livro*> auxLivros = quantidade_capitulos(auxNum,livros);
        if(auxLivros.empty()==1)
          cout << "Nenhum livro encontrado" << endl;
        else{
          cout << "Livros: " << endl;
          for(multimap<string,Livro*>::iterator aux=auxLivros.begin(); aux!=auxLivros.end();++aux)
            cout << aux->second << endl;
        }
      }
    break;
    case 8: //Retorna um iterator para cada tipo de livro
      {
        concatenar(dadoI,argv,argc-1);
        vector <Livro*>::iterator IT;

        if(retorna_iterador(dadoI,livros, IT, typeid(Impresso).name())){
          cout << dynamic_cast<Impresso*>(*IT) << endl;
        }

        if(retorna_iterador(dadoI,livros, IT, typeid(Eletronico).name())){
           cout << dynamic_cast<Eletronico*> (*IT) << endl;
        }

        if(retorna_iterador(dadoI,livros, IT, typeid(AudioBook).name())){
          cout << dynamic_cast<AudioBook*>(*IT) << endl;
        }

      }
    break;
    case 9: //Imprime todos os livros com seus dados no terminal ou em um arquivo
      dadoI = argv[2];
      try{
        if(dadoI!="[T]" && dadoI!="[A]")
          throw Inv_Argument();
        else
          escreve(dadoI,livros);
      }catch(exception& e){
        cerr << e.what() << " Agumentos: [T] = Texto | [A] = Arquivo" << endl;
      }
    break;
    case 10: //Retorna a quantidade de livros com uma determinada keyword
      {
        concatenar(dadoI,argv,argc-1);
        int auxNum = quantidade_livros(dadoI,livros);
        if(auxNum==0)
          cout << "Livros com a keyword " << dadoI << " não foram encontrados" <<endl;
        else
          cout << "Quantidade de livros com a keyword " << dadoI << ": " << auxNum << endl;
      }
    break;
    case 11:
        {
          map <string,string> mapeamento = { pair<string,string> ("Portugues", "POT"),
                                             pair<string,string> ("Ingles","ING"),
                                             pair<string,string> ("Espanhol","ESP"),
                                             pair<string,string> ("Frances", "FRS")};
          retorna_mapeamento(livros, mapeamento);
          for(auto aux:livros){
            cout << aux << endl;
          }
          cout << endl;
        }
    break;
  }

  liberarMemoria(livros); //Apaga o vector de livro
  return 0;
}

//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
// FUNÇÕES AUXILIARES

template < typename T >
void checagem(T valor, const int& argc){
  //Verificação se a opcao desejada seja a '6', pois ela permite a passagem de apenas 1 parametro
  if(argc==2){
    if(*valor[1]!='6' && *valor[1]!='2' && (*valor[1]!='1' && *valor[2]!='1')){
      cerr << "Quantidade de argumentos invalidos: <pesquisa> <dado a procurar>" << '\n';
      exit(1);
    }
  }
}

//Apaga o vector de livro
void liberarMemoria(vector< Livro*>& livros){
  size_t aux = livros.size();
  for(size_t i=0; i<aux ; i++)
    delete livros[i];
}


  //Associa um valor numerico para o segundo argumento. Caso ele nao seja um numero, auxnum = 0;
void associar_valor(int& auxNum, char const* argv[], vector<Livro*>& livros){
  try{
    auxNum = atoi(argv[2]);
    if(auxNum==0)
      throw Inv_Argument();
  }catch(exception& e){
    cerr << e.what() << " O argumento deve ser numeral" << '\n';
    liberarMemoria(livros); //Apaga o vector de livro
    exit(1);
  }
}

//Concatena a entrada para entradas compostas
void concatenar(string& dado, char const* argv[], const int& argc){
  dado = "";
  for(int i=2; i<argc; i++){
    dado +=argv[i];
    dado+=" ";
  }
  dado+=argv[argc];
}
