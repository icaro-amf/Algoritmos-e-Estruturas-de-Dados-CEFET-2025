#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas = 3;
    int colunas = 4;
    int i, j;

    // # Alocação -------------------------------------------------------------------------------------------------------------
    
    // ## Alocando o array de ponteiros (as linhas)
    int **matriz = (int **)malloc(linhas * sizeof(int *));

    // ## Alocando as colunas para cada linha
    for (i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }

    // # Preenchendo a matriz -------------------------------------------------------------------------------------------------------------
    int contador = 1;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = contador++;
        }
    }

    // # Exibindo a matriz -------------------------------------------------------------------------------------------------------------
    printf("Matriz %dx%d:\n", linhas, colunas);
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }

    
    
    // # Liberação de Memória -------------------------------------------------------------------------------------------------------------
    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);



    return 0;
}