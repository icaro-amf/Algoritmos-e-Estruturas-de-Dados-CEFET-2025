/****************

LAED1 - Projeto (Parte II) - Busca por padrão da pista.
Adaptação: diferenciar retas (incluindo diagonais) de curvas usando R²

Alunos: ANDRÉ JUNQUEIRA ESPÍNDOLA BOTELHO
        ICARO ALVES MOTA FONSECA

Data:   27/11/2025 (modificado)

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
        // sem necessidade de free aqui (ponteiro é NULL), apenas sair
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

    return (double)contador / (double)(n - 1);
}

/* NOVA FUNÇÃO
   Calcula o coeficiente de determinação R² ajustando uma reta y = m*x + c
   onde x são índices (0,1,...,n-1) e y são os pontos médios.
   Retorna R² no intervalo [0,1]. Se n <= 1 retorna 1.0 (perfeitamente linear por definição).
*/
double calc_r_quadrado(double *y, int n)
{
    if (n <= 1) return 1.0;

    double sumx = 0.0, sumy = 0.0;
    double sumxx = 0.0, sumxy = 0.0;
    for (int i = 0; i < n; i++)
    {
        double x = (double)i;
        sumx += x;
        sumy += y[i];
        sumxx += x * x;
        sumxy += x * y[i];
    }

    double denom = n * sumxx - sumx * sumx;
    double m = 0.0, c = 0.0;
    if (fabs(denom) > 1e-12)
    {
        m = (n * sumxy - sumx * sumy) / denom;
        c = (sumy - m * sumx) / n;
    }
    else
    {
        // caso degenerado (todos x iguais) — assume-se linha horizontal
        m = 0.0;
        c = sumy / n;
    }

    // calcular TSS e RSS
    double mean_y = sumy / n;
    double ss_tot = 0.0;
    double ss_res = 0.0;
    for (int i = 0; i < n; i++)
    {
        double xi = (double)i;
        double yi = y[i];
        double y_pred = m * xi + c;
        double diff_tot = yi - mean_y;
        double diff_res = yi - y_pred;
        ss_tot += diff_tot * diff_tot;
        ss_res += diff_res * diff_res;
    }

    if (ss_tot <= 1e-12) return 1.0; // sem variação em y => perfeito ajuste
    double r2 = 1.0 - (ss_res / ss_tot);
    if (r2 < 0.0) r2 = 0.0;
    if (r2 > 1.0) r2 = 1.0;
    return r2;
}

int main()
{
    int L;

    if (scanf("%d", &L) != 1) return 0;

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
        if (scanf("%d", &N) != 1) return 0;
        
        tamanhos[i] = N;

        imagem[i] = (int*) malloc(N * sizeof(int));
        if (imagem[i] == NULL)
        {
            for (int k = 0 ; k < i ; k++)
            {
                free(imagem[k]);
            }
            free(imagem);
            free(tamanhos);
            exit(0);
        }

        for (int j = 0 ; j < N ; j++)
        {
            scanf("%d", &imagem[i][j]);
        }
    }

    int padrao[] = {1, 3, 2, 3, 1};
    int posicao = sizeof(padrao) / sizeof(padrao[0]);

    double *pontos_medios = (double *) malloc(L * sizeof(double)); // (não usado mas mantido)
    int *linhas_detectadas = (int *) malloc(L * sizeof(int)); // (não usado mas mantido)

    if (pontos_medios == NULL || linhas_detectadas == NULL)
    {
        for (int i = 0 ; i < L ; i++)
        {
            free(imagem[i]);
        }
        free(imagem);
        free(tamanhos);
        free(pontos_medios);
        free(linhas_detectadas);
        exit(0);
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

        int pos = KMP_busca_retorna_pos(padrao, posicao, indices, aux);

        if (pos >= 0)
        {
            int p = 0;
            
            for (int k = 0 ; k < pos ; k++)
            {
                p += runs[k];
            }
            
            int tamSeg = 0;

            for (int k = pos ; k < pos + posicao ; k++)
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
        // libera memoria antes de sair
        for (int i = 0 ; i < L ; i++) free(imagem[i]);
        free(imagem);
        free(tamanhos);
        free(pontos);
        free(pontos_medios);
        free(linhas_detectadas);
        return 0;
    }



    // estimando formato entre Curva a direita, Curva a esquerda ou Pista em linha reta
    double mediaPontos = variacao_delta(pontos, achados);
    double fracao = fracao_deltas(pontos, achados, mediaPontos);

    // NOVO: verificar linearidade dos pontos (R²) para detectar retas diagonais
    double R2_LIMITE = 0.85; // limite ajustável: acima disso considera-se linear (reta)
    double r2 = calc_r_quadrado(pontos, achados);

    double limiteDelta = 0.1;
    double limiteCurvatura = 0.55;

    if (r2 >= R2_LIMITE)
    {
        // se R² alto, classificamos como reta (captura retas diagonais)
        printf("Resultado: Pista em linha reta.\n");
    }
    else
    {
        // se R² baixo, usa heurística anterior (média + fração)
        if (fabs(mediaPontos) < limiteDelta || fracao < limiteCurvatura)
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
    }

    fprintf(stderr, "DEBUG: pontos medios (ordem detectada, achados=%d):", achados);
    for (int i = 0; i < achados; i++) fprintf(stderr, " %.0f", pontos[i]);
    fprintf(stderr, "\n");
    fprintf(stderr, "DEBUG: R2=%.4f, mediaPontos=%.4f, fracao=%.4f\n", r2, mediaPontos, fracao);
    

    // libera os vetores para finalizar o programa
    for (int i = 0 ; i < L ; i++)
    {
        free(imagem[i]);
    }

    free(imagem);
    free(tamanhos);
    free(pontos);
    free(pontos_medios);
    free(linhas_detectadas);

    return 0;
}
