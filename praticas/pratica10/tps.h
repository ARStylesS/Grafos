#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

typedef struct {
    int n;
    int *dist;
} InstanciaTSP;

InstanciaTSP *tsp_criar(int n);
void tsp_destruir(InstanciaTSP *t);
InstanciaTSP *grafo_para_tsp(Grafo *g);
int tsp_custo_rota(InstanciaTSP *t, const int *rota);
int tsp_forca_bruta(InstanciaTSP *t, int *melhor_rota);

#endif