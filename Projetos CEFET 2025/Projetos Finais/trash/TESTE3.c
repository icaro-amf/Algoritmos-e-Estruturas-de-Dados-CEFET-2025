/* Projeto - Parte II - LAED I
 * Leitura: primeira linha = L (numero de linhas)
 * Para cada uma das L linhas:
 *   - linha com N (numero de elementos)
 *   - linha com N inteiros (valores dos pixels)
 *
 * Detecta o segmento principal (maior segmento de valores != 0) em cada linha,
 * calcula o ponto medio (arredondado) e, se pelo menos 70% das linhas tiverem
 * segmento, estima o formato da pista:
 *   Resultado: Curva a direita.
 *   Resultado: Curva a esquerda.
 *   Resultado: Pista em linha reta.
 *   Resultado: Formato da pista nao estimado.
 *
 * Compilar: gcc -std=c11 -O2 -Wall -Wextra -o parte2 parte2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int L;
    if (scanf("%d", &L) != 1) return 0;
    if (L <= 0) {
        printf("Resultado: Formato da pista nao estimado.\n");
        return 0;
    }

    // vetor para armazenar os pontos-medio detectados (um por linha válida)
    int *midpoints = (int*) malloc(sizeof(int) * L);
    if (!midpoints) return 0;
    int found = 0;

    for (int li = 0; li < L; ++li) {
        int N;
        if (scanf("%d", &N) != 1) { free(midpoints); return 0; }
        if (N <= 0) {
            // consumir linha (se houver) e pular
            for (int i=0;i<N;i++) { int tmp; if(scanf("%d",&tmp)!=1){ } }
            continue;
        }

        int *vals = (int*) malloc(sizeof(int) * N);
        if (!vals) { free(midpoints); return 0; }
        for (int i = 0; i < N; ++i) {
            if (scanf("%d", &vals[i]) != 1) vals[i] = 0;
        }

        // encontra todos os segmentos contíguos de valores != 0
        int best_p = -1, best_q = -1, best_len = 0;
        int p = -1;
        for (int i = 0; i < N; ++i) {
            if (vals[i] != 0) {
                if (p == -1) p = i;
            } else {
                if (p != -1) {
                    int q = i - 1;
                    int len = q - p + 1;
                    if (len > best_len) { best_len = len; best_p = p; best_q = q; }
                    p = -1;
                }
            }
        }
        if (p != -1) { // finaliza último segmento
            int q = N - 1;
            int len = q - p + 1;
            if (len > best_len) { best_len = len; best_p = p; best_q = q; }
        }

        if (best_len > 0) {
            // calcula ponto medio com arredondamento ao inteiro mais próximo
            double midf = (best_p + best_q) / 2.0;
            int mid = (int) floor(midf + 0.5);
            midpoints[found++] = mid;
        }

        free(vals);
    }

    // verifica percentagem minima: 70%
    int required = (int) ceil(0.7 * L - 1e-9);
    if (found < required) {
        printf("Resultado: Formato da pista nao estimado.\n");
        free(midpoints);
        return 0;
    }

    // calcula regressao linear y = a + b*x, onde x = 0..found-1 (ordem das linhas detectadas)
    // x: indices 0..found-1
    double sx = 0.0, sy = 0.0, sxx = 0.0, sxy = 0.0;
    for (int i = 0; i < found; ++i) {
        double x = (double)i;
        double y = (double) midpoints[i];
        sx += x;
        sy += y;
        sxx += x * x;
        sxy += x * y;
    }
    double n = (double) found;
    double denom = n * sxx - sx * sx;
    double slope = 0.0;
    if (fabs(denom) > 1e-12) {
        slope = (n * sxy - sx * sy) / denom;
    } else {
        slope = 0.0; // todos os x iguais? (improvavel) => trata como reta
    }

    // EPS define a sensibilidade (em pixels por indice de linha)
    const double EPS = 0.3;

    if (slope > EPS) {
        // slope positivo: pontos-medio aumentam com x (ou seja, deslocamento para a direita ao avançar nas linhas)
        printf("Resultado: Curva a direita.\n");
    } else if (slope < -EPS) {
        printf("Resultado: Curva a esquerda.\n");
    } else {
        printf("Resultado: Pista em linha reta.\n");
    }

    free(midpoints);
    return 0;
}
