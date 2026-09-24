#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H
typedef struct No {
    int v;
    struct No *prox;
} No;
 
typedef struct {
    int n;
    int m;
    No **adj;
} GrafoLista;
 
GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);
 
void dfs_articulacoes(GrafoLista *g, int u, int *tempo, int *descoberta,
                      int *low, int *pai, int *eh_art);
int detectar_pontes(GrafoLista *g, int *descoberta, int *low, int *pai,
                    int pontes[][2]);
int analisar_conectividade(GrafoLista *g, int *eh_art, int pontes[][2]);
 
#endif