#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

static void executar(GrafoListaPonderado *g, int origem) {
    int *dist = malloc((size_t)g->n * sizeof(int));
    int *pred = malloc((size_t)g->n * sizeof(int));
    if (!dist || !pred) {
        free(dist);
        free(pred);
        return;
    }

    if (bellman_ford(g, origem, dist, pred)) {
        printf("Sem ciclo negativo. Distancias a partir de %d:\n", origem);
        for (int i = 0; i < g->n; i++) {
            if (dist[i] == INF) printf("  %d: INF\n", i);
            else                printf("  %d: %d\n", i, dist[i]);
        }
    } else {
        reconstruir_ciclo_negativo(g, dist, pred);
    }

    free(dist);
    free(pred);
}

int main(void) {
    /* Grafo 1: aresta negativa, sem ciclo negativo */
    GrafoListaPonderado *g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1, 6);
    adicionar_aresta(g1, 0, 2, 7);
    adicionar_aresta(g1, 1, 2, 8);
    adicionar_aresta(g1, 1, 3, 5);
    adicionar_aresta(g1, 1, 4, -4);
    adicionar_aresta(g1, 2, 3, -3);
    adicionar_aresta(g1, 2, 4, 9);
    adicionar_aresta(g1, 3, 1, -2);
    adicionar_aresta(g1, 4, 3, 7);
    printf("=== Grafo 1 ===\n");
    executar(g1, 0);
    liberar_grafo(g1);

    /* Grafo 2: ciclo negativo 1 -> 2 -> 3 -> 1 (soma = -3) */
    GrafoListaPonderado *g2 = criar_grafo(5);
    adicionar_aresta(g2, 0, 1, 1);
    adicionar_aresta(g2, 1, 2, -1);
    adicionar_aresta(g2, 2, 3, -1);
    adicionar_aresta(g2, 3, 1, -1);
    adicionar_aresta(g2, 3, 4, 2);
    printf("\n=== Grafo 2 ===\n");
    executar(g2, 0);
    liberar_grafo(g2);

    return 0;
}