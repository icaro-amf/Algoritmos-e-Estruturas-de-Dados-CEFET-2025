#include <stdio.h>

void dec2bin(int dec){
    if(dec == 1){
        printf("%d", dec);
    }
    else{
        dec2bin(dec / 2);
        printf("%d", dec % 2);
    }

}

int main(){
    
    int decimal;

    printf("Digite um numero inteiro: ");
    scanf("%d", &decimal);
    
    printf("Resultado: ");

    dec2bin(decimal);

    printf("\n");

    return 0;
}