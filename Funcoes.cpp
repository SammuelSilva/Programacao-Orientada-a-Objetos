#include "Funcoes.hpp"

//Retorna um vetor de livro com um determinado idioma
vector <Livro*> retorna_livro_idioma(const string& idioma, vector <Livro*>& livros){
  vector <Livro*> aux_livros (livros.size());
  vector <Livro*>::iterator auxiliar = std::copy_if(livros.begin(), livros.end(),aux_livros.begin(),[&idioma](const Livro* auxLivro){return (auxLivro->getIdioma())==idioma;});
  aux_livros.resize(std::distance(aux_livros.begin(),auxiliar));

  return aux_livros;
}

//Funcao para retornar um vetor de livros do formato Eletronico
map <int,Livro*> retorna_livro_formato(vector <Livro*>& livros){
  map <int,Livro*> aux_livros;

  std::for_each(livros.begin(),livros.end(),[&aux_livros](Livro* aux){
    try{
      if (typeid(*aux).name()==typeid(Eletronico).name())
        aux_livros.insert(std::pair<int,Livro*> (aux->getAnopublicacao(),aux));
    }catch(bad_typeid& e){
      cerr << "Erro na verificação de tipo" << "\n";
      exit (1);
    }catch(...){
      cerr << "Erro na inserção ou obtenção de dados" << "\n";
      exit(1);
    }
  });

  return aux_livros;
}

//Funcao se escritor possui audiobook
bool possui_audiobook(const string& escritor, vector <Livro*>& livros){
  vector <Livro*>aux_livros(livros.size());
  bool flag = false;
  std::for_each(livros.begin(),livros.end(),[&escritor,&livros,&flag](const Livro* auxLivro){
    if(typeid(*auxLivro).name()==typeid(AudioBook).name()){
      vector<string> vEscritor = auxLivro->getEscritores();
      vector <string>::iterator aux = (find(vEscritor.begin(),vEscritor.end(),escritor));
      if(aux!=vEscritor.end())
        flag = true;
    }
  });
  return flag;
}

//Funcao que retorna uma colecao de livros, indepentende da midia
vector <Livro*> colecao_livros(const string& titulo, vector <Livro*>& livros){
  vector <Livro*> vLivros(livros.size());
  vector <Livro*>::iterator auxiliar = livros.begin();
  auxiliar=std::copy_if(auxiliar, livros.end(), vLivros.begin(),[&titulo](const Livro* comp){
      return (comp->getTitulo()==titulo);
  });
  vLivros.resize(std::distance(vLivros.begin(),auxiliar));

  return vLivros;
}

//Retorna um vetor de Keywords
set <string> retorna_keywords(vector <Livro*>& livros){
    set <string> vKRetorno;
    for(auto aux:livros){
        set <string> auxiliar = aux->getKeywords();
        vKRetorno.insert(auxiliar.begin(),auxiliar.end());
    }
    return vKRetorno;
}

//Retorna a quantidade de livros com uma determinada keyword
int quantidade_livros(const string& keyword, vector <Livro*>& livros){
  int contador = 0;
  std::for_each(livros.begin(),livros.end(),[&keyword,&livros,&contador](Livro* aux){
    set <string> vKeywords = aux->getKeywords();
    contador+=(vKeywords.count(keyword));
    vKeywords.clear();
  });
  return contador;
}

//Retorna um Map com os livros com a quantidade de capitulo menor ou igual a digitada
multimap <string,Livro*> quantidade_capitulos(const int& quant, vector <Livro*>& livros){
  multimap <string,Livro*> auxLivros;
  std::for_each(livros.begin(),livros.end(),[&quant,&auxLivros](Livro* aux){
    list <string> auxL = aux->getCapitulos();
    int i = auxL.size();
    if(i<=quant){
      auxLivros.insert(pair<string,Livro*> ((aux->getEscritores()).at(0), aux));
    }
  });

  return auxLivros;
}

//Retorna os livros que estao presentes em mais livrarias do que a digitada
vector <string> retorno_livro_livraria(int& qnt, vector <Livro*>& livros){
  vector<string> vaux;
  int cont = 0;
  std::for_each(livros.begin(),livros.end(),[&qnt,&cont,&vaux](Livro* auxLivro){
    try{
      if(typeid(*auxLivro).name()==typeid(Impresso).name()){
          if( static_cast <int> (((dynamic_cast <Impresso*> (auxLivro))->getLivrarias()).size())>=qnt){ //Convertendo unsigned type to int
            vaux.emplace_back((dynamic_cast <Impresso*> (auxLivro))->getTitulo());
            cont++;
            return true;
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
    return false;
  });
  qnt = cont;
  return vaux;
}

//Imprime no terminal o no arquivo todos os dados do livro
void escreve(const string& saida, vector <Livro*>& livros){
  if(saida=="[T]"){ //Imprime no terminal
    for(auto aux:livros){
      try{
        if (typeid(*aux).name()==typeid(Impresso).name()){
            //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "Impresso   | " << dynamic_cast <Impresso*> (aux) << endl;
        }else if(typeid(*aux).name()==typeid(Eletronico).name()){
            //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "Eletronico | " << dynamic_cast <Eletronico*> (aux) << endl;
        }else{
            //Realiza um DownCast para realizar a impressa odos dados das derivadas
            cout << "AudioBook  | " << dynamic_cast <AudioBook*> (aux) << endl;
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
            //Realiza um downcast para imprimir os dados
            arquivo << "Impresso | " << dynamic_cast <Impresso*> (aux) << endl;
        }else if(typeid(*aux).name()==typeid(Eletronico).name()){
            //Realiza um downcast para imprimir os dados
            arquivo << "Eletronico | " << dynamic_cast <Eletronico*> (aux) << endl;
        }else{
            //Realiza um downcast para imprimir os dados
            arquivo << "AudioBook | " << dynamic_cast <AudioBook*> (aux) << endl;
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

bool retorna_iterador(const string& nome,vector <Livro*>& livros, vector <Livro*>::iterator& auxiliar,string tipo){

  auxiliar = std::find_if(livros.begin(), livros.end(), [&nome,&tipo](const Livro* comp){
     return (comp->getTitulo() == nome && typeid(*comp).name()==tipo);});
   if(auxiliar!=livros.end())
     return true;

  return false;
}

void retorna_mapeamento(vector <Livro*>& livros, const map <string,string>& mapeamento){
  std::for_each(livros.begin(),livros.end(),[&mapeamento](Livro* livro){ //Função lambda que recebe mapeamento por referencia e UM livro
    livro->setIdioma((mapeamento.find(livro->getIdioma()))->second);
  });
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
    xArquivo = to_string(i+1)+".txt";
    ifstream arquivo( xArquivo, ios::in);
    if(!arquivo){
      cerr << "Erro ao Abrir arquivo" << endl;
      exit(1);
    }

    arquivo >> tipo; //Lê o Tipo do livro (1,2,3)
      tipo-=1;
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
