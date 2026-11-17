#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "agm.h"

#define INF INT_MAX

DSU *dsu_criar(int n) {
    DSU *d = malloc(sizeof(DSU));
    d->n = n;
    d->pai = malloc(sizeof(int) * (size_t)n);
    d->rank = calloc((size_t)n, sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
    }
    return d;
}

void dsu_destruir(DSU *d) {
    free(d->pai);
    free(d->rank);
    free(d);
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

int unir(DSU *d, int x, int y) {
    int rx = find(d, x);
    int ry = find(d, y);
    if (rx == ry) {
        return 0;
    }
    if (d->rank[rx] < d->rank[ry]) {
        d->pai[rx] = ry;
    } else if (d->rank[rx] > d->rank[ry]) {
        d->pai[ry] = rx;
    } else {
        d->pai[ry] = rx;
        d->rank[rx]++;
    }
    return 1;
}

static int comparar_arestas(const void *a, const void *b) {
    const Aresta *x = a;
    const Aresta *y = b;
    return (x->peso > y->peso) - (x->peso < y->peso);
}

int kruskal(int n, Aresta *arestas, int m, Aresta *mst, int *qtd) {
    qsort(arestas, (size_t)m, sizeof(Aresta), comparar_arestas);

    DSU *d = dsu_criar(n);
    int total = 0;
    *qtd = 0;

    for (int i = 0; i < m && *qtd < n - 1; i++) {
        if (unir(d, arestas[i].u, arestas[i].v)) {
            mst[(*qtd)++] = arestas[i];
            total += arestas[i].peso;
        }
    }

    dsu_destruir(d);
    return total;
}

GrafoPonderado *grafo_criar(int n) {
    GrafoPonderado *g = malloc(sizeof(GrafoPonderado));
    g->n = n;
    g->adj = malloc(sizeof(NoPeso *) * (size_t)n);
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void grafo_destruir(GrafoPonderado *g) {
    for (int i = 0; i < g->n; i++) {
        NoPeso *atual = g->adj[i];
        while (atual != NULL) {
            NoPeso *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

void grafo_adicionar_aresta(GrafoPonderado *g, int u, int v, int peso) {
    NoPeso *nu = malloc(sizeof(NoPeso));
    nu->vertice = v;
    nu->peso = peso;
    nu->prox = g->adj[u];
    g->adj[u] = nu;

    NoPeso *nv = malloc(sizeof(NoPeso));
    nv->vertice = u;
    nv->peso = peso;
    nv->prox = g->adj[v];
    g->adj[v] = nv;
}

static void heap_trocar(MinHeap *h, int i, int j) {
    HeapNo tmp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = tmp;
    h->pos[h->dados[i].vertice] = i;
    h->pos[h->dados[j].vertice] = j;
}

static void heap_subir(MinHeap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[pai].chave <= h->dados[i].chave) {
            break;
        }
        heap_trocar(h, pai, i);
        i = pai;
    }
}

static void heap_descer(MinHeap *h, int i) {
    for (;;) {
        int menor = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        if (esq < h->tamanho && h->dados[esq].chave < h->dados[menor].chave) {
            menor = esq;
        }
        if (dir < h->tamanho && h->dados[dir].chave < h->dados[menor].chave) {
            menor = dir;
        }
        if (menor == i) {
            break;
        }
        heap_trocar(h, i, menor);
        i = menor;
    }
}

MinHeap *heap_criar(int n) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->dados = malloc(sizeof(HeapNo) * (size_t)n);
    h->pos = malloc(sizeof(int) * (size_t)n);
    h->capacidade = n;
    h->tamanho = n;
    for (int v = 0; v < n; v++) {
        h->dados[v].vertice = v;
        h->dados[v].chave = INF;
        h->pos[v] = v;
    }
    return h;
}

void heap_destruir(MinHeap *h) {
    free(h->dados);
    free(h->pos);
    free(h);
}

int heap_vazio(MinHeap *h) {
    return h->tamanho == 0;
}

HeapNo heap_extrair_min(MinHeap *h) {
    HeapNo raiz = h->dados[0];
    HeapNo ultimo = h->dados[h->tamanho - 1];
    h->tamanho--;
    h->pos[raiz.vertice] = -1;
    if (h->tamanho > 0) {
        h->dados[0] = ultimo;
        h->pos[ultimo.vertice] = 0;
        heap_descer(h, 0);
    }
    return raiz;
}

void heap_diminuir_chave(MinHeap *h, int vertice, int nova_chave) {
    int i = h->pos[vertice];
    h->dados[i].chave = nova_chave;
    heap_subir(h, i);
}

int prim(GrafoPonderado *g, int origem, int *pred) {
    int n = g->n;
    int *chave = malloc(sizeof(int) * (size_t)n);
    for (int i = 0; i < n; i++) {
        chave[i] = INF;
        pred[i] = -1;
    }

    MinHeap *h = heap_criar(n);
    chave[origem] = 0;
    heap_diminuir_chave(h, origem, 0);

    int total = 0;
    while (!heap_vazio(h)) {
        HeapNo no = heap_extrair_min(h);
        if (no.chave == INF) {
            break;
        }
        int u = no.vertice;
        total += no.chave;

        NoPeso *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->vertice;
            if (h->pos[v] != -1 && atual->peso < chave[v]) {
                chave[v] = atual->peso;
                pred[v] = u;
                heap_diminuir_chave(h, v, atual->peso);
            }
            atual = atual->prox;
        }
    }

    heap_destruir(h);
    free(chave);
    return total;
}