#include <stdio.h>
#include <stdlib.h>

#define MAX_MAPEAR 1000

int main() {
    int **armazenador;
    int num;

    scanf("%d", &num);

    armazenador = (int **) malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        armazenador[i] = (int *) malloc(num * sizeof(int));
        if (armazenador[i] == NULL) {
            return 1;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num ; j++)
        {
            scanf("%d ", armazenador[i][j]);
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= num ; j++)
        {
            printf("%d ", *armazenador[0]);
        }
    }

    printf("\n");

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j <= num ; j++)
    //     {
    //         printf("%d ", **armazenador);
    //     }
    // }
}