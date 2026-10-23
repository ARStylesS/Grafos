#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAX_VERTICES 6
#define INF 10000000

typedef struct No {
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    int num_vertices;
    No *lista[MAX_VERTICES];
} GrafoListaPonderado;

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

void iniciar_grafo(GrafoListaPonderado *g, int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

MinHeap *criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int nova_dist);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif