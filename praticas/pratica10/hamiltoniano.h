#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

typedef struct {
    int n;
    int *adj;
} Grafo;

Grafo *grafo_criar(int n);
void grafo_destruir(Grafo *g);
void grafo_adicionar_aresta(Grafo *g, int u, int v);
int grafo_contar_arestas(Grafo *g);

int encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho);
int encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo);

#endif