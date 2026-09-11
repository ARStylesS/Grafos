#include <stdlib.h>
#include "busca_profundidade.h"
 
Pilha *pilha_criar(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    p->dados = malloc(sizeof(int) * (size_t)capacidade);
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}
 
void pilha_destruir(Pilha *p) {
    free(p->dados);
    free(p);
}
 
int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}
 
int pilha_cheia(Pilha *p) {
    return p->topo == p->capacidade - 1;
}
 
void pilha_empilhar(Pilha *p, int valor) {
    if (pilha_cheia(p)) {
        return;
    }
    p->topo++;
    p->dados[p->topo] = valor;
}
 
int pilha_desempilhar(Pilha *p) {
    if (pilha_vazia(p)) {
        return -1;
    }
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}
 
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *contador) {
    visitado[u] = 1;
    ordem[*contador] = u;
    (*contador)++;
 
    NoAdjacencia *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->vertice;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, pred, ordem, contador);
        }
        atual = atual->prox;
    }
}
 
int tem_ciclo(GrafoLista *g) {
    int *visitado = calloc((size_t)g->num_vertices, sizeof(int));
    int resultado = 0;
    int capacidade_pilha = g->num_vertices * g->num_vertices + 1;
    Pilha *pilha_vertices = pilha_criar(capacidade_pilha);
    Pilha *pilha_pais = pilha_criar(capacidade_pilha);
 
    for (int inicio = 0; inicio < g->num_vertices && !resultado; inicio++) {
        if (visitado[inicio]) {
            continue;
        }
        pilha_empilhar(pilha_vertices, inicio);
        pilha_empilhar(pilha_pais, -1);
 
        while (!pilha_vazia(pilha_vertices) && !resultado) {
            int u = pilha_desempilhar(pilha_vertices);
            int pai = pilha_desempilhar(pilha_pais);
            if (visitado[u]) {
                continue;
            }
            visitado[u] = 1;
 
            NoAdjacencia *atual = g->adj[u];
            while (atual != NULL) {
                int v = atual->vertice;
                if (!visitado[v]) {
                    pilha_empilhar(pilha_vertices, v);
                    pilha_empilhar(pilha_pais, u);
                } else if (v != pai) {
                    resultado = 1;
                    break;
                }
                atual = atual->prox;
            }
        }
    }
 
    pilha_destruir(pilha_vertices);
    pilha_destruir(pilha_pais);
    free(visitado);
    return resultado;
}