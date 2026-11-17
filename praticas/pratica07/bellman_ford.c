#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

GrafoListaPonderado *criar_grafo(int n) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    if (!g) return NULL;
    g->n = n;
    g->adj = calloc((size_t)n, sizeof(Aresta *));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    Aresta *a = malloc(sizeof(Aresta));
    if (!a) return;
    a->destino = v;
    a->peso = peso;
    a->prox = g->adj[u];
    g->adj[u] = a;
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->n; i++) {
        Aresta *a = g->adj[i];
        while (a) {
            Aresta *prox = a->prox;
            free(a);
            a = prox;
        }
    }
    free(g->adj);
    free(g);
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->n;

    /* 1) Inicialização */
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    /* 2) n-1 rodadas de relaxação de todas as arestas */
    for (int rodada = 1; rodada < n; rodada++) {
        int mudou = 0;

        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;

            for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
                int v = a->destino;
                if (dist[u] + a->peso < dist[v]) {
                    dist[v] = dist[u] + a->peso;
                    pred[v] = u;
                    mudou = 1;
                }
            }
        }
        if (!mudou) break;   /* convergiu antes: otimização */
    }

    /* 3) Passada extra: se ainda relaxa, há ciclo negativo */
    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;

        for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
            if (dist[u] + a->peso < dist[a->destino]) {
                return 0;   /* ciclo negativo */
            }
        }
    }

    return 1;   /* sucesso */
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred) {
    int n = g->n;
    int x = -1;

    /* 1) Acha uma aresta que ainda relaxa e liga o predecessor dela */
    for (int u = 0; u < n && x == -1; u++) {
        if (dist[u] == INF) continue;

        for (Aresta *a = g->adj[u]; a != NULL; a = a->prox) {
            if (dist[u] + a->peso < dist[a->destino]) {
                pred[a->destino] = u;
                x = a->destino;
                break;
            }
        }
    }

    if (x == -1) {
        printf("Nao ha ciclo negativo.\n");
        return;
    }

    /* 2) Retrocede n vezes pelo pred[]: garante estar DENTRO do ciclo */
    for (int i = 0; i < n; i++) {
        x = pred[x];
    }

    /* 3) Percorre pred[] até voltar a x, guardando o ciclo (ordem invertida) */
    int *ciclo = malloc((size_t)n * sizeof(int));
    if (!ciclo) return;
    int tam = 0;

    int v = x;
    do {
        ciclo[tam++] = v;
        v = pred[v];
    } while (v != x);

    /* 4) Imprime na ordem correta e fecha o ciclo */
    printf("Ciclo negativo: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d -> ", ciclo[i]);
    }
    printf("%d\n", ciclo[tam - 1]);

    free(ciclo);
}