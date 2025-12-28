#include <stdio.h>

int mult(int base, int exp){
    int resultado;

    if(exp == 0){
        resultado = 1;

        return resultado;
    }

    else{
        resultado = base * mult(base, exp-1);

        return resultado;
    }
}

int main(){

    int x, n;

    printf("Digite a base e o expoente inteiros: ");
    scanf("%d %d", &x, &n);
    
    printf("Resultado: %d", mult(x,n));

    printf("\n");

    return 0;
}