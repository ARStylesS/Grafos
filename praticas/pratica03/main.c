#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int main(void) {
    int num_vertices = 6;
    GrafoLista* g = criar_grafo(num_vertices);

    adicionar_aresta(g, 5, 2);
    adicionar_aresta(g, 5, 0);
    adicionar_aresta(g, 4, 0);
    adicionar_aresta(g, 4, 1);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 1);

    if (eh_dag(g)) {
        printf("O grafo eh um DAG.\n");
    } else {
        printf("O grafo possui ciclos (nao eh DAG).\n");
    }

    int tam_kahn = 0;
    int* res_kahn = ordenacao_topologica_kahn(g, &tam_kahn);
    if (res_kahn) {
        printf("Ordenacao Topologica (Kahn): ");
        for (int i = 0; i < tam_kahn; i++) {
            printf("%d ", res_kahn[i]);
        }
        printf("\n");
        free(res_kahn);
    }

    int tam_dfs = 0;
    int* res_dfs = ordenacao_topologica_dfs(g, &tam_dfs);
    if (res_dfs) {
        printf("Ordenacao Topologica (DFS): ");
        for (int i = 0; i < tam_dfs; i++) {
            printf("%d ", res_dfs[i]);
        }
        printf("\n");
        free(res_dfs);
    }

    liberar_grafo(g);
    return 0;
}