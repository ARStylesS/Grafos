#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobertura.h"

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

int eh_cobertura(Grafo *g, const int *cobertura) {
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {
            if (g->adj[i * g->n + j] && !cobertura[i] && !cobertura[j]) {
                return 0;
            }
        }
    }
    return 1;
}

static void backtracking(Grafo *g, int *atual, int tam, int *melhor, int *melhor_tam) {
    int n = g->n;
    int u = -1;
    int v = -1;

    for (int i = 0; i < n && u == -1; i++) {
        if (atual[i]) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (g->adj[i * n + j] && !atual[j]) {
                u = i;
                v = j;
                break;
            }
        }
    }

    if (u == -1) {
        if (tam < *melhor_tam) {
            *melhor_tam = tam;
            memcpy(melhor, atual, sizeof(int) * (size_t)n);
        }
        return;
    }

    if (tam + 1 >= *melhor_tam) {
        return;
    }

    atual[u] = 1;
    backtracking(g, atual, tam + 1, melhor, melhor_tam);
    atual[u] = 0;

    atual[v] = 1;
    backtracking(g, atual, tam + 1, melhor, melhor_tam);
    atual[v] = 0;
}

int cobertura_minima_bt(Grafo *g, int *cobertura) {
    int n = g->n;
    int *atual = calloc((size_t)n, sizeof(int));
    int melhor_tam = n;

    for (int i = 0; i < n; i++) {
        cobertura[i] = 1;
    }

    backtracking(g, atual, 0, cobertura, &melhor_tam);

    free(atual);
    return melhor_tam;
}

int cobertura_gulosa(Grafo *g, int *cobertura) {
    int n = g->n;
    int *restante = malloc(sizeof(int) * (size_t)(n * n));
    memcpy(restante, g->adj, sizeof(int) * (size_t)(n * n));

    for (int i = 0; i < n; i++) {
        cobertura[i] = 0;
    }

    int tam = 0;
    for (;;) {
        int escolhido = -1;
        int maior_grau = 0;

        for (int i = 0; i < n; i++) {
            int grau = 0;
            for (int j = 0; j < n; j++) {
                grau += restante[i * n + j];
            }
            if (grau > maior_grau) {
                maior_grau = grau;
                escolhido = i;
            }
        }

        if (escolhido == -1) {
            break;
        }

        cobertura[escolhido] = 1;
        tam++;
        for (int j = 0; j < n; j++) {
            restante[escolhido * n + j] = 0;
            restante[j * n + escolhido] = 0;
        }
    }

    free(restante);
    return tam;
}