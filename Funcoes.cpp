#include "Funcoes.hpp"

//Retorna um vetor de livro com um determinado idioma
vector <string> retorna_livro_idioma(string idioma, vector <Livro*> livros){
  vector <string> aux_livros;

  for(auto aux:livros)
    if(aux->getIdioma()==idioma)
      aux_livros.emplace_back(aux->getTitulo());

  return aux_livros;
}

//Funcao para retornar um vetor de livros com um determinado formato
map <int,string> retorna_livro_formato(int formato, vector <Livro*> livros){
  map <int,string> aux_livros;

  switch(formato){
    case TEletronico:
      for(auto aux:livros){
        try{
            if (typeid(*aux).name()==typeid(Eletronico).name())
              aux_livros.insert(pair<int,string> (aux->getAnopublicacao(),aux->getTitulo()));
        }catch(bad_typeid& e){
          cerr << "Erro na verificação de tipo" << "\n";
          exit (1);
        }catch(...){
          cerr << "Erro na inserção ou obtenção de dados" << "\n";
          exit(1);
        }
      }
      break;
    case TImpresso:
      for(auto aux:livros){
        try{
          if (typeid(*aux).name()==typeid(Impresso).name()){
            aux_livros.insert(pair<int,string> (aux->getAnopublicacao(),aux->getTitulo()));
          }
        }catch(bad_typeid& e){
          cerr << "Erro na verificação de tipo" << "\n";
          exit(1);
        }catch(...){
          cerr << "Erro na inserção ou obtenção de dados" << "\n";
          exit(1);
        }
      }
      break;
    case TAudioBook:
      for(auto aux:livros){
        try{
          if (typeid(*aux).name()==typeid(AudioBook).name())
            aux_livros.insert(pair<int,string> (aux->getAnopublicacao(),aux->getTitulo()));
        }catch(bad_typeid& e){
          cerr << "Erro na verificação de tipo" << "\n";
          exit(1);
        }catch(...){
          cerr << "Erro na inserção ou obtenção de dados" << "\n";
          exit(1);
        }
      }
      break;
  }

  return aux_livros;
}

//Funcao se escritor possui audiobook
bool possui_audiobook(string escritor, vector <Livro*> livros){
  vector <string> vEscritor;
  vector <string>::iterator auxiliar;
  for(auto aux:livros){
    try{
      if(typeid(*aux).name()==typeid(AudioBook).name()){
        vEscritor = aux->getEscritores();
        auxiliar = find(vEscritor.begin(),vEscritor.end(),escritor);
        if(auxiliar!=vEscritor.end())
          return true;
      }
    }catch(bad_typeid& e){
      cerr << "Erro na verificação de tipo" << "\n";
      exit(1);
    }catch(...){
      cerr << "Erro" << "\n";
      exit(1);
    }
  }
  return false;
}

//Funcao que retorna uma colecao de livros, indepentende da midia
vector <Livro*> colecao_livros(string titulo, vector <Livro*> livros){
  vector <Livro*> vLivros;

  for (auto aux:livros)
    if(titulo==aux->getTitulo())
      vLivros.emplace_back(aux);

  return vLivros;
}

//Retorna um vetor de Keywords
set <string> retorna_keywords(vector <Livro*> livros){
    set <string> vKRetorno;
    for(auto aux:livros){
      set <string> auxiliar = aux->getKeywords();
      vKRetorno.insert(auxiliar.begin(),auxiliar.end());
    }
    return vKRetorno;
}

//Retorna a quantidade de livros com uma determinada keyword
int quantidade_livros(string keyword, vector <Livro*> livros){
  int contador = 0;
  set <string> vKeywords;

  for(auto aux:livros){
    vKeywords = aux->getKeywords();
    if(vKeywords.count(keyword))
      contador++;
    vKeywords.clear();
  }

  return contador;
}

//Retorna um Map com os livros com a quantidade de capitulo menor ou igual a digitada
map <string,string> quantidade_capitulos(const int quant, vector <Livro*> livros){
  map <string,string> auxLivros;

  for(auto aux:livros){
    list <string> auxL = aux->getCapitulos();
    int i = auxL.size();
    if(i<=quant){
      auxLivros.insert(pair<string,string> ((aux->getEscritores()).at(0), aux->getTitulo()));
    }
  }
  return auxLivros;
}

//Retorna os livros que estao presentes em mais livrarias do que a digitada
vector <string> retorno_livro_livraria(int& qnt, vector <Livro*> livros){
  vector<string> vaux;
  int cont = 0;
  for(auto aux:livros){
    try{
      if(typeid(*aux).name()==typeid(Impresso).name()){
          Impresso* Iaux = dynamic_cast <Impresso*> (aux);
          if( static_cast <int> (Iaux->getLivrarias().size())>=qnt){ //Convertendo unsigned type to int
            vaux.emplace_back(Iaux->getTitulo());
            cont++;
          }

      }
    }catch(bad_typeid& e){
      cerr << "Erro na verificação de tipo" << "\n";
      exit(1);
    }catch(bad_cast& e){
      cerr << "Erro de conversão de tipo" << "\n";
      exit(1);
    }catch(...){
      cerr << "Erro" << "\n";
      exit(1);
    }
  }
  qnt = cont;
  return vaux;
}

