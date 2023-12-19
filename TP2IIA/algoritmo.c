#include <stdlib.h>
#include "algoritmo.h"
#include <limits.h>
#include <stdio.h>

int trepacolinas(int *solucao, int **grafo, int v, int nr_iter, int aceitar_custo_igual, int tipo_vizinhanca) {
    int custoAtual = calculaCusto(solucao, grafo, v);
    int custoVizinho;
    int melhorVizinhoEncontrado = 1;
    int iter = 0;

    while (iter < nr_iter) {
        melhorVizinhoEncontrado = 0;

        switch (tipo_vizinhanca) {
            case 1:  // Troca de vértices
            {
                int *solucaoVizinhaTroca = malloc(sizeof(int) * v);
                substituiSol(solucaoVizinhaTroca, solucao, v);
                trocaVertices(solucaoVizinhaTroca, v);
                custoVizinho = calculaCusto(solucaoVizinhaTroca, grafo, v);

                if ((custoVizinho <= custoAtual || aceitar_custo_igual) && solucaoValida(solucaoVizinhaTroca, v, grafo)) {
                    custoAtual = custoVizinho;
                    substituiSol(solucao, solucaoVizinhaTroca, v);
                    melhorVizinhoEncontrado = 1;
                    // printf("\nA solução foi melhorada por troca de vértices");
                }

                free(solucaoVizinhaTroca);
            }
                break;

            case 2:  // Minimização de arestas
            {
                int *solucaoVizinhaAresta = malloc(sizeof(int) * v);
                substituiSol(solucaoVizinhaAresta, solucao, v);

                do {
                    minimizaArestas(solucaoVizinhaAresta, grafo, v);
                } while (!solucaoValida(solucaoVizinhaAresta, v, grafo));

                custoVizinho = calculaCusto(solucaoVizinhaAresta, grafo, v);

                if ((custoVizinho <= custoAtual || aceitar_custo_igual) && solucaoValida(solucaoVizinhaAresta, v, grafo)) {
                    custoAtual = custoVizinho;
                    substituiSol(solucao, solucaoVizinhaAresta, v);
                    melhorVizinhoEncontrado = 1;
                    // printf("\nA solução foi melhorada por minimização de arestas");
                }

                free(solucaoVizinhaAresta);
            }
                break;



            default:
                break;
        }

        iter++;
    }

    return custoAtual;
}



// Função para trocar dois vértices na solução
void trocaVertices(int *solucao, int v) {
    int vertice1, vertice2;

        // Escolhe aleatoriamente dois vértices diferentes e que nao estejam ja com os valores que queremos
        do {
            vertice1 = rand() % v;
            vertice2 = rand() % v;
        } while (vertice1 == vertice2 || solucao[vertice1]==0 || solucao[vertice2]==1);

        // Realiza a troca
        solucao[vertice1] = 0;
        solucao[vertice2] = 1;
}

// Função para minimizar arestas na solução
void minimizaArestas(int *solucao, int **grafo, int v) {
    int custoOriginal = calculaCusto(solucao, grafo, v);

    // correr todos os vértices da solução
    for (int i = 0; i < v; ++i) {
        if (solucao[i] == 1) {
            // para  cada vértice não selecionado, tenta minimizar o custo
            for (int j = 0; j < v; ++j) {
                if (solucao[j] == 0) {
                    // trocar o vértice i por j na solução
                    solucao[i] = 0;
                    solucao[j] = 1;

                    // ver se da uma solução valida e com menor custo
                    if (solucaoValida(solucao, v, grafo)) {
                        int custoNovo = calculaCusto(solucao, grafo, v);

                        if (custoNovo < custoOriginal) {
                            // se o custo for menor, aceita
                            custoOriginal = custoNovo;
                        } else {
                            // se o custo não for menor, desfaz
                            solucao[i] = 1;
                            solucao[j] = 0;
                        }
                    } else {
                        // se a solução não for valida, desfaz
                        solucao[i] = 1;
                        solucao[j] = 0;
                    }
                }
            }
        }
    }
}

// Função para realizar a seleção por torneio
void selecaoTorneio(chrom *populacao, int popSize, int tamanhoTorneio, chrom *paisSelecionados) {
    for (int i = 0; i < popSize; i++) {
        // escolher aleatoriamente alguns indivíduos para o torneio
        int participantes[tamanhoTorneio];
        for (int j = 0; j < tamanhoTorneio; j++) {
            participantes[j] = rand() % popSize;
        }

        // encontrar o melhor individuo do torneio
        int melhorIndice = -1;
        int melhorCusto = INT_MAX;  // Inicializado com um valor elevado
        for (int j = 0; j < tamanhoTorneio; j++) {
            int indiceAtual = participantes[j];
            if (populacao[indiceAtual].custo < melhorCusto) {
                melhorCusto = populacao[indiceAtual].custo;
                melhorIndice = indiceAtual;
            }
        }

        // atribuir o melhor indivíduo como pai selecionado
        paisSelecionados[i] = populacao[melhorIndice];


    }

}

