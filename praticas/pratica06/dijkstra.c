#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

/* ---------- Grafo ---------- */
void iniciar_grafo(GrafoListaPonderado *g, int n) {
    g->num_vertices = n;
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }
}

static void inserir_no(GrafoListaPonderado *g, int u, int v, int peso) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        exit(EXIT_FAILURE);
    }
    novo->vertice = v;
    novo->peso = peso;
    novo->proximo = g->lista[u];
    g->lista[u] = novo;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    inserir_no(g, u, v, peso);
    inserir_no(g, v, u, peso);
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            No *prox = no->proximo;
            free(no);
            no = prox;
        }
        g->lista[i] = NULL;
    }
}

/* ---------- Min-Heap ---------- */
static void trocar(MinHeap *h, int i, int j) {
    NoHeap tmp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = tmp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

static void descer(MinHeap *h, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia) {
        menor = esq;
    }
    if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia) {
        menor = dir;
    }
    if (menor != i) {
        trocar(h, i, menor);
        descer(h, menor);
    }
}

MinHeap *criar_min_heap(int capacidade) {
    MinHeap *h = malloc(sizeof(MinHeap));
    if (h == NULL) {
        exit(EXIT_FAILURE);
    }
    h->dados = malloc((size_t)capacidade * sizeof(NoHeap));
    h->posicao = malloc((size_t)capacidade * sizeof(int));
    if (h->dados == NULL || h->posicao == NULL) {
        exit(EXIT_FAILURE);
    }
    h->capacidade = capacidade;
    h->tamanho = 0;
    return h;
}

NoHeap extrair_minimo(MinHeap *h) {
    NoHeap raiz = h->dados[0];
    trocar(h, 0, h->tamanho - 1);
    h->posicao[raiz.vertice] = -1; // marca: saiu do heap
    h->tamanho--;
    descer(h, 0);
    return raiz;
}

void diminuir_chave(MinHeap *h, int vertice, int nova_dist) {
    int i = h->posicao[vertice];
    h->dados[i].distancia = nova_dist;
    while (i > 0 && h->dados[i].distancia < h->dados[(i - 1) / 2].distancia) {
        trocar(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}   // <-- era esta chave que faltava

/* ---------- Dijkstra ---------- */
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;
    MinHeap *h = criar_min_heap(n);

    for (int v = 0; v < n; v++) {
        dist[v] = INF;
        pred[v] = -1;
        h->dados[v].vertice = v;
        h->dados[v].distancia = INF;
        h->posicao[v] = v;
    }
    h->tamanho = n;

    dist[origem] = 0;
    diminuir_chave(h, origem, 0);

    while (h->tamanho > 0) {
        NoHeap u = extrair_minimo(h);
        if (u.distancia == INF) {
            break; // o que sobrou é inalcançável
        }

        for (No *no = g->lista[u.vertice]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            if (h->posicao[v] != -1 && dist[u.vertice] + no->peso < dist[v]) {
                dist[v] = dist[u.vertice] + no->peso;
                pred[v] = u.vertice;
                diminuir_chave(h, v, dist[v]);
            }
        }
    }

    free(h->dados);
    free(h->posicao);
    free(h);
}

/* ---------- Caminho ---------- */
void reconstruir_caminho(int origem, int destino, int *pred) {
    if (destino == origem) {
        printf("%c", 'A' + origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("(sem caminho)");
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %c", 'A' + destino);
}