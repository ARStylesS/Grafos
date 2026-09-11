#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"
 
static void imprimir_bfs(GrafoLista *g, int origem) {
    int *dist = malloc(sizeof(int) * (size_t)g->num_vertices);
    int *pred = malloc(sizeof(int) * (size_t)g->num_vertices);
 
    bfs(g, origem, dist, pred);
 
    printf("BFS a partir do vertice %d:\n", origem);
    for (int i = 0; i < g->num_vertices; i++) {
        printf("  vertice %d -> distancia %d, predecessor %d\n", i, dist[i], pred[i]);
    }
 
    free(dist);
    free(pred);
}
 
static void imprimir_dfs(GrafoLista *g, int origem) {
    int *visitado = calloc((size_t)g->num_vertices, sizeof(int));
    int *pred = malloc(sizeof(int) * (size_t)g->num_vertices);
    int *ordem = malloc(sizeof(int) * (size_t)g->num_vertices);
    int contador = 0;
 
    for (int i = 0; i < g->num_vertices; i++) {
        pred[i] = -1;
    }
 
    dfs_recursiva(g, origem, visitado, pred, ordem, &contador);
 
    printf("DFS a partir do vertice %d:\n  ordem de visita: ", origem);
    for (int i = 0; i < contador; i++) {
        printf("%d ", ordem[i]);
    }
    printf("\n");
 
    free(visitado);
    free(pred);
    free(ordem);
}
 
int main(void) {
    int num_vertices = 8;
    GrafoLista *g = criar_grafo(num_vertices);
 
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 4, 5);
    adicionar_aresta(g, 6, 7);
 
    imprimir_bfs(g, 0);
    printf("\n");
    imprimir_dfs(g, 0);
    printf("\n");
 
    printf("O grafo e bipartido? %s\n", eh_bipartido(g) ? "sim" : "nao");
    printf("Numero de componentes conexas: %d\n", contar_componentes(g));
    printf("O grafo possui ciclo? %s\n", tem_ciclo(g) ? "sim" : "nao");
 
    destruir_grafo(g);
    return 0;
}
 
