#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algoritmo.h"

#define TAXA_MUTACAO 0.001

int main() {
    char nome_fich[1000];
    int **matriz;
    int *sol_inic, *sol_best, custo, n;

    int rondas = 20;
    int totalBestCost = 0;

    int best_custo = 0, num_iter;
    int k = 0, v = 0, a = 0, op;

    printf("Nome do ficheiro: ");
    fgets(nome_fich, 1000, stdin);
    strtok(nome_fich, "\n");
    char resposta[10];
    int aceitar_custo_igual;

    printf("Pretende aceitar solucoes de custo igual? (s/n): ");
    scanf("%s", resposta);


    if (strcmp(resposta, "s") == 0 || strcmp(resposta, "sim") == 0) {
        aceitar_custo_igual = 1;
        printf("Solucoes de custo igual serao aceitas.\n");
    }

    else if (strcmp(resposta, "n") == 0 || strcmp(resposta, "nao") == 0) {
        aceitar_custo_igual = 0;
        printf("Solucoes de custo igual nao serao aceitas.\n");
    }

    // lê e cria matriz
    matriz = leDados(nome_fich, &k, &v, &a);
    sol_inic = malloc(sizeof(int) * v);
    sol_best = malloc(sizeof(int) * v);

    if (sol_inic == NULL || sol_best == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    init_rand();


    printf("1- Trepa Colinas\n");
    printf("2- Algoritmo Evolutivo\n");
    printf("3- Algoritmo Hibrido 1\n");
    printf("4- Algoritmo Hibrido 2\n");

    printf("Escolha: ");
    scanf("%d", &op);

    if (op == 1) {
        // Trepa Colinas
        int vi;
        printf("--> Trepa Colinas <--\n");
        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);
        printf("Tipo de vizinhanca:\n");
        printf("1-Troca vertices:\n");
        printf("2-Minimizacao de arestas\n");
        scanf("%s", &vi);


        for (int i = 0; i < rondas; i++) {
            printf("\n\nRONDA %d\n", i);

            // gera e mostra solucao inicial
            printf("\nSolucao Inicial:");
            geraSolInicial(sol_inic, k, v, matriz);
            mostraSol(sol_inic, v);
            custo = calculaCusto(sol_inic, matriz, v);
            printf("Custo Inicial: %d", custo);

            printf("\nTrepaColinas:\n");
            custo = trepacolinas(sol_inic, matriz, v, num_iter, aceitar_custo_igual,vi);
            mostraSol(sol_inic, v);
            printf("Custo PosTrepa: %d\n", custo);

            if (i == 0 || best_custo > custo) {
                best_custo = custo;
                substituiSol(sol_best, sol_inic, v);
            }

            // atualiza melhor custo
            totalBestCost += custo;
        }

        printf("\nResultado:\nMelhor solucao:");
        mostraSol(sol_best, v);
        printf("Custo final: %2d\n", best_custo);

        // media
        float averageBestCost = (float)totalBestCost / rondas;

        printf("\nMedia dos melhores custos: %.2f\n", averageBestCost);


        free(sol_best);
        free(sol_inic);

    } else if (op == 2) {
        // Algoritmo Evolutivo
        printf("--> Algoritmo Evolutivo <--\n");
        int popSize = 200;  // Tamanho da população
        int numGenerations = 1000;  // Número de gerações
        int melhorCustoGlobal=0;
        int *melhorSolucaoGlobal = malloc(sizeof(int) * v);
        int total=0;
        int  tipoSelecao, tipoCrossover, tipoMutacao, tipoEstrategiaInvalida;



        printf("\nTipo de estrategia de selecao:\n");
        printf("1 - Selecao por torneio\n");
        printf("2 - Selecao proporcional a aptidao (Roleta)\n");
        scanf("%d", &tipoSelecao);

        printf("\nTipo de estrategia de crossover:\n");
        printf("1 - Crossover de um ponto\n");
        printf("2 - Crossover de dois pontos\n");
        scanf("%d", &tipoCrossover);

        printf("\nTipo de estrategia de mutacao:\n");
        printf("1 - Mutacao de bit\n");
        printf("2 - Inversao de sequencia\n");
        scanf("%d", &tipoMutacao);

        printf("\nTipo de estrategia de tratamento de solucoes invalidas:\n");
        printf("1 - Penalização\n");
        printf("2 - Reparacao com geracao de solucao inicial\n");
        scanf("%d", &tipoEstrategiaInvalida);

        // populacao de soluc iniciais aleatorias
        chrom *populacao = malloc(sizeof(chrom) * popSize);
        for (int i = 0; i < popSize; i++) {
            populacao[i].solucao = malloc(sizeof(int) * v);
            geraSolInicial(populacao[i].solucao, k, v, matriz);
            populacao[i].custo = calculaCusto(populacao[i].solucao, matriz, v);
        }

        for (int gen = 0; gen < numGenerations; gen++) {
            // metodo evolutivo
            evoluirPopulacao(populacao, popSize, TAXA_MUTACAO, v, matriz, k,tipoSelecao,tipoCrossover,tipoMutacao,tipoEstrategiaInvalida);

            // avalicao
            for (int i = 0; i < popSize; i++) {
                populacao[i].custo = calculaCusto(populacao[i].solucao, matriz, v);
            }

            chrom melhorSolucao = encontraMelhorSolucao(populacao, popSize);

            // melhor solucao
            printf("\nResultado:\nMelhor solucao:");
            mostraSol(melhorSolucao.solucao, v);
            printf("Custo final: %2d\n", melhorSolucao.custo);
            if (melhorSolucao.custo < melhorCustoGlobal ||gen == 0) {
                melhorCustoGlobal = melhorSolucao.custo;
                melhorSolucaoGlobal = melhorSolucao.solucao;
            }
            total += melhorSolucao.custo;
        }

        printf("\n\nFinal:\nMelhor solucao:");
        mostraSol(melhorSolucaoGlobal, v);
        printf("Custo final: %2d\n", melhorCustoGlobal);

        free(melhorSolucaoGlobal);




        free(populacao);

    }else if (op == 3) {
        int popSize = 200;  // Tamanho da população
        int numGenerations = 1000;  // Número de gerações
        int vi;
        printf("--> Algoritmo Hibrido 1 <--\n");
        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);
        int tipoVizinhanca, tipoSelecao, tipoCrossover, tipoMutacao, tipoEstrategiaInvalida;


        printf("Tipo de vizinhanca:\n");
        printf("1 - Troca de vertices\n");
        printf("2 - Minimizaçao de arestas\n");
        scanf("%d", &tipoVizinhanca);


        printf("\nTipo de estrategia de selecao:\n");
        printf("1 - Selecao por torneio\n");
        printf("2 - Selecao proporcional a aptidao (Roleta)\n");
        scanf("%d", &tipoSelecao);

        printf("\nTipo de estrategia de crossover:\n");
        printf("1 - Crossover de um ponto\n");
        printf("2 - Crossover de dois pontos\n");
        scanf("%d", &tipoCrossover);

        printf("\nTipo de estrategia de mutacao:\n");
        printf("1 - Mutacao de bit\n");
        printf("2 - Inversao de sequencia\n");
        scanf("%d", &tipoMutacao);

        printf("\nTipo de estrategia de tratamento de solucoes invalidas:\n");
        printf("1 - Penalização\n");
        printf("2 - Reparacao com geracao de solucao inicial\n");
        scanf("%d", &tipoEstrategiaInvalida);
        int melhorCustoGlobal = 0;
        int *melhorSolucaoGlobal;
        int total = 0;

        for (int i = 0; i < num_iter; i++) {
            printf("\n\nITERACAO %d\n", i + 1);

            // Trepa Colinas
            printf("\n--> Trepa Colinas <--\n");
            geraSolInicial(sol_inic, k, v, matriz);
            custo = trepacolinas(sol_inic, matriz, v, 1,aceitar_custo_igual,tipoVizinhanca);
            mostraSol(sol_inic, v);
            printf("Custo TrepaColinas: %d\n", custo);

            if (melhorCustoGlobal > custo || i == 0) {
                melhorCustoGlobal = custo;
                substituiSol(melhorSolucaoGlobal, sol_inic, v);
            }

            totalBestCost += custo;

            // Algoritmo Evolutivo
            printf("\n--> Algoritmo Evolutivo <--\n");

            // solucoes iniciais aleatorias
            chrom *populacao = malloc(sizeof(chrom) * popSize);
            for (int j = 0; j < popSize; j++) {
                populacao[j].solucao = malloc(sizeof(int) * v);
                geraSolInicial(populacao[j].solucao, k, v, matriz);
                populacao[j].custo = calculaCusto(populacao[j].solucao, matriz, v);
            }

            for (int gen = 0; gen < numGenerations; gen++) {
                // Método evolutivo
                evoluirPopulacao(populacao, popSize, TAXA_MUTACAO, v, matriz, k,tipoSelecao,tipoCrossover,tipoMutacao,tipoEstrategiaInvalida);

                // avaliação
                for (int j = 0; j < popSize; j++) {
                    populacao[j].custo = calculaCusto(populacao[j].solucao, matriz, v);
                }

                chrom melhorSolucao = encontraMelhorSolucao(populacao, popSize);

                // melhor solução
                printf("\nResultado:\nMelhor solucao:");
                mostraSol(melhorSolucao.solucao, v);
                printf("Custo final: %2d\n", melhorSolucao.custo);

                if (melhorSolucao.custo < melhorCustoGlobal || gen == 0) {
                    melhorCustoGlobal = melhorSolucao.custo;
                    melhorSolucaoGlobal = melhorSolucao.solucao;
                }
                total += melhorSolucao.custo;
            }

            printf("\nMelhor solucao global após o Algoritmo Evolutivo:");
            mostraSol(melhorSolucaoGlobal, v);
            printf("Custo final: %2d\n", melhorCustoGlobal);

            free(populacao);
        }

        float averageBestCost = (float)totalBestCost / num_iter;
        printf("\nMedia dos melhores custos: %.2f\n", averageBestCost);

        free(sol_best);
        free(sol_inic);

    }
    else if (op == 4) {
            int popSize = 200;  // Tamanho da população
            int numGenerations = 1000;  // Número de gerações


        int vi;
        printf("--> Algoritmo Hibrido 2 <--\n");
        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);
        int tipoVizinhanca, tipoSelecao, tipoCrossover, tipoMutacao, tipoEstrategiaInvalida;

        printf("Tipo de vizinhanca:\n");
        printf("1 - Troca de vertices\n");
        printf("2 - Minimizacao de arestas\n");
        scanf("%d", &tipoVizinhanca);

        printf("\nTipo de estrategia de selecao:\n");
        printf("1 - Selecao por torneio\n");
        printf("2 - Selecao proporcional a aptidao (Roleta)\n");
        scanf("%d", &tipoSelecao);

        printf("\nTipo de estrategia de crossover:\n");
        printf("1 - Crossover de um ponto\n");
        printf("2 - Crossover de dois pontos\n");
        scanf("%d", &tipoCrossover);

        printf("\nTipo de estrategia de mutacao:\n");
        printf("1 - Mutacao de bit\n");
        printf("2 - Inversao de sequencia\n");
        scanf("%d", &tipoMutacao);

        printf("\nTipo de estrategia de tratamento de solucoes invalidas:\n");
        printf("1 - Penalização\n");
        printf("2 - Reparacao com geracao de solucao inicial\n");
        scanf("%d", &tipoEstrategiaInvalida);

            int melhorCustoGlobal = 0;
            int *melhorSolucaoGlobal;
            int total = 0;

            for (int i = 0; i < num_iter; i++) {
                printf("\n\nITERACAO %d\n", i + 1);

                // Algoritmo Evolutivo
                printf("\n--> Algoritmo Evolutivo <--\n");

                printf("\n--> Algoritmo Evolutivo <--\n");

                // popolcacao sulocoes aleatorias
                chrom *populacao = malloc(sizeof(chrom) * popSize);
                for (int j = 0; j < popSize; j++) {
                    populacao[j].solucao = malloc(sizeof(int) * v);
                    geraSolInicial(populacao[j].solucao, k, v, matriz);
                    populacao[j].custo = calculaCusto(populacao[j].solucao, matriz, v);
                }

                for (int gen = 0; gen < numGenerations; gen++) {
                    // método evolutivo
                    evoluirPopulacao(populacao, popSize, TAXA_MUTACAO, v, matriz, k,tipoSelecao,tipoCrossover,tipoMutacao,tipoEstrategiaInvalida);

                    // avaliação
                    for (int j = 0; j < popSize; j++) {
                        populacao[j].custo = calculaCusto(populacao[j].solucao, matriz, v);
                    }

                    chrom melhorSolucao = encontraMelhorSolucao(populacao, popSize);

                    // melhor solução
                    printf("\nResultado:\nMelhor solucao:");
                    mostraSol(melhorSolucao.solucao, v);
                    printf("Custo final: %2d\n", melhorSolucao.custo);

                    if (melhorSolucao.custo < melhorCustoGlobal || gen == 0) {
                        melhorCustoGlobal = melhorSolucao.custo;
                        melhorSolucaoGlobal = melhorSolucao.solucao;
                    }
                    total += melhorSolucao.custo;
                }

                printf("\nMelhor solucao global após o Algoritmo Evolutivo:");
                mostraSol(melhorSolucaoGlobal, v);
                printf("Custo final: %2d\n", melhorCustoGlobal);

                free(populacao);

                // Trepa Colinas
                printf("\n--> Trepa Colinas <--\n");
                geraSolInicial(sol_inic, k, v, matriz);
                custo = trepacolinas(sol_inic, matriz, v, 1, aceitar_custo_igual,tipoVizinhanca);
                mostraSol(sol_inic, v);
                printf("Custo TrepaColinas: %d\n", custo);

                if (custo < melhorCustoGlobal || i == 0) {
                    melhorCustoGlobal = custo;
                    melhorSolucaoGlobal = sol_inic;
                }

                printf("\nMelhor solucao global após o Trepa Colinas:");
                mostraSol(melhorSolucaoGlobal, v);
                printf("Custo final: %2d\n", melhorCustoGlobal);


                totalBestCost += custo;
            }

            float averageBestCost = (float)totalBestCost / num_iter;
            printf("\nMedia dos melhores custos: %.2f\n", averageBestCost);

            free(sol_best);
            free(sol_inic);


    }else{
        printf("--> Opcao invalida <--\n");

    }

    for (int i = 0; i < v; i++) {
        free(matriz[i]);
    }

    free(matriz);

    return 0;
}
