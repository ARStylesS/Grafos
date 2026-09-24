#ifndef COLORACAO_H
#define COLORACAO_H

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
 
int *coloracao_gulosa(GrafoLista *g, int *num_cores);
int *coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);

#endif