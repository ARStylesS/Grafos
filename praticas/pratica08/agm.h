#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

DSU *dsu_criar(int n);
void dsu_destruir(DSU *d);
int find(DSU *d, int x);
int unir(DSU *d, int x, int y);

int kruskal(int n, Aresta *arestas, int m, Aresta *mst, int *qtd);

typedef struct NoPeso {
    int vertice, peso;
    struct NoPeso *prox;
} NoPeso;

typedef struct {
    int n;
    NoPeso **adj;
} GrafoPonderado;

GrafoPonderado *grafo_criar(int n);
void grafo_destruir(GrafoPonderado *g);
void grafo_adicionar_aresta(GrafoPonderado *g, int u, int v, int peso);

typedef struct {
    int vertice, chave;
} HeapNo;

typedef struct {
    HeapNo *dados;
    int *pos;
    int tamanho, capacidade;
} MinHeap;

MinHeap *heap_criar(int n);
void heap_destruir(MinHeap *h);
int heap_vazio(MinHeap *h);
HeapNo heap_extrair_min(MinHeap *h);
void heap_diminuir_chave(MinHeap *h, int vertice, int nova_chave);

int prim(GrafoPonderado *g, int origem, int *pred);

#endif