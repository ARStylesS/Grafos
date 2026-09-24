#include <stdlib.h>
#include "conectividade.h"
 
GrafoLista *criar_grafo(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;
    g->m = 0;
    g->adj = calloc(n, sizeof(No *));
    return g;
}
 
static void inserir(GrafoLista *g, int u, int v) {
    No *novo = malloc(sizeof(No));
    novo->v = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}
 
void adicionar_aresta(GrafoLista *g, int u, int v) {
    inserir(g, u, v);
    inserir(g, v, u);
    g->m++;
}
 
void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        No *p = g->adj[i];
        while (p) {
            No *t = p->prox;
            free(p);
            p = t;
        }
    }
    free(g->adj);
    free(g);
}
 
void dfs_articulacoes(GrafoLista *g, int u, int *tempo, int *descoberta,
                      int *low, int *pai, int *eh_art) {
    int filhos = 0;
    descoberta[u] = low[u] = ++(*tempo);
 
    for (No *p = g->adj[u]; p; p = p->prox) {
        int v = p->v;
        if (descoberta[v] == 0) {
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, tempo, descoberta, low, pai, eh_art);
            if (low[v] < low[u]) low[u] = low[v];
            if (pai[u] != -1 && low[v] >= descoberta[u]) eh_art[u] = 1;
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) low[u] = descoberta[v];
        }
    }
 
    if (pai[u] == -1 && filhos > 1) eh_art[u] = 1;
}
 
int detectar_pontes(GrafoLista *g, int *descoberta, int *low, int *pai,
                    int pontes[][2]) {
    int qtd = 0;
    for (int v = 0; v < g->n; v++) {
        if (pai[v] != -1 && low[v] > descoberta[pai[v]]) {
            pontes[qtd][0] = pai[v];
            pontes[qtd][1] = v;
            qtd++;
        }
    }
    return qtd;
}
 
int analisar_conectividade(GrafoLista *g, int *eh_art, int pontes[][2]) {
    int n = g->n;
    int *descoberta = calloc(n, sizeof(int));
    int *low = calloc(n, sizeof(int));
    int *pai = malloc(n * sizeof(int));
    int tempo = 0;
 
    for (int i = 0; i < n; i++) {
        pai[i] = -1;
        eh_art[i] = 0;
    }
    for (int i = 0; i < n; i++)
        if (descoberta[i] == 0)
            dfs_articulacoes(g, i, &tempo, descoberta, low, pai, eh_art);
 
    int qtd = detectar_pontes(g, descoberta, low, pai, pontes);
 
    free(descoberta);
    free(low);
    free(pai);
    return qtd;
}