/*
    Alunos:
    André Junqueira Espíndola Botelho - 20223008025
    Ícaro Alves Mota Fonseca - 20213012973
    Atividade:
    Exercício Intercalação Listas - para 20/10/2025


    Bibliografia:
    Projetos de Algoritmos com implementacoes em Pascal e C, Nivio Ziviani.
    https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
    https://www.ibm.com/docs/pt-br/i/7.6.0?topic=functions-fgets-read-string
    https://www.reddit.com/r/cprogramming/comments/1jpuket/i_am_trying_to_implement_a_link_list_in_c_using/?tl=pt-br
*/


#include <stdio.h>
#include <stdlib.h>

// Cada célula tem um item (Item) e um ponteiro que aponta para o próximo elemento da lista (Prox).
typedef struct Celula {
    int Item;
    struct Celula *Prox;
} Celula;

typedef struct {
    Celula *Primeiro;
    Celula *Ultimo;
} TipoLista;

// Alocação Dinâmica para a célula cabeça (Celula); ponteiros ‘Primeiro’ e ‘Ultimo’ apontam para a célula cabeça.
void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = (Celula *) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

// Retorna ‘1’ se a lista estiver vazia, ‘0’ caso a lista não estiver vazia.
int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}

// Ponteiro ‘Ultimo’ sendo atualizado para apontar para o novo nó criado.
void Insere(TipoLista *Lista, int x) {
    Lista->Ultimo->Prox = (Celula *) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

// Imprime todos valores após a célula cabeça.
void Imprime(TipoLista *Lista) {
    Celula *Aux = Lista->Primeiro->Prox;
    int Primeiro = 1;
    printf("Lista final: ");
    while (Aux != NULL) {
        if (!Primeiro) printf(",");
        printf("%d", Aux->Item);
        Primeiro = 0;
        Aux = Aux->Prox;
    }
    printf("\n");
}

// Recebe como parâmetro duas listas encadeadas e ordenadas em ordem crescente.
// Retorna uma nova lista com os elementos das duas em ordem crescente.
TipoLista IntercalaDuas(TipoLista *l1, TipoLista *l2) {
    TipoLista resultado;
    FLVazia(&resultado);

    Celula *a = l1->Primeiro->Prox;
    Celula *b = l2->Primeiro->Prox;

    while (a != NULL && b != NULL) {
        if (a->Item <= b->Item) {
            Insere(&resultado, a->Item);
            a = a->Prox;
        } else {
            Insere(&resultado, b->Item);
            b = b->Prox;
        }
    }
    while (a != NULL) {
        Insere(&resultado, a->Item);
        a = a->Prox;
    }

    while (b != NULL) {
        Insere(&resultado, b->Item);
        b = b->Prox;
    }

    return resultado;
}

// Intercala duas listas por vez, acumulando o resultado em ‘resultado’.
// Retorna ‘resultado’.
TipoLista IntercalaKListas(TipoLista *listas, int K) {
    if (K == 0) {
        TipoLista vazia;
        FLVazia(&vazia);
        return vazia;
    }

    TipoLista resultado = listas[0];

    for (int i = 1; i < K; i++) {
        TipoLista temp = IntercalaDuas(&resultado, &listas[i]);
        resultado = temp;
    }

    return resultado;
}






// # Exemplo de arquivo:
// 3
// 1 4 5
// 1 3 4
// 2 6
// ## Saída esperada:
// Digite o nome do arquivo de entrada: teste.txt
// Lista final: 1,1,2,3,4,4,5,6

int main() {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivo);

    FILE *arquivo = fopen(nomeArquivo, "r");

    int K;

    fscanf(arquivo, "%d", &K);

    TipoLista *listas = (TipoLista *) malloc(K*sizeof(TipoLista));
   
    for (int i = 0; i < K; i++) {
        FLVazia(&listas[i]);
        int num;

        while (fscanf(arquivo, "%d", &num) == 1) {
            Insere(&listas[i], num);
            int c = fgetc(arquivo);
            if (c == '\n' || c == EOF) break;
            ungetc(c, arquivo);
        }
    }

    fclose(arquivo);

    TipoLista final = IntercalaKListas(listas, K);

    Imprime(&final);

    free(listas);
    return 0;
}