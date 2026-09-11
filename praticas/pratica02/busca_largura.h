#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H
 
typedef struct NoAdjacencia {
    int vertice;
    struct NoAdjacencia *prox;
} NoAdjacencia;
 
typedef struct {
    int num_vertices;
    NoAdjacencia **adj;
} GrafoLista;
 
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;
 
GrafoLista *criar_grafo(int num_vertices);
void destruir_grafo(GrafoLista *g);
void adicionar_aresta(GrafoLista *g, int u, int v);
 
Fila *fila_criar(int capacidade);
void fila_destruir(Fila *f);
int fila_vazia(Fila *f);
int fila_cheia(Fila *f);
void fila_enfileirar(Fila *f, int valor);
int fila_desenfileirar(Fila *f);
 
void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);
 
#endif
 