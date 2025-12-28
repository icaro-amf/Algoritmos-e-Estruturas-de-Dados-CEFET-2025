/****************

LAED1 - Projeto (Parte III) - Busca por impedimentos

Autores: ANDRÉ JUNQUEIRA ESPÍNDOLA BOTELHO
         ICARO ALVES MOTA FONSECA

Data:   11/12/2025
Versão: código corrigido e refatorado

****************/
#include <stdio.h>
#include <stdlib.h>


// Função de pre-processamento do algoritmo kmp, "lps", que ordena e atribui indices aos caracteres/valores na posicao
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


// KMP: retorna 1 se houver impedimento, 0 caso não houver impedimento
int KMP(int *substring, int tamanhoPadrao, int *txt, int tamanhoTexto)
{
    if (tamanhoPadrao == 0)
    {
        return 0;
    }

    int *prefixoSufixo = (int *) malloc(sizeof(int) * tamanhoPadrao);

    if (prefixoSufixo == NULL)
    {
        exit(0);
    }

    lps(substring, tamanhoPadrao, prefixoSufixo);

    int i = 0;
    int j = 0;

    while (i < tamanhoTexto)
    {
        if (substring[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == tamanhoPadrao)
        {
            free(prefixoSufixo);
            return 1;
        }
        else if (i < tamanhoTexto && substring[j] != txt[i])
        {
            if (j != 0)
            {
                j = prefixoSufixo[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    free(prefixoSufixo);
    return 0;
}

int *linhas_indices(int *linha, int N, int *vetor)
{
    if (N <= 0)
    {
        *vetor = 0;
        return NULL;
    }

    // Aloca no máximo N, depois ajustamos se necessário
    int *indices = (int *) malloc(sizeof(int) * N);
    if (indices == NULL)
    {
        *vetor = 0;
        return NULL;
    }

    int aux = 0;
    for (int i = 0; i < N; )
    {
        int valor = linha[i];
        int cont = 1;

        while (i + cont < N && linha[i + cont] == valor)
        {
            cont++;
        }

        // Definindo cores em chaves 0, 1, 2 e 3
        int indice;
        if (valor == 0)
            indice = 1; // Preto
        else if (valor == 128)
            indice = 2; // Vermelho
        else if (valor == 255)
            indice = 3; // Branco
        else
            indice = 0; // Valor inesperado

        indices[aux] = indice;
        aux++;
        i += cont;
    }

    *vetor = aux;
    return indices;
}

int main()
{
    int L;
    if (scanf("%d", &L) != 1)
    {
        return 0;
    }

    int **imagem = (int **) malloc(L * sizeof(int *));
    int *tamanhos = (int *) malloc(L * sizeof(int));

    if (imagem == NULL || tamanhos == NULL)
    {
        free(imagem);
        free(tamanhos);
        return 0;
    }

    // Leitura das linhas
    for (int i = 0; i < L; i++)
    {
        int N;
        scanf("%d", &N);

        tamanhos[i] = N;
        imagem[i] = (int *) malloc(sizeof(int) * N);
        
        // Registrando na matriz
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &imagem[i][j]);
        }
    }


    // Possiveis padroes
    int padrao1[] = {2, 0, 2}; // inesperado entre vermelhos
    int M1 = sizeof(padrao1) / sizeof(padrao1[0]);

    int padrao2[] = {2, 1, 2}; // branco entre vermelhos
    int M2 = sizeof(padrao2) / sizeof(padrao2[0]);

    int padrao3[] = {2, 3, 2}; // preto entre vermelhos
    int M3 = sizeof(padrao3) / sizeof(padrao3[0]);

    int encontrado = 0;

    
    // Para cada linha comprime e testa os 3 padrões
    for (int linha = 0; linha < L && !encontrado; linha++)
    {
        int N = tamanhos[linha];
        int *conteudo = imagem[linha];

        int auxSize = 0;
        int *indices = linhas_indices(conteudo, N, &auxSize);
        if (indices == NULL)
        {
            return 1;
        }

        if (KMP(padrao1, M1, indices, auxSize) == 1)
        {
            encontrado = 1;
        }
        else if (KMP(padrao2, M2, indices, auxSize) == 1)
        {
            encontrado = 1;
        }
        else if (KMP(padrao3, M3, indices, auxSize) == 1)
        {
            encontrado = 1;
        }

        free(indices);
    }

    // Verificando se tem Impedimento e Imprimindo
    if (encontrado)
    {
        printf("Resultado: Pista com impedimento.\n");
    }
    else
    {
        printf("Resultado: Pista sem impedimento.\n");
    }

    for (int i = 0; i < L; i++)
    {
        free(imagem[i]);
    }

    free(imagem);
    free(tamanhos);

    return 0;
}
