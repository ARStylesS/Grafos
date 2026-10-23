#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main(void) {
    GrafoListaPonderado g;
    iniciar_grafo(&g, 6);

    adicionar_aresta(&g, 0, 1, 4);  // A-B
    adicionar_aresta(&g, 0, 2, 2);  // A-C
    adicionar_aresta(&g, 1, 2, 1);  // B-C
    adicionar_aresta(&g, 1, 3, 5);  // B-D
    adicionar_aresta(&g, 1, 4, 8);  // B-E
    adicionar_aresta(&g, 2, 3, 4);  // C-D
    adicionar_aresta(&g, 2, 4, 10); // C-E
    adicionar_aresta(&g, 3, 4, 2);  // D-E
    adicionar_aresta(&g, 3, 5, 1);  // D-F
    adicionar_aresta(&g, 4, 5, 3);  // E-F

    int dist[MAX_VERTICES];
    int pred[MAX_VERTICES];
    dijkstra(&g, 0, dist, pred);

    for (int v = 0; v < g.num_vertices; v++) {
        printf("A -> %c | dist = %d | caminho: ", 'A' + v, dist[v]);
        reconstruir_caminho(0, v, pred);
        printf("\n");
    }

    liberar_grafo(&g);
    return 0;
}