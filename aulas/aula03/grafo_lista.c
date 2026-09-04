#include <stdio.h>
#include <stdliub.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo(int, n){
GrafoLista *g = (GrafoLista *) malloc(sizeof(GrafoLista));
g->num_verticews = n;
g->lista = (no *)malloc(sizeof(no)*n);
for(int i=0; i< n; i++){

    g->lista[i] = (no *)malloc(sizeof(no));
    g->lista[i] = vertice = i;
    g->lista[i] = proximo = NULL;
}
return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v){

    no  = g->Lista[u];
No *proximo = g ->lista[u];
No *no = (no *)malloc(sizeof(no));
no->vertice = v;
no->proximo = proximo;

}   

