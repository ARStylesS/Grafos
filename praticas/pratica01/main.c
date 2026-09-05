#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

void exibir_matriz(GrafoMatriz *g)
{
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj[i][j]);
        }

        printf("\n");
    }
}

void exibir_lista(GrafoLista *g)
{
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];

        printf("%d:", i);

        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->prox;
        }

        printf(" -> NULL\n" );
    }
}

int main(void)
{
    int numero_vertices = 4;

    GrafoMatriz *gm = criar_grafo_matriz(numero_vertices);

    if (gm == NULL) {
        printf("Erro ao criar grafo matriz.\n");
        return 1;
    }

    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 0, 2);
    inserir_aresta_matriz(gm, 1, 2);
    inserir_aresta_matriz(gm, 1, 3);
    inserir_aresta_matriz(gm, 2, 3);

    printf("Matriz de adjacencia:\n");

    exibir_matriz(gm);

    printf("\nGrau do vertice 0: %d\n",
           grau_matriz(gm, 0));

    printf("0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_matriz(gm, 0, 2)
               ? "Sim"
               : "Nao");

    remover_aresta_matriz(gm, 0, 2);

    printf("Depois da remocao, 0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_matriz(gm, 0, 2)
               ? "Sim"
               : "Nao");

    liberar_grafo_matriz(gm);

    GrafoLista *gl = criar_grafo_lista(numero_vertices);

    if (gl == NULL) {
        printf("Erro ao criar grafo lista.\n");
        return 1;
    }

    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 0, 2);
    inserir_aresta_lista(gl, 1, 2);
    inserir_aresta_lista(gl, 1, 3);
    inserir_aresta_lista(gl, 2, 3);

    printf("\nLista de adjacencia:\n");

    exibir_lista(gl);

    printf("\nGrau do vertice 0: %d\n",
           grau_lista(gl, 0));

    printf("0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_lista(gl, 0, 2)
               ? "Sim"
               : "Nao");

    remover_aresta_lista(gl, 0, 2);

    printf("Depois da remocao, 0 e 2 sao adjacentes? %s\n",
           sao_adjacentes_lista(gl, 0, 2)
               ? "Sim"
               : "Nao");

    liberar_grafo_lista(gl);

    return 0;
}