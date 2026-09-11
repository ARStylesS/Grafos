#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
 
GrafoLista *criar_grafo(int num_vertices) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adj = malloc(sizeof(NoAdjacencia *) * (size_t)num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}
 
void destruir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        NoAdjacencia *atual = g->adj[i];
        while (atual != NULL) {
            NoAdjacencia *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}
 
void adicionar_aresta(GrafoLista *g, int u, int v) {
    NoAdjacencia *nu = malloc(sizeof(NoAdjacencia));
    nu->vertice = v;
    nu->prox = g->adj[u];
    g->adj[u] = nu;
 
    NoAdjacencia *nv = malloc(sizeof(NoAdjacencia));
    nv->vertice = u;
    nv->prox = g->adj[v];
    g->adj[v] = nv;
}
 
Fila *fila_criar(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    f->dados = malloc(sizeof(int) * (size_t)capacidade);
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}
 
void fila_destruir(Fila *f) {
    free(f->dados);
    free(f);
}
 
int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}
 
int fila_cheia(Fila *f) {
    return f->tamanho == f->capacidade;
}
 
void fila_enfileirar(Fila *f, int valor) {
    if (fila_cheia(f)) {
        return;
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}
 
int fila_desenfileirar(Fila *f) {
    if (fila_vazia(f)) {
        return -1;
    }
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}
 
void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    int *visitado = calloc((size_t)g->num_vertices, sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }
 
    Fila *f = fila_criar(g->num_vertices);
    dist[origem] = 0;
    visitado[origem] = 1;
    fila_enfileirar(f, origem);
 
    while (!fila_vazia(f)) {
        int u = fila_desenfileirar(f);
        NoAdjacencia *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->vertice;
            if (!visitado[v]) {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                fila_enfileirar(f, v);
            }
            atual = atual->prox;
        }
    }
 
    fila_destruir(f);
    free(visitado);
}
 
int eh_bipartido(GrafoLista *g) {
    int *cor = malloc(sizeof(int) * (size_t)g->num_vertices);
    for (int i = 0; i < g->num_vertices; i++) {
        cor[i] = -1;
    }
 
    Fila *f = fila_criar(g->num_vertices);
    int resultado = 1;
 
    for (int inicio = 0; inicio < g->num_vertices && resultado; inicio++) {
        if (cor[inicio] != -1) {
            continue;
        }
        cor[inicio] = 0;
        fila_enfileirar(f, inicio);
 
        while (!fila_vazia(f) && resultado) {
            int u = fila_desenfileirar(f);
            NoAdjacencia *atual = g->adj[u];
            while (atual != NULL) {
                int v = atual->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila_enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    resultado = 0;
                    break;
                }
                atual = atual->prox;
            }
        }
    }
 
    fila_destruir(f);
    free(cor);
    return resultado;
}
 
int contar_componentes(GrafoLista *g) {
    int *visitado = calloc((size_t)g->num_vertices, sizeof(int));
    int componentes = 0;
    Fila *f = fila_criar(g->num_vertices);
 
    for (int inicio = 0; inicio < g->num_vertices; inicio++) {
        if (visitado[inicio]) {
            continue;
        }
        componentes++;
        visitado[inicio] = 1;
        fila_enfileirar(f, inicio);
 
        while (!fila_vazia(f)) {
            int u = fila_desenfileirar(f);
            NoAdjacencia *atual = g->adj[u];
            while (atual != NULL) {
                int v = atual->vertice;
                if (!visitado[v]) {
                    visitado[v] = 1;
                    fila_enfileirar(f, v);
                }
                atual = atual->prox;
            }
        }
    }
 
    fila_destruir(f);
    free(visitado);
    return componentes;
}