#ifndef GRAFO_LISTA
#define GRAFO_LISTA

typedef struct no {

int vertice;
struct no *proximo;
} no;

typedef struct {
no **Lista;
int num_vertices;
}GrafoLista;

GrafoLista *criar_grafo(int,n);
void adiciionar_aresta(GrafoLista *g, int u, int v);

#endif