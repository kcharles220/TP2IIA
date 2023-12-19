
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int **leDados(char *nome_fich, int *k, int *v, int *a) {
    FILE *arquivo;
    int **matriz;
    int i, j, v1, v2, custo;

    arquivo = fopen(nome_fich, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_fich);
        exit(1);
    }

    fscanf(arquivo, "k %d\n", k);

    fscanf(arquivo, "p edge %d %d\n", v, a);

    matriz = (int **)malloc((*v) * sizeof(int *));
    for (i = 0; i < *v; i++) {
        matriz[i] = (int *)malloc(*v * sizeof(int));
        for (j = 0; j < *v; j++) {
            matriz[i][j] = 0;  // Inicializa com zero
        }
    }

    while (fscanf(arquivo, "e %d %d %d\n", &v1, &v2, &custo) == 3) {
        v1--;
        v2--;

        matriz[v1][v2] = custo;
        matriz[v2][v1] = custo;
    }

    fclose(arquivo);

    return matriz;
}
void mostraMatriz(int **mat, int m){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
void init_rand(){
    srand((unsigned)time(NULL));
}

void geraSolInicial(int *solucao, int k, int v, int **grafo) {
    do {
        // inicializa a solução como zero
        for (int i = 0; i < v; i++) {
            solucao[i] = 0;
        }

        for (int i = 0; i < k; i++) {
            int vertice;
            do {
                vertice = rand() % v;
            } while (solucao[vertice] == 1);
            solucao[vertice] = 1;
            //printf("\nVertice: %d", vertice);
        }
    }while(!solucaoValida(solucao, v, grafo));
}

void mostraSol(int *solucao, int v){
    printf("\n[");
    for(int i = 0; i < v; i++){
        printf("%d", solucao[i]);
    }
    printf("]\n");
}
int calculaCusto(int *solucao, int **grafo, int v) {
    int custo = 0;

    for (int i = 0; i < v; ++i) {
        if (solucao[i] == 1) {
            for (int j = 0; j < v; ++j) {
                if (grafo[i][j] > 0 && solucao[j] == 1) {
                    custo += grafo[i][j];
                }
            }
        }
    }

    //matriz é simetrica
    custo=custo/2;

    return custo;
}
void substituiSol(int *a, int *b, int v){
    for(int i = 0; i < v; i++)
        a[i] = b[i];
}
bool solucaoValida(int *solucao, int v, int **grafo) {
    // verificar se cada vértice marcado como 1 na solução está conectado a pelo menos um outro vértice marcado
    for (int i = 0; i < v; ++i) {
        if (solucao[i] == 1) {
            int conexaoEncontrada = 0;  // flag para verificar se encontramos pelo menos uma conexão
            for (int j = 0; j < v; ++j) {
                if (solucao[j] == 1 && grafo[i][j] > 0) {
                    conexaoEncontrada = 1;
                    break;
                }
            }

            // Se não encontrou a solução não é válida
            if (!conexaoEncontrada) {
                return false;
            }
        }
    }

    return true;  //  solução é válida
}

bool solucaoValidaK(int *solucao, int v, int **grafo, int k) {
    int numVerticesMarcados = 0;

    for (int i = 0; i < v; ++i) {
        if (solucao[i] == 1) {
            numVerticesMarcados++;

            int conexaoEncontrada = 0;
            for (int j = 0; j < v; ++j) {
                if (solucao[j] == 1 && grafo[i][j] > 0) {
                    conexaoEncontrada = 1;
                    break;
                }
            }

            if (!conexaoEncontrada) {
                return false;
            }
        }
    }

    // verifica se o número de vértices marcados é igual a k
    if (numVerticesMarcados != k) {
        return false;
    }

    return true;  // solução é válida
}
