#include <stdio.h>
#include <stdlib.h>

#define MAX_MAPEAR 1000

int main() {
    int **armazenador, *vetor_num_user;
    int num;

    scanf("%d", &num);

    vetor_num_user = (int *) malloc(num * sizeof(int));
    if (vetor_num_user == NULL) {
        return 1;
    }

    for (int i = 0; i < num; i++) {
        scanf("%d", &vetor_num_user[i]);
    }

    armazenador = (int **) malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        armazenador[i] = (int *) malloc(num * sizeof(int));
        if (armazenador[i] == NULL) {
            return 1;
        }
    }

    int mapaValor[MAX_MAPEAR];
    int mapaIndice[MAX_MAPEAR];
    int mapeador = 0;
    int col = 0;

    //mapear os valores dentro do vetor que sao diferentes ou iguais
    for (int i = 0; i < num; i++) {
        int valor = vetor_num_user[i];
        int ja_existe = 0;
        for (int j = 0; j < mapeador; j++) {
            if (mapaValor[j] == valor) {
                ja_existe = 1;
                break;
            }
        }
        if (ja_existe == 0) {
            mapaValor[mapeador++] = valor;
        }
    }

    //ordenar os valores diferentes EM ORDEM CRESCENTE
    for (int i = 0; i < mapeador - 1; i++) {
        for (int j = i + 1; j < mapeador; j++) {
            if (mapaValor[i] > mapaValor[j]) {
                int temp = mapaValor[i];
                mapaValor[i] = mapaValor[j];
                mapaValor[j] = temp;
            }
        }
    }

    //atribui os indices aos segmetos ordenados
    for (int i = 0; i < mapeador; i++) {
        mapaIndice[i] = i + 1;
    }

    //faz os agrupamentos por segmentos iguais
    for (int i = 0; i < num; ) {
        int valor = vetor_num_user[i];
        int cont = 1;

        //verifica a repeticao em sequencia do mesmo valor
        while (i + cont < num && vetor_num_user[i + cont] == valor) {
            cont++;
        }

        //encontra e atribui o indice do segmento correspondente ao valor
        int indice = 0;
        for (int j = 0; j < mapeador; j++) {
            if (mapaValor[j] == valor) {
                indice = mapaIndice[j];
                break;
            }
        }

        armazenador[0][col] = indice;
        armazenador[1][col] = cont;

        col++;
        i += cont;
    }

    for (int j = 0; j < col; j++) {
        if(j == col - 1) printf("%d", armazenador[0][j]);
        else printf("%d ", armazenador[0][j]);
    }
    printf("\n");

    for (int j = 0; j < col; j++) {
        if(j == col - 1) printf("%d", armazenador[1][j]);
        else printf("%d ", armazenador[1][j]);
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        free(armazenador[i]);
    }

    free(armazenador);
    free(vetor_num_user);

    return 0;
}
