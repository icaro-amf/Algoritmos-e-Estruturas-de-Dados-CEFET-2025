/****************

LAED1 - Projeto (Parte II) - Busca por padrão da pista.

Alunos: ANDRÉ JUNQUEIRA ESPÍNDOLA BOTELHO
        ICARO ALVES MOTA FONSECA

Data:   27/11/2025

****************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1000

//alteracao das funcoes KMP e prefixoSufixo anteriores por uma unica funcao completa.
int KMP_busca_retorna_pos(int *substring, int tamanhoPadrao, int *txt, int tamanhoTexto)
{
    //vetor para identificar sufixo ou prefixo
    int *prefixoSufixo = (int *)malloc(sizeof(int) * tamanhoPadrao);

    if (prefixoSufixo == NULL)
    {
        free(prefixoSufixo);
        exit(0);
    }

    // calcula prefixo/sufixo
    prefixoSufixo[0] = 0;
    int len = 0;
    int i = 1;

    while (i < tamanhoPadrao) //ATT: falta verificar possiveis erros
    {
        if (substring[i] == substring[len])
        {
            len++;
            prefixoSufixo[i] = len;
            i++;
        } 
        else
        {
            if (len != 0)
            {
                len = prefixoSufixo[len - 1];
            } 
            else
            {
                prefixoSufixo[i] = 0;
                i++;
            }
        }
    }

    //mudar antes de enviar
    int a = 0; 
    int b = 0;

    while (a < tamanhoTexto)
    {
        if (substring[b] == txt[a])
        {
            a++;
            b++;
        }

        if (b == tamanhoPadrao)
        {
            int pos = a - b;
            free(prefixoSufixo);
            return pos;
        } 
        
        else if (a < tamanhoTexto && substring[b] != txt[a]) //verifica similaridade
        {
            if (b != 0)
            {
                b = prefixoSufixo[b - 1];
            }

            else
            {
                a++;
            }
        }
    }

    free(prefixoSufixo);
    return -1;
}

// função para calcula diferença entre dois pontos médios consecutivos
double variacao_delta(double *y, int n)
{
    if (n <= 1)
    {
        return 0;
    }

    double somador = 0;

    for (int i = 0 ; i < n - 1 ; i++) //calcula efetivamentesm a media da linha em questao
    {
        somador += (y[i+1] - y[i]); 
    }
    
    return (somador / (n - 1));
}

// função para calcular
double fracao_deltas(double *y, int n, double ref)
{
    if (n <= 1)
    {
        return 0;
    }

    int contador = 0;
    
    for (int i = 0 ; i < n - 1 ; i++)
    {
        double d = y[i+1] - y[i];
        if ((ref > 0 && d > 0) || (ref < 0 && d < 0) || (ref == 0 && fabs(d) < EPS))
        {
            contador++;
        }
    }

    return contador / (n - 1);
}




int main()
{
    int L;

    scanf("%d", &L);

    int **imagem = (int **) malloc(L * sizeof(int*));
    int *tamanhos = (int *) malloc(L * sizeof(int));

    if (imagem == NULL || tamanhos == NULL)
    {
        free(imagem);
        free(tamanhos);
        exit(0);
    }

    for (int i = 0 ; i < L ; i++)
    {
        int N;

        scanf("%d", &N);
        
        tamanhos[i] = N;

        imagem[i] = (int*) malloc(N * sizeof(int));
        if (imagem[i] == NULL)
        {
            for (int k = 0 ; k < i ; k++)
            {
                free(imagem[k]);
                free(imagem);
                free(tamanhos);
                exit(0);
            }
        }

        for (int j = 0 ; j < N ; j++)
        {
            scanf("%d", &imagem[i][j]);
        }
    }

    int padrao[] = {1, 3, 2, 3, 1};
    int tamanho_padrao = sizeof(padrao) / sizeof(padrao[0]);

    double *pontos_medios = (double *) malloc(L * sizeof(double));
    int *linhas_detectadas = (int *) malloc(L * sizeof(int));

    if (pontos_medios == NULL || linhas_detectadas == NULL)
    {
        for (int i = 0 ; i < L ; i++)
        {
            free(imagem[i]);
            free(imagem);
            free(tamanhos);
            free(pontos_medios);
            free(linhas_detectadas);
            exit(0);
        }
    }

    double *pontos = (double *) malloc(L * sizeof(double));
    int achados = 0;

    // processa cada linha
    for (int linha = 0 ; linha < L ; linha++)
    {
        int N = tamanhos[linha];
        int *vet = imagem[linha];

        int *indices = (int *) malloc(N * sizeof(int));
        int *runs = (int *) malloc(N * sizeof(int));

        int aux = 0;

        for (int i = 0 ; i < N ; )
        {
            int valor = vet[i];
            int cont = 1;

            while (i + cont < N && vet[i + cont] == valor)
            {
                cont++;
            }

            int indice = 0;
            if (valor == 0)
            {
                indice = 1;
            }
            else if (valor == 128)
            {
                indice = 2;
            }
            else if (valor == 255)
            {
                indice = 3;
            }

            indices[aux] = indice;
            runs[aux] = cont;

            aux++;
            i += cont;
        }

        int pos = KMP_busca_retorna_pos(padrao, tamanho_padrao, indices, aux);

        if (pos >= 0)
        {
            int p = 0;
            
            for (int k = 0 ; k < pos ; k++)
            {
                p += runs[k];
            }
            
            int tamSeg = 0;

            for (int k = pos ; k < pos + tamanho_padrao ; k++)
            {
                tamSeg += runs[k];
            }
            
            int q = p + tamSeg - 1;

            int soma = p + q;
            int pt_medio;

            if (soma % 2 == 0) {
                pt_medio = soma / 2;
            } else {
                pt_medio = (soma + 1) / 2;
            }

            pontos[achados] = pt_medio;
            achados++;
        }

        free(indices);
        free(runs);
    }



    // teste dos 70%
    int minimo = (int)(0.7 * L + 0.9999);

    if (achados < minimo)
    {
        printf("Resultado: Formato da pista nao estimado\n");
        return 0;
    }



    // estimando formato entre Curva a direita, Curva a esquerda ou Pista em linha reta
    double mediaPontos = variacao_delta(pontos, achados);

    double limiteDelta = 0.2;
    double limiteCurvatura = 0.55;

    if (fabs(mediaPontos) < limiteDelta)
    {
        printf("Resultado: Pista em linha reta.\n");
    }
    else
    {
        if (mediaPontos > 0)
        {
        printf("Resultado: Curva a esquerda.\n");
        }
        else
        {
        printf("Resultado: Curva a direita.\n");
        }
    }
    

    // libera os vetores para finalizar o programa
    for (int i = 0 ; i < L ; i++)
    {
        free(imagem[i]);
    }

    free(imagem);
    free(tamanhos);
    free(pontos);

    return 0;
}