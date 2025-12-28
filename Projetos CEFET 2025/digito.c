#include <stdio.h>

int Digitos(int n){
    int cont = 1;

    if (n < 10){
        return cont;
    }

    else{
        return cont + Digitos(n / 10);
    }
}

int main(){

    int num;

    printf("Digite um numero inteiro: ");
    scanf("%d", &num);

    printf("Resultado: %d", Digitos(num));

    printf("\n");

    return 0;

}

