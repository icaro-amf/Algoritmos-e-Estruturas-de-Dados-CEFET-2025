#include <stdio.h>
#include <stdlib.h>
#define tamanho_alocado 20

void libera_matriz(int num, int **matriz);
void operacao(int num, int **matriz, int *camada,int *caixa);

int main()
{
    int n;
    int i, j;
    int camada=0, caixa=0;

    scanf("%d", &n);

    if (n > tamanho_alocado)
    {
        printf("Erro: n maior que tamanho_alocado\n");
        return 1;
    }

    int **matriz = calloc(tamanho_alocado, sizeof(int*));

    for (i = 0; i < n; i++)
    {

        matriz[i] = calloc(tamanho_alocado, sizeof(int));

    }
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= i; j++) 
        {

            scanf("%d", &matriz[i][j]);

        }
    }

    operacao(n, matriz, &camada, &caixa);
    printf("Resposta: camada %d, caixa %d.", camada, caixa);
    libera_matriz(n, matriz);

    printf("\n");
    return 0;
}

void libera_matriz(int num, int **matriz){
    int i;
    for (i = 0; i < num; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void operacao(int num, int **matriz, int *camada,int *caixa){
    int i,j;
    int soma_camada = matriz [0][0];
    int maior_valor = 0;

    *camada = 0;
    *caixa = 0;

    for (i = 0; i < num; i++)
    {
        int soma_atual = 0;
        
        for (j = 0; j <= i; j++)
        {
            int soma = matriz[i][j] + soma_camada;

            if(soma > maior_valor){
                maior_valor = soma;
                *camada = i + 1;
                *caixa = j + 1;
            }

            soma_atual = matriz[i][j] + soma_atual;

        }

        soma_camada = soma_atual + soma_camada;
        
    }
}