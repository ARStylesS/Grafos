#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <limits.h>

#define INF INT_MAX

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int n;
    Aresta **adj;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

/* Retorna 1 se tudo certo (sem ciclo negativo) e 0 se há ciclo negativo. */
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);

/* Chamar quando bellman_ford retornar 0. Imprime o ciclo negativo. */
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred);

#endif