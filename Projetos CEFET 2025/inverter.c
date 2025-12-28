/*
  ICARO ALVES MOTA FONSECA
  ENTREGA: 31/10/2025
  ARQUIVO INVERTIDO
  REFERENCIAS: 
  https://www2.dcc.ufmg.br/livros/algoritmos/cap3/codigo/c/3.3a3.4-lista-apontadores.c
  https://www.youtube.com/watch?v=USsUSMpNGsM
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME_ARQUIVO 100 //maximo de caracteres para nome do arquivo
#define MAX_TEXTO 5000 //maximo de caracteres dentro do arquivo
#define MAX_PALAVRA_CHAVE 50 //maximo de caracteres que a palavra a ser procurada pelo arquivo pode ter

// ------ Estrutura de Lista do Ziviani ------
typedef int TipoChave;

typedef struct {
  int Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { printf("%d ", Aux -> Item.Chave); //alterei o \n por apenas um espaco por fins esteticos da impressao dos indices para representar a repeticao.
      Aux = Aux -> Prox;
    }
}

// ------ Fim da implementacao do Ziviani ------

// ------ Padronizar o texto do arquivo ------

void Minusculo(char *str) { // nao consegue alterar letras acentuadas
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32; // transforma a string atual em minuscula. Na tabela ASCII, "A" + 32(posicoes) = "a"
    }
  }
}

typedef struct {
  char palavra[MAX_PALAVRA_CHAVE];
  TipoLista ocorrencias;
} TipoPalavra;

void AddVocabulario(TipoPalavra vocab[], int *qtd, char *palavra, int posicao) {
  for (int i = 0; i < *qtd; i++) { //se a palavra ja existir no vocabulario, adiciona mais uma ocorrencia
    if (strcmp(vocab[i].palavra, palavra) == 0) {
      TipoItem item;
      item.Chave = posicao;
      Insere(item, &vocab[i].ocorrencias);
      return;
    }
  }
  // se a palavra ainda nao existir, cria um nova palavra no vocabulario e sua ocorrencia.
  strcpy(vocab[*qtd].palavra, palavra);
  FLVazia(&vocab[*qtd].ocorrencias);
  TipoItem item;
  item.Chave = posicao;
  Insere(item, &vocab[*qtd].ocorrencias);
  (*qtd)++;
}

int PesquisaBi(TipoPalavra vocab[], int qtd, char *palavra) { //funcao de busca binaria/ pesquisa binaria para encontrar o padrao
  int esq = 0, dir = qtd - 1;
  while (esq <= dir) {
    int meio = (esq + dir) / 2;
    int cmp = strcmp(vocab[meio].palavra, palavra);
      if (cmp == 0) return meio;  // encontrou
      else if (cmp < 0) esq = meio + 1;
      else dir = meio - 1;
    }
    return -1;
}

void Alfabetica(TipoPalavra vocab[], int qtd) { //ordena as palavras em ordem alfabetica.
  for (int i = 0; i < qtd - 1; i++) {
    for (int j = i + 1; j < qtd; j++) {
      if (strcmp(vocab[i].palavra, vocab[j].palavra) > 0) {
        // Troca os elementos (palavra e lista de ocorrências)
        TipoPalavra temp = vocab[i];
        vocab[i] = vocab[j];
        vocab[j] = temp;
      }
    }
  }
}

//nao exibe acentuacao das letras como á é í ó â ê î ô etc
int main(){
  char nome_arquivo[MAX_NOME_ARQUIVO];
  FILE *arquivo_de_texto;

  printf("Nome do arquivo a ser aberto, exemplo: (arquivo.txt):\n");

  if (fgets(nome_arquivo, MAX_NOME_ARQUIVO, stdin) == NULL) {
    printf("Erro ao ler o nome do arquivo.\n");
    exit(0);
  }

  nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; // retira o \n que vem junto ao dar enter no nome

  arquivo_de_texto = fopen(nome_arquivo, "r");

  if (arquivo_de_texto == NULL) {
    printf("Nao foi possivel concluir a abertura do arquivo!\n");
    exit(0);
  }

  char palavra_chave[MAX_PALAVRA_CHAVE];
  char texto_escrito[MAX_TEXTO];

  if (fgets(palavra_chave, MAX_PALAVRA_CHAVE, arquivo_de_texto) == NULL || //le a primeira linha e posiciona o \0 apos o \n (vai para segunda linha)
      fgets(texto_escrito, MAX_TEXTO, arquivo_de_texto) == NULL){ //le a linha posterior e posiciona o \0 apos o \n (vai para "terceira linha")
    printf("Erro ao reconhecer a palavra chave ou o texto do arquivo.\n");
    fclose(arquivo_de_texto);
    exit(0);
  }

  palavra_chave[strcspn(palavra_chave, "\n")] = '\0'; // mesma situacao que o nome_arquivo e pra texto_escrito.
  texto_escrito[strcspn(texto_escrito, "\n")] = '\0';

  /*LEMBRETE: no pdf nao tem nada falando sobre normalizar o texto antes de realizar o arq. invertido. 
  Entao, seguindo o padrao do pdf, vou considerar TODOS os caracteres como validos para a contagem de indice.
  */

  Minusculo(palavra_chave); // chama funcao para transformar todo texto em minusculo, facilitando a verificacao de quantas vezes repete
  Minusculo(texto_escrito);

  TipoPalavra vocabulario[MAX_TEXTO];
  int qtd = 0;
  int posicao;
  char *token = strtok(texto_escrito, " ,.;:!?\n"); //tempo acabando, fiz essa "limpeza" na pontuacao de maneira um pouco porca, mas tava me incomodando exibir as palavras com um . ou , no final
  
  while (token != NULL) {
    //calcula a posicao real da palavra no texto original
    posicao = token - texto_escrito + 1;  // comeca em 1, não em 0.
    AddVocabulario(vocabulario, &qtd, token, posicao);
    token = strtok(NULL, " ,.;:!?\n"); // linha 156
  }

  Alfabetica(vocabulario, qtd); // chama a funcao para fazer a organizacao da lista de palavras

  printf("\nArquivo Invertido:\n");
  for (int i = 0; i < qtd; i++) {
    printf("%s: ", vocabulario[i].palavra);
    Imprime(vocabulario[i].ocorrencias);
    printf("\n");
  }

  int indice = PesquisaBi(vocabulario, qtd, palavra_chave);
  if (indice != -1) {
    printf("\nOcorrencias do padrao \"%s\": ", palavra_chave);
    Imprime(vocabulario[indice].ocorrencias);
    printf("\n");
}
 
  fclose(arquivo_de_texto);

  return 0;
}