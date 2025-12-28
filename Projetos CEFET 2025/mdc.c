#include <stdio.h>

int mdc(int a, int b) {
	
    if (b == 0){
    	
		return a;
	}
        
    return mdc(b, a % b);
}

/*Bibliografia: https://www.blogcyberini.com/2018/03/algoritmo-de-euclides-implementacoes-e.html*/

int main(){

    int a, b;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &a, &b);
    
    printf("Resultado: %d", mdc(a,b));

    printf("\n");

    return 0;
}