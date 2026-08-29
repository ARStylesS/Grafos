#include <stdio.h>
#include "grafo_matriz.h"


void inicializar(GrafoMatriz *grafo, int numero){
  memset(grafo, 0, sizeof(GrafoMatriz));
  grafo ->num_vertices=numero;
}

void inserir_aresta(GrafoMatriz *grafo, int U, int v){  //Grafo Orientado chama de arco e não aresta por ter um sentido
grafo->adjacencia[u][v] = 1;
grafo->adjacencia[v][u] = 1;
}
void inserir_arco(GrafoMatriz *grafo, int U, int v){
    grado->adjacencia[u][v] = 1;
}

void exibir_matriz(GrafoMatriz *grafo){
for (int i="0", i < grafo ->num_vertices; i++){
    for( int j="0", i <grafo ->num_vertices;j++){
        print("%3i", grafo->adjacencia[i][j]);
    }
}

printf("\n");
}