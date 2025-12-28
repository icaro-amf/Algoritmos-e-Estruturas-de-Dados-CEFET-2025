#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int Item1; // segmento
    int Item2; // quantidade de repetições do segmento
    struct Celula *Prox;
} Celula;

typedef struct {
    Celula *Primeiro;
    Celula *Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = (Celula *) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

void Insere(int item1, int item2, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Celula *) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item1 = item1;
    Lista->Ultimo->Item2 = item2;
    Lista->Ultimo->Prox = NULL;
}

void Imprime(TipoLista Lista) {
    Celula *Aux = Lista.Primeiro->Prox;
    while (Aux != NULL) {
        printf("%d ", Aux->Item1);
        Aux = Aux->Prox;
    }
    printf("\n");

    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL) {
        printf("%d ", Aux->Item2);
        Aux = Aux->Prox;
    }
    printf("\n");
}

void LiberaLista(TipoLista *Lista) {
    Celula *Aux = Lista->Primeiro;
    while (Aux != NULL) {
        Celula *Temp = Aux;
        Aux = Aux->Prox;
        free(Temp);
    }
}

int main() {
    int num;
    scanf("%d", &num);

    int *vetorteste = (int *) malloc(num * sizeof(int));
    if (vetorteste == NULL) {
        return 1;
    }

    for (int i = 0; i < num; i++) {
        scanf("%d", &vetorteste[i]);
    }

    TipoLista Lista;
    FLVazia(&Lista);

    // vetor para mapear o segmento
    int mapaNum[1000];
    int totalMapeados = 0;

    int segmento = 0;

    int i = 0;
    while (i < num) {
        int valor = vetorteste[i];
        int cont = 1;

        while (i + 1 < num && vetorteste[i + 1] == valor) {
            i++;
            cont++;
        }

        // verificar se o segmento ja existe
        int indice = 0;
        int encontrado = 0;

        for (int j = 0; j < totalMapeados; j += 2) {
            if (mapaNum[j] == valor) {
                indice = mapaNum[j + 1];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            segmento++;
            indice = segmento;
            mapaNum[totalMapeados++] = valor;
            mapaNum[totalMapeados++] = indice;
        }

        Insere(indice, cont, &Lista);

        i++;
    }

    Imprime(Lista);

    printf("\n");

    LiberaLista(&Lista);
    free(vetorteste);
    
    return 0;
}
