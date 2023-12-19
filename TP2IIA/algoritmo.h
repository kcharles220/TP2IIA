#include "utils.h"

int trepacolinas(int *solucao, int **grafo, int v, int nr_iter, int aceitar_custo_igual, int tipo_vizinhanca);
void trocaVertices(int *solucao, int v);
void minimizaArestas(int *solucao, int **grafo, int v);
void selecaoTorneio(chrom *populacao, int popSize, int tamanhoTorneio, chrom *paisSelecionados);
void mutacaoBit(chrom *individuo, float taxaMutacao, int numGenes) ;
void evoluirPopulacao(chrom *populacao, int popSize, float taxaMutacao, int v, int **matriz, int k,
                      int tipoSelecao, int tipoCrossover, int tipoMutacao, int tipoEstrategiaInvalida);
chrom encontraMelhorSolucao(chrom *populacao, int popSize);
void selecaoRoleta(chrom *populacao, int popSize, chrom *selecionados);
void crossoverDoisPontos(chrom pai1, chrom pai2, chrom *filho1, chrom *filho2, int v);
void estrategiaPenalizacaoReparacao(int *solucao, int v, int **matriz, int k, int tipoEstrategia);
void inversaoSequencia(int *solucao, int v);
void trocaVerticeAleatorio(int *solucao, int verticeInvalido, int v);
int verticeInvalido(int *solucao, int vertice, int v);
int verticeDesconectado(int vertice, int v);
int encontrarVerticeInvalido(int *solucao, int v);