/*
    Alunos:
    André Botelho
    Ícaro Fonseca
    Matheus Saad
    
    Atividade:
    Exercício Ordenação por seleção parcial - para 25/11/2025
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAXTAM          20
typedef int TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;
typedef int  TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1];
TipoVetor A, B;
TipoIndice i, n, k;

void SelecaoParcial(TipoVetor A, TipoIndice n, TipoIndice k)
{ TipoIndice i, j, Min;  TipoItem x;
  for (i = 1; i <= k; i++) 
    { Min = i;
      for (j = i + 1; j <= n; j++) 
        if (A[j].Chave < A[Min].Chave) Min = j;
      x = A[Min]; A[Min] = A[i]; A[i] = x;
    } 
}

void Imprime(TipoVetor V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%d ", V[i].Chave);
  putchar('\n');
}

void Copia(TipoVetor Fonte, TipoVetor Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

void Testa(TipoVetor V, TipoIndice n, TipoIndice k)
{ for (i = 2; i <= k; i++) 
    { if (V[i].Chave < V[i-1].Chave) 
      { printf("ERRO: ");
        Imprime(V, n);
        exit(1);
      }
    }
  printf("OK  : ");
  Imprime(V, n);
}

int main()
{ int TEMP;
  
printf("Digite o tamanho do vetor (max 20): ");
scanf("%d", &n);

printf("Digite os %d valores do vetor:\n", n);
for (i = 1; i <= n; i++) {
    scanf("%d", &A[i].Chave);
    B[i].Chave = A[i].Chave;
  }

  printf("Desordenado   : ");
  Imprime(A, n);

  printf("SelecaoParcial com k = ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  SelecaoParcial(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  return 0;
}