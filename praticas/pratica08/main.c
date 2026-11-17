#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main(void) {
    int n = 6;
    Aresta arestas[] = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3},
        {2, 5, 2}, {2, 4, 4}, {3, 4, 3}, {5, 4, 3}
    };
    int m = (int)(sizeof(arestas) / sizeof(arestas[0]));

    Aresta *mst = malloc(sizeof(Aresta) * (size_t)n);
    int qtd = 0;
    int peso_k = kruskal(n, arestas, m, mst, &qtd);

    printf("Kruskal:\n");
    for (int i = 0; i < qtd; i++) {
        printf("  %d - %d (peso %d)\n", mst[i].u, mst[i].v, mst[i].peso);
    }
    printf("  Peso total: %d\n\n", peso_k);

    GrafoPonderado *g = grafo_criar(n);
    for (int i = 0; i < m; i++) {
        grafo_adicionar_aresta(g, arestas[i].u, arestas[i].v, arestas[i].peso);
    }

    int *pred = malloc(sizeof(int) * (size_t)n);
    int peso_p = prim(g, 0, pred);

    printf("Prim (origem 0):\n");
    for (int v = 1; v < n; v++) {
        printf("  %d - %d\n", pred[v], v);
    }
    printf("  Peso total: %d\n", peso_p);

    free(pred);
    free(mst);
    grafo_destruir(g);
    return 0;
}