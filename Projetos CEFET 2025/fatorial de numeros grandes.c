#include <stdio.h>
#include <stdlib.h>
#define tamanho_alocado 36000


int multiplicacaofat(int *vetor, int tamanho, int numero){
    int auxiliar = 0;
    int operacao, i;
    for(i = 0; i < tamanho; i++){
        operacao = vetor[i] * numero + auxiliar;
        vetor[i] = operacao % 10;
        auxiliar = operacao / 10;
    }
    while (auxiliar > 0){
        vetor[tamanho] = auxiliar % 10;
        auxiliar /= 10;
        tamanho++;
    }
    return tamanho;
}


int main(){
    int n;
    scanf("%d", &n);

    int *vetor = calloc(tamanho_alocado, sizeof(int));

    if(n < 0)
    {
        printf("Nao existe o fatorial de numeros negativos");
    }
    
    else if(n < 2)
    {
        printf("1");
    }

    else
    {
        vetor[0]  = 2;
        int tamanho = 1;
        int i;
        for(i = n; i > 2; i--)
        {
            tamanho = multiplicacaofat(vetor, tamanho, i);
        }

        printf("Resultado: ");
        for(i = tamanho - 1; i >= 0; i--)
        {
            printf("%d", vetor[i]);
        }

        free(vetor);

    }

    printf("\n");
    return 0;

}