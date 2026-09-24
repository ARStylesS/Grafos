#include <stdio.h>
#include <stdlib.h>

#include "coloracao.h"

typedef struct {
    int v;
    int grau;
} Par;
 
GrafoLista *criar_grafo(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;
    g->m = 0;
    g->adj = calloc(n > 0 ? n : 1, sizeof(No *));
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
 
static int *colorir_na_ordem(GrafoLista *g, const int *ordem, int *num_cores) {
    int n = g->n;
    int *cor = malloc((n > 0 ? n : 1) * sizeof(int));
    int *usada = malloc((n + 1) * sizeof(int));
    int max = 0;
 
    for (int i = 0; i < n; i++) cor[i] = -1;
    for (int i = 0; i <= n; i++) usada[i] = -1;
 
    for (int i = 0; i < n; i++) {
        int v = ordem[i];
        for (No *p = g->adj[v]; p; p = p->prox)
            if (cor[p->v] != -1) usada[cor[p->v]] = v;
 
        int c = 0;
        while (usada[c] == v) c++;
        cor[v] = c;
        if (c + 1 > max) max = c + 1;
    }
 
    free(usada);
    *num_cores = max;
    return cor;
}
 
int *coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->n;
    int *ordem = malloc((n > 0 ? n : 1) * sizeof(int));
    for (int i = 0; i < n; i++) ordem[i] = i;
 
    int *cor = colorir_na_ordem(g, ordem, num_cores);
    free(ordem);
    return cor;
}
 
static int comparar(const void *a, const void *b) {
    const Par *x = a;
    const Par *y = b;
    if (x->grau != y->grau) return y->grau - x->grau;
    return x->v - y->v;
}
 
int *coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->n;
    Par *pares = malloc((n > 0 ? n : 1) * sizeof(Par));
    int *ordem = malloc((n > 0 ? n : 1) * sizeof(int));
 
    for (int v = 0; v < n; v++) {
        int grau = 0;
        for (No *p = g->adj[v]; p; p = p->prox) grau++;
        pares[v].v = v;
        pares[v].grau = grau;
    }
    qsort(pares, n, sizeof(Par), comparar);
    for (int i = 0; i < n; i++) ordem[i] = pares[i].v;
 
    int *cor = colorir_na_ordem(g, ordem, num_cores);
    free(pares);
    free(ordem);
    return cor;
}
 
int eh_bipartido(GrafoLista *g) {
    int n = g->n;
    int *cor = malloc((n > 0 ? n : 1) * sizeof(int));
    int *fila = malloc((n > 0 ? n : 1) * sizeof(int));
    int ok = 1;
 
    for (int i = 0; i < n; i++) cor[i] = -1;
 
    for (int s = 0; s < n && ok; s++) {
        if (cor[s] != -1) continue;
 
        int ini = 0, fim = 0;
        cor[s] = 0;
        fila[fim++] = s;
 
        while (ini < fim && ok) {
            int u = fila[ini++];
            for (No *p = g->adj[u]; p; p = p->prox) {
                int v = p->v;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila[fim++] = v;
                } else if (cor[v] == cor[u]) {
                    ok = 0;
                    break;
                }
            }
        }
    }
 
    free(cor);
    free(fila);
    return ok;
}




