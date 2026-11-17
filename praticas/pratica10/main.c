#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

typedef int (*AlgoritmoGrafo)(Grafo *, int *);

static Grafo *gerar_grafo(int n, int densidade) {
    Grafo *g = grafo_criar(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < densidade) {
                grafo_adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

static double medir_grafo(AlgoritmoGrafo f, Grafo *g, int *saida, int *resultado) {
    long reps = 0;
    clock_t ini = clock();
    clock_t fim;
    do {
        *resultado = f(g, saida);
        reps++;
        fim = clock();
    } while ((fim - ini) < CLOCKS_PER_SEC / 50);
    double total_us = (double)(fim - ini) * 1e6 / (double)CLOCKS_PER_SEC;
    return total_us / (double)reps;
}

static double medir_tsp(InstanciaTSP *t, int *rota, int *custo) {
    long reps = 0;
    clock_t ini = clock();
    clock_t fim;
    do {
        *custo = tsp_forca_bruta(t, rota);
        reps++;
        fim = clock();
    } while ((fim - ini) < CLOCKS_PER_SEC / 50);
    double total_us = (double)(fim - ini) * 1e6 / (double)CLOCKS_PER_SEC;
    return total_us / (double)reps;
}

int main(void) {
    int tamanhos[] = {5, 8, 10, 12};
    int qtd = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    srand(42);

    printf("%-4s %-8s | %-8s %-13s | %-6s %-13s | %-9s %-14s | %-10s\n",
           "n", "arestas", "caminho", "tempo(us)", "ciclo", "tempo(us)",
           "TSP custo", "TSP tempo(us)", "custo == n");

    for (int k = 0; k < qtd; k++) {
        int n = tamanhos[k];
        Grafo *g = gerar_grafo(n, 50);
        InstanciaTSP *t = grafo_para_tsp(g);
        int *saida = malloc(sizeof(int) * (size_t)n);
        int *rota = malloc(sizeof(int) * (size_t)n);

        int tem_caminho = 0;
        int tem_ciclo = 0;
        int custo = 0;

        double t_caminho = medir_grafo(encontrar_caminho_hamiltoniano_bt, g, saida, &tem_caminho);
        double t_ciclo = medir_grafo(encontrar_ciclo_hamiltoniano_bt, g, saida, &tem_ciclo);
        double t_tsp = medir_tsp(t, rota, &custo);

        printf("%-4d %-8d | %-8s %-13.2f | %-6s %-13.2f | %-9d %-14.2f | %-10s\n",
               n, grafo_contar_arestas(g),
               tem_caminho ? "sim" : "nao", t_caminho,
               tem_ciclo ? "sim" : "nao", t_ciclo,
               custo, t_tsp,
               custo == n ? "sim" : "nao");

        free(saida);
        free(rota);
        tsp_destruir(t);
        grafo_destruir(g);
    }

    return 0;
}