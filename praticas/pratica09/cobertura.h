#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct {
    int n;
    int *adj;
} Grafo;

Grafo *grafo_criar(int n);
void grafo_destruir(Grafo *g);
void grafo_adicionar_aresta(Grafo *g, int u, int v);
int grafo_contar_arestas(Grafo *g);

int eh_cobertura(Grafo *g, const int *cobertura);
int cobertura_minima_bt(Grafo *g, int *cobertura);
int cobertura_gulosa(Grafo *g, int *cobertura);

#endif