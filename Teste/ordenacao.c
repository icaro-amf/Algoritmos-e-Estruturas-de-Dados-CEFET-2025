#include <stdio.h>
#include <stdlib.h>
#define tamanho_alocado 20

int main()
{
    int n;
    int i,j;
    
    scanf("%d", &n);
    
    int **matriz = calloc(tamanho_alocado, sizeof(int*));

    for (i = 0; i < n; i++)
    {
        matriz[i] = calloc(tamanho_alocado, sizeof(int));
    }
    
    for (i = 0; i < n ; i++)
    {

        for(j = 0; j <= i; j++){
            scanf("%d", &matriz[i][j]);
            
        }

    }

    for (i = 0; i < n; i++)
    {
        for(j = 0; j <= i; j++){
            printf("%d\n",matriz[i][j]);
        }
    }
    

    free(matriz);
    
}