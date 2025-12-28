/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos: ANDRÉ JUNQUEIRA ESPÍNDOLA BOTELHO
        ICARO ALVES MOTA FONSECA

Data:   06/11/2024

****************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_MAPEAR 1000

// Função para preencher um vetor para o maior prefixo que é sufixo
void lps(int *substring, int tamanhoPadrao, int *prefixoSufixo)
{
    int tamanho = 0;
    prefixoSufixo[0] = 0;
    int i = 1;

    while (i < tamanhoPadrao)
    {
        if (substring[i] == substring[tamanho])
        {
            tamanho++;
            prefixoSufixo[i] = tamanho;
            i++;
        }
        else
        {
            if (tamanho != 0)
            {
                tamanho = prefixoSufixo[tamanho - 1];
            }
            else
            {
                prefixoSufixo[i] = 0;
                i++;
            }
        }
    }
}

// Função principal de busca KMP
void KMP(int *substring, int tamanhoPadrao, int *txt, int tamanhoTexto)
{
    // Cria array de maior prefixo que é sufixo
    int *prefixoSufixo = (int *)malloc(sizeof(int) * tamanhoPadrao);
    // Chama função para fazer a verificaro entre prefixo/sufixo
    lps(substring, tamanhoPadrao, prefixoSufixo);

    int i = 0;
    int j = 0;
    int verificador = 0;

    while (i < tamanhoTexto)
    {
        if (substring[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == tamanhoPadrao)
        {
            printf("Resultado: Padrao encontrado.");
            verificador = 1;
            j = prefixoSufixo[j - 1];
            break;
        }
        else if (i < tamanhoTexto && substring[j] != txt[i])
        {
            if (j != 0)
                j = prefixoSufixo[j - 1];
            else
                i++;
        }
    }

    if (verificador == 0)
    {
        printf("Resultado: Padrao nao encontrado nessa linha.");
    }

    free(prefixoSufixo);

}

int main()
{
    int L;         // quantidade de linhas(L) de pixeis a serem analisadas

    scanf("%d", &L);

    int **imagem = (int **) malloc(L * sizeof(int*));
    int *tamanhos = (int *) malloc(L * sizeof(int)); // guarda N de cada linha

    if (imagem == NULL || tamanhos == NULL)
    { // se ocorrer algum erro na alocacao dos vetores, apos liberar os vetores, encerra imediatamente o programa
        free(imagem);
        free(tamanhos);
        exit(0);
    }

    for (int i = 0; i < L; i++) {
        int N;
        scanf("%d", &N);

        tamanhos[i] = N; // salva o tamanho da linha

        imagem[i] = (int*) malloc(N * sizeof(int));
        if (imagem[i] == NULL) {
            for (int k = 0; k < i; k++){
                free(imagem[k]);
                free(imagem);
                free(tamanhos);
                exit(0);
            }
        }
        
        for (int j = 0; j < N; j++) {
            scanf("%d", &imagem[i][j]);
        }
    }

    int padrao[] = {1, 3, 2, 3, 1};
    int M = sizeof(padrao) / sizeof(padrao[0]);

   for (int linha = 0; linha < L; linha++) {
        int num = tamanhos[linha];
        int *num_user = imagem[linha];

        // Vetor indices com tamanho máximo num (cada repetição consecutiva vira um índice)
        int *indices = (int *) malloc(num * sizeof(int));
        if (indices == NULL) {
            for (int k = 0; k < L; k++){
                free(imagem[k]);
                free(imagem);
                free(tamanhos);
                exit(0);
            }
        }

        int aux = 0;

        // Fazer o agrupamento e armazenar os índices (mesma lógica original)
        for (int i = 0; i < num; )
        {
            int valor = num_user[i];
            int cont = 1;

            // Conta quantas vezes o mesmo valor se repete em sequência
            while (i + cont < num && num_user[i + cont] == valor)
            {
                cont++;
            }

            // Define o índice fixo conforme o valor
            int indice = 0;
            if (valor == 0)
                indice = 1;
            else if (valor == 128)
                indice = 2;
            else if (valor == 255)
                indice = 3;

            // Armazena o índice
            indices[aux] = indice;

            aux++;
            i += cont;
        }

        // Executa KMP no vetor indices (tamanho = aux)
        KMP(padrao, M, indices, aux);
        printf("\n");

        free(indices);
    }

    // libera tudo
    for (int i = 0; i < L; i++){
        free(imagem[i]);
        free(imagem);
        free(tamanhos);
    }

    return 0;
}