//Imprime no terminal o no arquivo todos os dados do livro
void escreve(string saida, vector <Livro*> livros){
  if(saida=="[T]"){ //Imprime no terminal
    for(auto aux:livros){
      try{
        if (typeid(*aux).name()==typeid(Impresso).name()){
            Impresso* Iaux = dynamic_cast <Impresso*> (aux); //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "Impresso | " << Iaux << endl;
        }else if(typeid(*aux).name()==typeid(Eletronico).name()){
            Eletronico* Eaux = dynamic_cast <Eletronico*> (aux); //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "Eletronico | " << Eaux << endl;
        }else{
            AudioBook* Aaux = dynamic_cast <AudioBook*> (aux); //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "AudioBook | " << Aaux << endl;
        }
      }catch(bad_cast& e){
        cerr << "Erro de conversão de tipo" << '\n';
        exit(1);
      }catch(...){
        cerr << "Erro de impressao" << "\n";
        exit(1);
      }
    }
  }else{ //Imprime no Arquivo
    ofstream arquivo ("Saida.txt",ios::out);
    if(!arquivo){
      cerr << "Erro ao abrir o arquivo" << '\n';
      exit(1);
    }
    for (auto aux:livros){
      try{
        if (typeid(*aux).name()==typeid(Impresso).name()){
            Impresso* Iaux = dynamic_cast <Impresso*> (aux); //Realiza um downcast para imprimir os dados
            arquivo << "Impresso | " << Iaux << endl;
        }else if(typeid(*aux).name()==typeid(Eletronico).name()){
            Eletronico* Eaux = dynamic_cast <Eletronico*> (aux); //Realiza um downcast para imprimir os dados
            arquivo << "Eletronico | " << Eaux << endl;
        }else{
            AudioBook* Aaux = dynamic_cast <AudioBook*> (aux); //Realiza um downcast para imprimir os dados
            arquivo << "AudioBook | " << Aaux << endl;
        }
      }catch(bad_cast& e){
        cerr << "Erro de conversão de tipo" << "\n";
        exit(1);
      }catch(...){
        cerr << "Erro de impressao" << "\n";
        exit(1);
      }
    }
    arquivo.close();
  }
}


//--------------------------------------------------------------------------------------------------------------
//Funcao de separacao
vector<string> split(const string& str, char delim){
  stringstream ss(str);
  string token;
  vector <string> auxiliar;

  while (getline(ss, token, delim))
    auxiliar.emplace_back(token);

  return auxiliar;
}

//funcao de entrada de dados por arquivo
void LeituraArquivo(vector <Livro*>& livros){
  int tipo, anoP, colunas;
  float duracao;
  string xArquivo, sAuxiliarGeral, lixo, sNome, sIdioma, sFormato; //Variaveis auxiliares


  for(int i=0; i<MAXARQ; i++){
    xArquivo = "arquivo"+to_string(i)+".txt";
    ifstream arquivo( xArquivo, ios::in);
    if(!arquivo){
      cerr << "Erro ao Abrir arquivo" << endl;
      exit(1);
    }

    arquivo >> tipo; //Lê o Tipo do livro (1,2,3)
      getline(arquivo,lixo); //Lê o \n
    getline(arquivo,sNome); //Lê o nome do livro
    getline(arquivo,sAuxiliarGeral); //Lê os autores do livro
      vector<string> vEscritores = split(sAuxiliarGeral,';');
    arquivo >> anoP; //Lê o ano de publicacao
      getline(arquivo,lixo); //Lê o \n
    getline(arquivo, sIdioma); //Lê o Idioma do Livro
    getline(arquivo, sAuxiliarGeral);  //Lê as Keywords do Livro
      vector<string> vKeywords = split(sAuxiliarGeral,';');
    getline(arquivo,sAuxiliarGeral); //Lê os capitulos do livro
      vector<string> vCapitulos = split(sAuxiliarGeral,';');

    set <string> stKeywords(vKeywords.begin(),vKeywords.end()); //Cria um set com os dados do vector
    list <string> lCapitulos(vCapitulos.begin(),vCapitulos.end()); //Cria uma lista com os capitulos do vector

    switch(tipo){
      case TImpresso:
      {
        getline(arquivo,sAuxiliarGeral);
        arquivo >> colunas;
        vector <string> vLivrarias = split(sAuxiliarGeral, ';');
        livros.emplace_back(new Impresso(vLivrarias,vEscritores,lCapitulos,stKeywords,sNome,sIdioma,anoP,colunas));
      }
      break;
      case TEletronico:
      {
        string sUrl;
          getline(arquivo,sUrl); getline(arquivo,sFormato);
          livros.emplace_back(new Eletronico(vEscritores,lCapitulos,stKeywords,sNome,sIdioma,sUrl,sFormato,anoP));
      }
      break;
      case TAudioBook:
      {
        arquivo >> duracao;
        getline(arquivo,lixo); getline(arquivo,sFormato);
        livros.emplace_back(new AudioBook(vEscritores,lCapitulos,stKeywords,sNome,sIdioma,sFormato,duracao,anoP));
      }
      break;
      default:
        cerr << "Formato de livro invalido" << endl;
        exit(1);
    }
    arquivo.close();
  }
}
