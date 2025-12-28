#include <stdio.h>
#include <stdlib.h>

int main(){
    int **armazenador, *vetorteste;
    int num;

    scanf("%d", &num);
    
    vetorteste = (int *)malloc(num*sizeof(int));

    if(vetorteste == NULL)
    {
        return 1;
    }

    for (int i = 0; i < num; i++) 
    {
        scanf("%d", &vetorteste[i]);
    }

    armazenador = (int **)malloc(2*sizeof(int *));

    for (int i = 0; i < 2; i++)
    {
        armazenador[i] = (int *)malloc(num*sizeof(int));
    }
    
    if(armazenador == NULL)
    {
        return 1;
    }

    int k = 1;
    int comparador = 0;
    int col = 0;

    //separa em segmentos
    while (comparador < num)
    {
        int inicio = comparador;
        int cont = 1;

        // conta quantos numeros iguais seguidos
        while (comparador + 1 < num && vetorteste[comparador + 1] == vetorteste[inicio])
        {
            comparador++;
            cont++;
        }

        // marca o numero do segmento e o tamanho em todas as posicoes desse trecho
        for (int j = inicio; j <= comparador; j++) {
            armazenador[0][col] = k;
            armazenador[1][col] = cont;
        }

        k++;
        comparador++;
        col++;
    }

    for (int j = 0; j < col; j++) {
        printf("%d ", armazenador[0][j]);
    }
    printf("\n");

    for (int j = 0; j < col; j++) {
        printf("%d ", armazenador[1][j]);
    }
    printf("\n");

    for (int i = 0; i < 2; i++)
    {
        free(armazenador[i]);
    }
    
    free(armazenador);
    free(vetorteste);
    
    return 0;
}