#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1000

int qtd_char(const char cifra[]) {
    int i = 0;
    while (cifra[i] != '\0') i++;
    return i;
}

//permuta blocos de 2 (troca 1º com último, 3º com antepenúltimo, etc.)
char *espelhar_blocos(char *cifra) {
    char a0, a1;
    int q = qtd_char(cifra);
    int n_blocos = q / 2;
    // percorre blocos de 2, saltando de 2 blocos (índices de bloco pares: 0,2,4,...)
    for (int b = 0; b < n_blocos / 2; b += 2) {
        int b2 = n_blocos - 1 - b; 
        int i = 2 * b;
        int j = 2 * b2;

        if (i + 1 >= q || j + 1 >= q) break;

        a0 = cifra[i]; a1 = cifra[i + 1];
        cifra[i] = cifra[j];
        cifra[i + 1] = cifra[j + 1];
        cifra[j] = a0;
        cifra[j + 1] = a1;
    }

    return cifra;

}

//inverte cada bloco de 2 caracteres
char *inverter_pares(char *cifra) {
    int q = qtd_char(cifra);

    for (int i = 0; i + 1 < q; i += 2) {
        char tmp = cifra[i];
        cifra[i] = cifra[i + 1];
        cifra[i + 1] = tmp;
    }

    return cifra;
}

//desfaz a cifra de César
char *cesar(char *cifra) {
    int q = qtd_char(cifra);
    char *s2 = malloc((q + 1) * sizeof(char));

    for (int i = 0; i < q; ++i) {
        unsigned char c = cifra[i];
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A';
            x = (x - 5 + 26) % 26;
            s2[i] = (char)('A' + x);
        } else if (c >= 'a' && c <= 'z') {
            int x = c - 'a';
            x = (x - 5 + 26) % 26;
            s2[i] = (char)('a' + x);
        } else {
            s2[i] = cifra[i];
        }
    }
    s2[q] = '\0';
    return s2;
}

//substitui '#' por espaço. Retorna nova string alocada.
char *inserir_espacos(char *cifra) {
    int q = qtd_char(cifra);
    char *s2 = malloc((q + 1) * sizeof(char));

    for (int i = 0; i < q; ++i) {
        if (cifra[i] == '#') s2[i] = ' ';
        else s2[i] = cifra[i];
    }
    s2[q] = '\0';
    return s2;
}

/* resolve usando as etapas inversas conforme o enunciado */
void decodificador(char *cifra) {
    char *tmp = espelhar_blocos(cifra);
    tmp = inverter_pares(tmp);
    char *tmp2 = cesar(tmp);
    char *resultado = inserir_espacos(tmp2);
    printf("%s", resultado);

    free(tmp2);
    free(resultado);
}

int main() {
    char *cifra = malloc(MAX_INPUT * sizeof(char));
    fgets(cifra, MAX_INPUT, stdin);

    printf("Mensagem codificada:\n%s", cifra);

    printf("\nMensagem decodificada:\n");
    decodificador(cifra);

    printf("\n");
    free(cifra);
    return 0;
}