#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME_ARQUIVO 100
#define MAX_TEXTO 5000
#define MAX_PALAVRA 50
#define MAX_PALAVRAS 1000

// --------------------
// Estruturas do Ziviani
// --------------------
typedef int TipoChave;

typedef struct {
  int Chave;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) {
  Lista->Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista) {
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) {
  Lista->Ultimo->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

// imprime os elementos da lista de posições
void ImprimeLista(TipoLista Lista) {
  TipoApontador Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) {
    printf("%d", Aux->Item.Chave);
    if (Aux->Prox != NULL) printf(" ");
    Aux = Aux->Prox;
  }
}

// --------------------
// Estrutura para o vocabulário
// --------------------
typedef struct {
  char palavra[MAX_PALAVRA];
  TipoLista ocorrencias;
} TipoPalavra;

// --------------------
// Funções auxiliares
// --------------------

// Converte para minúsculo
void ParaMinusculo(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower((unsigned char) str[i]);
  }
}

// Remove pontuação
void LimparPontuacao(char *str) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    if (isalnum((unsigned char) str[i]) || str[i] == 'ç')
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
}

// Adiciona palavra ao vocabulário ou insere posição se já existir
void AdicionarPalavra(TipoPalavra vocab[], int *qtd, char *palavra, int posicao) {
  for (int i = 0; i < *qtd; i++) {
    if (strcmp(vocab[i].palavra, palavra) == 0) {
      TipoItem item;
      item.Chave = posicao;
      Insere(item, &vocab[i].ocorrencias);
      return;
    }
  }

  // nova palavra
  strcpy(vocab[*qtd].palavra, palavra);
  FLVazia(&vocab[*qtd].ocorrencias);
  TipoItem item;
  item.Chave = posicao;
  Insere(item, &vocab[*qtd].ocorrencias);
  (*qtd)++;
}

// comparação lexicográfica para ordenar
int CompararPalavras(const void *a, const void *b) {
  return strcmp(((TipoPalavra *)a)->palavra, ((TipoPalavra *)b)->palavra);
}

// busca binária no vocabulário
int BuscaBinaria(TipoPalavra vocab[], int n, char *chave) {
  int inicio = 0, fim = n - 1, meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;
    int cmp = strcmp(chave, vocab[meio].palavra);
    if (cmp == 0)
      return meio;
    else if (cmp < 0)
      fim = meio - 1;
    else
      inicio = meio + 1;
  }
  return -1;
}

// --------------------
// Programa principal
// --------------------
int main() {
  char nome_arquivo[MAX_NOME_ARQUIVO];
  FILE *arquivo;

  printf("Insira o nome do arquivo a ser aberto:\n");

  if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) == NULL) {
    printf("Erro ao ler o nome do arquivo.\n");
    return 0;
  }

  nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';

  arquivo = fopen(nome_arquivo, "r");
  if (arquivo == NULL) {
    printf("Nao foi possivel abrir o arquivo!\n");
    return 0;
  }

  // leitura do padrão e texto
  char padrao[MAX_PALAVRA];
  char texto[MAX_TEXTO];

  if (fgets(padrao, sizeof(padrao), arquivo) == NULL ||
      fgets(texto, sizeof(texto), arquivo) == NULL) {
    printf("Erro ao ler o conteudo do arquivo.\n");
    fclose(arquivo);
    return 0;
  }

  padrao[strcspn(padrao, "\n")] = '\0';
  texto[strcspn(texto, "\n")] = '\0';
  fclose(arquivo);

  ParaMinusculo(padrao);
  ParaMinusculo(texto);

  TipoPalavra vocab[MAX_PALAVRAS];
  int qtd_vocab = 0;

  char palavra_atual[MAX_PALAVRA];
  int idx = 0, posicao = 1;

  // percorre o texto e identifica palavras + posições
  for (int i = 0; texto[i] != '\0'; i++, posicao++) {
    if (isalpha((unsigned char) texto[i]) || texto[i] == 'ç') {
      palavra_atual[idx++] = texto[i];
    } else {
      if (idx > 0) {
        palavra_atual[idx] = '\0';
        LimparPontuacao(palavra_atual);
        AdicionarPalavra(vocab, &qtd_vocab, palavra_atual, posicao - idx);
        idx = 0;
      }
    }
  }

  if (idx > 0) {
    palavra_atual[idx] = '\0';
    LimparPontuacao(palavra_atual);
    AdicionarPalavra(vocab, &qtd_vocab, palavra_atual, posicao - idx);
  }

  // ordena vocabulário
  qsort(vocab, qtd_vocab, sizeof(TipoPalavra), CompararPalavras);

  // imprime arquivo invertido
  printf("\nArquivo invertido:\n");
  for (int i = 0; i < qtd_vocab; i++) {
    printf("%s ", vocab[i].palavra);
    ImprimeLista(vocab[i].ocorrencias);
    printf("\n");
  }

  // busca binária do padrão
  int pos_encontrada = BuscaBinaria(vocab, qtd_vocab, padrao);

  printf("\nOcorrencias do padrao \"%s\": ", padrao);
  if (pos_encontrada != -1) {
    ImprimeLista(vocab[pos_encontrada].ocorrencias);
  } else {
    printf("nenhuma ocorrencia encontrada");
  }
  printf("\n");

  return 0;
}
