#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**)malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista* g, int origem, int destino) {
    No* novo = (No*)malloc(sizeof(No));
    novo->vertice = destino;
    novo->proximo = g->listas[origem];
    g->listas[origem] = novo;
}

void liberar_grafo(GrafoLista* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->listas[i];
        while (atual) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *grau_entrada = (int*)calloc(n, sizeof(int));
    
    for (int u = 0; u < n; u++) {
        No* p = g->listas[u];
        while (p) {
            grau_entrada[p->vertice]++;
            p = p->proximo;
        }
    }

    int *fila = (int*)malloc(n * sizeof(int));
    int inicio = 0, fim = 0;

    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *resultado = (int*)malloc(n * sizeof(int));
    int count = 0;

    while (inicio < fim) {
        int u = fila[inicio++];
        resultado[count++] = u;

        No* p = g->listas[u];
        while (p) {
            int v = p->vertice;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
            p = p->proximo;
        }
    }

    free(grau_entrada);
    free(fila);

    if (count != n) {
        free(resultado);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = count;
    return resultado;
}

static int dfs_rec(GrafoLista *g, int u, int *visitado, int *pilha_rec, int *ordem, int *idx) {
    visitado[u] = 1;
    pilha_rec[u] = 1;

    No* p = g->listas[u];
    while (p) {
        int v = p->vertice;
        if (!visitado[v]) {
            if (dfs_rec(g, v, visitado, pilha_rec, ordem, idx)) {
                return 1;
            }
        } else if (pilha_rec[v]) {
            return 1;
        }
        p = p->proximo;
    }

    pilha_rec[u] = 0;
    ordem[(*idx)--] = u;
    return 0;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *visitado = (int*)calloc(n, sizeof(int));
    int *pilha_rec = (int*)calloc(n, sizeof(int));
    int *resultado = (int*)malloc(n * sizeof(int));
    int idx = n - 1;
    int tem_ciclo = 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            if (dfs_rec(g, i, visitado, pilha_rec, resultado, &idx)) {
                tem_ciclo = 1;
                break;
            }
        }
    }

    free(visitado);
    free(pilha_rec);

    if (tem_ciclo) {
        free(resultado);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = n;
    return resultado;
}

int eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem == NULL) {
        return 0;
    }
    free(ordem);
    return 1;
}