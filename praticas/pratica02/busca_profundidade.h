#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H
 
#include "busca_largura.h"
 
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;
 
Pilha *pilha_criar(int capacidade);
void pilha_destruir(Pilha *p);
int pilha_vazia(Pilha *p);
int pilha_cheia(Pilha *p);
void pilha_empilhar(Pilha *p, int valor);
int pilha_desempilhar(Pilha *p);
 
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *contador);
int tem_ciclo(GrafoLista *g);
 
#endif