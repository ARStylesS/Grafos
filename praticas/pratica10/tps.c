#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tps.h"

InstanciaTSP *tsp_criar(int n) {
    InstanciaTSP *t = malloc(sizeof(InstanciaTSP));
    t->n = n;
    t->dist = calloc((size_t)(n * n), sizeof(int));
    return t;
}

void tsp_destruir(InstanciaTSP *t) {
    free(t->dist);
    free(t);
}

InstanciaTSP *grafo_para_tsp(Grafo *g) {
    int n = g->n;
    InstanciaTSP *t = tsp_criar(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                t->dist[i * n + j] = 0;
            } else {
                t->dist[i * n + j] = g->adj[i * n + j] ? 1 : 2;
            }
        }
    }
    return t;
}

int tsp_custo_rota(InstanciaTSP *t, const int *rota) {
    int n = t->n;
    int custo = 0;
    for (int i = 0; i < n - 1; i++) {
        custo += t->dist[rota[i] * n + rota[i + 1]];
    }
    custo += t->dist[rota[n - 1] * n + rota[0]];
    return custo;
}

static void tsp_rec(InstanciaTSP *t, int *atual, int *usado, int pos, int custo,
                    int *melhor, int *melhor_custo) {
    int n = t->n;
    if (pos == n) {
        int total = custo + t->dist[atual[n - 1] * n + atual[0]];
        if (total < *melhor_custo) {
            *melhor_custo = total;
            memcpy(melhor, atual, sizeof(int) * (size_t)n);
        }
        return;
    }
    for (int v = 1; v < n; v++) {
        if (!usado[v]) {
            usado[v] = 1;
            atual[pos] = v;
            tsp_rec(t, atual, usado, pos + 1, custo + t->dist[atual[pos - 1] * n + v],
                    melhor, melhor_custo);
            usado[v] = 0;
        }
    }
}

int tsp_forca_bruta(InstanciaTSP *t, int *melhor_rota) {
    int n = t->n;
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        melhor_rota[0] = 0;
        return 0;
    }

    int *atual = calloc((size_t)n, sizeof(int));
    int *usado = calloc((size_t)n, sizeof(int));
    int melhor_custo = INT_MAX;

    atual[0] = 0;
    usado[0] = 1;
    tsp_rec(t, atual, usado, 1, 0, melhor_rota, &melhor_custo);

    free(atual);
    free(usado);
    return melhor_custo;
}