void crossoverUmPonto(chrom pai1, chrom pai2, chrom *filho1, chrom *filho2, int v) {
    // ponto de crossover aleatório
    int pontoCrossover = rand() % v;

    *filho1 = pai1;
    *filho2 = pai2;

    // trocar os segmentos à direita do ponto
    for (int i = pontoCrossover; i < v; i++) {
        int temp = filho1->solucao[i];
        filho1->solucao[i] = filho2->solucao[i];
        filho2->solucao[i] = temp;
    }
}


void mutacaoBit(chrom *individuo, float taxaMutacao, int numGenes) {
    for (int i = 0; i < numGenes; i++) {
        if (rand() / (float)RAND_MAX < taxaMutacao) {
            // inverter o bit com probabilidade de taxaMutacao
            individuo->solucao[i] = 1 - individuo->solucao[i];
        }
    }
}

// Função para evoluir a população usando um algoritmo evolutivo
void evoluirPopulacao(chrom *populacao, int popSize, float taxaMutacao, int v, int **matriz, int k,
                      int tipoSelecao, int tipoCrossover, int tipoMutacao, int tipoEstrategiaInvalida) {

    // atualizar custos
    for (int i = 0; i < popSize; i++) {
        populacao[i].custo = calculaCusto(populacao[i].solucao, matriz, v);
    }

    int tamanhoTorneio = 2;

    // selecionar pais para usar no crossover
    chrom paisSelecionados[popSize];
    switch (tipoSelecao) {
        case 1:
            selecaoTorneio(populacao, popSize, tamanhoTorneio, paisSelecionados);
            break;
        case 2:
            selecaoRoleta(populacao, popSize, paisSelecionados);
            break;
        default:
            selecaoTorneio(populacao, popSize, tamanhoTorneio, paisSelecionados);
    }

    // crossover e mutação
    for (int i = 0; i < popSize; i += 2) {
        chrom filho1, filho2;

        // Crossover
        switch (tipoCrossover) {
            case 1:
                crossoverUmPonto(paisSelecionados[i], paisSelecionados[i + 1], &filho1, &filho2, v);
                break;
            case 2:
                crossoverDoisPontos(paisSelecionados[i], paisSelecionados[i + 1], &filho1, &filho2, v);
                break;
            default:
                crossoverUmPonto(paisSelecionados[i], paisSelecionados[i + 1], &filho1, &filho2, v);
        }

        // Mutação
        switch (tipoMutacao) {
            case 1:
                mutacaoBit(&filho1, taxaMutacao, v);
                mutacaoBit(&filho2, taxaMutacao, v);
                break;
            case 2:
                inversaoSequencia(filho1.solucao, v);
                inversaoSequencia(filho2.solucao, v);
                break;
                default:
                mutacaoBit(&filho1, taxaMutacao, v);
                mutacaoBit(&filho2, taxaMutacao, v);
                break;
        }


        // Tratamento de soluções inválidas
        switch (tipoEstrategiaInvalida) {
            case 1:
                // penalização
                estrategiaPenalizacaoReparacao(filho1.solucao, v, matriz, k, 1);
                estrategiaPenalizacaoReparacao(filho2.solucao, v, matriz, k, 1);
                break;
            case 2:
                // reparação
                estrategiaPenalizacaoReparacao(filho1.solucao, v, matriz, k, 2);
                estrategiaPenalizacaoReparacao(filho2.solucao, v, matriz, k, 2);
                break;
            default:
                // reparação
                estrategiaPenalizacaoReparacao(filho1.solucao, v, matriz, k, 2);
                estrategiaPenalizacaoReparacao(filho2.solucao, v, matriz, k, 2);
        }

        // custos
        filho1.custo = calculaCusto(filho1.solucao, matriz, v);
        filho2.custo = calculaCusto(filho2.solucao, matriz, v);

        int indicePai1 = i;
        int indicePai2 = (i + 1) % popSize; // garantir que o índice não ultrapassa o popSize

        if (filho1.custo < populacao[indicePai1].custo) {
            populacao[indicePai1] = filho1;
        }

        if (filho2.custo < populacao[indicePai2].custo) {
            populacao[indicePai2] = filho2;
        }

    }

}


