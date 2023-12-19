int **leDados(char *nome_fich, int *k, int *v, int *a);
void mostraMatriz(int **mat, int m);
void init_rand();
void geraSolInicial(int *solucao, int k, int v, int **grafo);
void mostraSol(int *solucao, int v);
int calculaCusto(int *solucao, int **grafo, int v);
void substituiSol(int *a, int *b, int v);
bool solucaoValida(int *solucao, int v, int **grafo);
typedef struct {
    int *solucao;
    int custo;
} chrom;

bool solucaoValidaK(int *solucao, int v, int **grafo, int k) ;
