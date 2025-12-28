#include <stdio.h>

void ponteiroTeste(int teste){
    teste += 5;
    printf("teste: %d\n", teste);
}

int main(){
    int a = 10;
    printf("a 1: %d\n", a);
    ponteiroTeste(a);
    printf("a 2: %d\n", a);
}