#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"
 
int eh_planar_euler(GrafoLista *g);
int tem_subdivisao_k5_k33(GrafoLista *g);
int eh_planar(GrafoLista *g);

#endif