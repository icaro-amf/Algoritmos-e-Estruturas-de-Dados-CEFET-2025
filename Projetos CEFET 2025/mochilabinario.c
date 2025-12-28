#include <stdio.h>
#include <stdlib.h>

int caso_otimo(int max, int itens, int *peso, int*valor);

int main(){
    int capacidade; // capacidade da mochila em kg
    int num_itens; //quantidade de itens que o usuario ira dar como opcoes
    int *peso, *valor, *solucao;
    
    scanf("%d",&capacidade);
    scanf("%d",&num_itens);

    peso = (int *) malloc(num_itens*sizeof(int));
    valor = (int *) malloc(num_itens*sizeof(int));
    solucao = (int *) malloc(num_itens * sizeof(int));

    if(peso == NULL || valor == NULL || solucao == NULL){ // evita segmentacao
        return 1;
    }

    for(int i = 0; i < num_itens; i++){ // captar os pesos e valores de cada um dos itens pedido / i comeca em 1 para o programa solicitar exatamente o numero digitado pelo usuario em num_itens
        scanf("%d %d", &peso[i], &valor[i]);
    }

    for (int i = 0; i < num_itens; i++){ // recebe a tentativa de solucao do usuario
        scanf("%d", &solucao[i]);
    }

    
    int peso_total = 0, valor_total = 0;
    for (int i = 0; i < num_itens; i++){ // calcula peso e valor total da solucao fornecida para fazer futuras comparacoes para solucaos
        if (solucao[i] == 1) {
            peso_total += peso[i];
            valor_total += valor[i];
        }
    }

    if (peso_total > capacidade){

        printf("Solucao inviavel.\n");

    } 

    else{
        int valor_otimo = caso_otimo(capacidade, num_itens, peso, valor);

        if (valor_total == valor_otimo)
            printf("Solucao otima.\n");
        else
            printf("Solucao viavel mas nao otima.\n");
    }

    free(peso);
    free(valor);
    free(solucao);

    return 0;
}

int caso_otimo(int max, int itens, int *peso, int*valor){
        
    if(max == 0 || itens == 0){
        return 0;
    }

    if(peso[itens-1] > max){
        return caso_otimo(max, itens-1, peso, valor);
    }

    int incluir = valor[itens - 1] + caso_otimo(max - peso[itens - 1], itens - 1, peso, valor); //soma o valor do item com o que cabe no espaco restante
    int ignorar = caso_otimo(max, itens - 1, peso, valor); //calcula o maximo sem o item

    if(incluir > ignorar){
        return incluir;
    }
    else{
        return ignorar;
    }
}