void selecaoRoleta(chrom *populacao, int popSize, chrom *selecionados) {
    float totalFitness = 0.0;

    // calcular o total de aptidão da população
    for (int i = 0; i < popSize; i++) {
        totalFitness += 1.0 / populacao[i].custo; // considerando minimização, invertendo o custo como aptidão
    }

    // selecionar por roleta
    for (int i = 0; i < popSize; i++) {
        float pontoSelecao = ((float)rand() / RAND_MAX) * totalFitness;
        float acumulado = 0.0;

        // encontrar o cromo correspondente ao ponto de seleção
        for (int j = 0; j < popSize; j++) {
            acumulado += 1.0 / populacao[j].custo;
            if (acumulado >= pontoSelecao) {
                selecionados[i] = populacao[j];
                break;
            }
        }
    }
}

chrom encontraMelhorSolucao(chrom *populacao, int popSize) {
    chrom melhor = populacao[0];

    for (int i = 1; i < popSize; i++) {
        if (populacao[i].custo < melhor.custo) {
            melhor = populacao[i];
        }
    }

    return melhor;
}



int encontrarVerticeInvalido(int *solucao, int v) {
    for (int i = 0; i < v; i++) {
        if (solucao[i] == 1) {
            //ver se o vertice é invalido
            if (verticeInvalido(solucao, i, v)) {
                // retorna o indice do invalido
                return i;
            }
        }
    }
    return -1;  // se não encontrar invalidos
}

int verticeInvalido(int *solucao, int vertice, int v) {
    if (solucao[vertice] == 1) {
        if (verticeDesconectado(vertice, v)) {
            return 1;  // inválido
        }
    }
    return 0;  // válido
}

int verticeDesconectado(int vertice, int v) {
    return vertice > v / 2;
}


void trocaVerticeAleatorio(int *solucao, int verticeInvalido, int v) {
    // encontrar um vertice valido aleatorio diferente do inválido
    int verticeValido;
    do {
        verticeValido = rand() % v;
    } while (verticeValido == verticeInvalido);

    // troca o vertice invalido pelo valido
    solucao[verticeInvalido] = 0;
    solucao[verticeValido] = 1;
}

void crossoverDoisPontos(chrom pai1, chrom pai2, chrom *filho1, chrom *filho2, int v) {
    int pontoCrossover1 = rand() % v;
    int pontoCrossover2 = rand() % v;

    // garantir que os pontos de crossover sao diferentes
    while (pontoCrossover1 == pontoCrossover2) {
        pontoCrossover2 = rand() % v;
    }

    // garantir que pontoCrossover1 < pontoCrossover2
    if (pontoCrossover1 > pontoCrossover2) {
        int temp = pontoCrossover1;
        pontoCrossover1 = pontoCrossover2;
        pontoCrossover2 = temp;
    }

    *filho1 = pai1;
    *filho2 = pai2;

    // trocar os segmentos entre os pontos de crossover
    for (int i = pontoCrossover1; i <= pontoCrossover2; i++) {
        int temp = filho1->solucao[i];
        filho1->solucao[i] = filho2->solucao[i];
        filho2->solucao[i] = temp;
    }
}

void inversaoSequencia(int *solucao, int v) {
    int inicio = rand() % v;
    int fim = rand() % v;

    // garantir que o início é < que o fim
    if (inicio > fim) {
        int temp = inicio;
        inicio = fim;
        fim = temp;
    }

    // inverte a sequencia entre inicio e fim
    while (inicio < fim) {
        int temp = solucao[inicio];
        solucao[inicio] = solucao[fim];
        solucao[fim] = temp;
        inicio++;
        fim--;
    }
}






void estrategiaPenalizacaoReparacao(int *solucao, int v, int **matriz, int k, int tipoEstrategia) {
    if (tipoEstrategia == 1) {
        while (!solucaoValidaK(solucao, v, matriz, k)) {
            geraSolInicial(solucao, k, v, matriz);
        }
    } else if (tipoEstrategia == 2) {
        // tentar reparar a solução inválida
        // trocar vértices inválidos aleatoriamente até obter uma solução válida
        while (!solucaoValidaK(solucao, v, matriz, k)) {
            // vértice inválido
            int verticeInvalido = encontrarVerticeInvalido(solucao, v);
            if (verticeInvalido != -1) {
                // trocar o vértice inválido por um vértice válido aleatório
                trocaVerticeAleatorio(solucao, verticeInvalido, v);
            } else {
                geraSolInicial(solucao, k, v, matriz);
            }
        }
    }
}