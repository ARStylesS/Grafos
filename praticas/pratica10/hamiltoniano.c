#include <stdio.h>
#include <stdlib.h>
#include "hamiltoniano.h"

Grafo *grafo_criar(int n) {
    Grafo *g = malloc(sizeof(Grafo));
    g->n = n;
    g->adj = calloc((size_t)(n * n), sizeof(int));
    return g;
}

void grafo_destruir(Grafo *g) {
    free(g->adj);
    free(g);
}

void grafo_adicionar_aresta(Grafo *g, int u, int v) {
    if (u == v) {
        return;
    }
    g->adj[u * g->n + v] = 1;
    g->adj[v * g->n + u] = 1;
}

int grafo_contar_arestas(Grafo *g) {
    int total = 0;
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {
            total += g->adj[i * g->n + j];
        }
    }
    return total;
}

static int caminho_bt(Grafo *g, int *caminho, int *usado, int pos) {
    int n = g->n;
    if (pos == n) {
        return 1;
    }
    int ultimo = caminho[pos - 1];
    for (int v = 0; v < n; v++) {
        if (!usado[v] && g->adj[ultimo * n + v]) {
            usado[v] = 1;
            caminho[pos] = v;
            if (caminho_bt(g, caminho, usado, pos + 1)) {
                return 1;
            }
            usado[v] = 0;
        }
    }
    return 0;
}

int encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho) {
    int n = g->n;
    if (n == 0) {
        return 0;
    }
    int *usado = calloc((size_t)n, sizeof(int));
    for (int inicio = 0; inicio < n; inicio++) {
        usado[inicio] = 1;
        caminho[0] = inicio;
        if (caminho_bt(g, caminho, usado, 1)) {
            free(usado);
            return 1;
        }
        usado[inicio] = 0;
    }
    free(usado);
    return 0;
}

static int ciclo_bt(Grafo *g, int *ciclo, int *usado, int pos) {
    int n = g->n;
    if (pos == n) {
        return g->adj[ciclo[n - 1] * n + ciclo[0]];
    }
    int ultimo = ciclo[pos - 1];
    for (int v = 1; v < n; v++) {
        if (!usado[v] && g->adj[ultimo * n + v]) {
            usado[v] = 1;
            ciclo[pos] = v;
            if (ciclo_bt(g, ciclo, usado, pos + 1)) {
                return 1;
            }
            usado[v] = 0;
        }
    }
    return 0;
}

int encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo) {
    int n = g->n;
    if (n < 3) {
        return 0;
    }
    int *usado = calloc((size_t)n, sizeof(int));
    usado[0] = 1;
    ciclo[0] = 0;
    int achou = ciclo_bt(g, ciclo, usado, 1);
    free(usado);
    return achou;
}