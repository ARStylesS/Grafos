#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

typedef int (*Algoritmo)(Grafo *, int *);

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

static double medir_us(Algoritmo f, Grafo *g, int *saida, int *tam) {
    long reps = 0;
    clock_t ini = clock();
    clock_t fim;
    do {
        *tam = f(g, saida);
        reps++;
        fim = clock();
    } while ((fim - ini) < CLOCKS_PER_SEC / 50);
    double total_us = (double)(fim - ini) * 1e6 / (double)CLOCKS_PER_SEC;
    return total_us / (double)reps;
}

int main(void) {
    int tamanhos[] = {5, 8, 10, 12, 15};
    int qtd = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    srand(42);

    printf("%-4s %-9s | %-8s %-14s | %-8s %-14s | %-8s %-8s\n",
           "n", "arestas", "BT tam", "BT tempo(us)", "Gul tam", "Gul tempo(us)", "valida", "razao");

    for (int k = 0; k < qtd; k++) {
        int n = tamanhos[k];
        Grafo *g = gerar_grafo(n, 40);
        int *cob_bt = malloc(sizeof(int) * (size_t)n);
        int *cob_gu = malloc(sizeof(int) * (size_t)n);
        int tam_bt = 0;
        int tam_gu = 0;

        double t_bt = medir_us(cobertura_minima_bt, g, cob_bt, &tam_bt);
        double t_gu = medir_us(cobertura_gulosa, g, cob_gu, &tam_gu);

        int ok = eh_cobertura(g, cob_bt) && eh_cobertura(g, cob_gu);
        double razao = tam_bt > 0 ? (double)tam_gu / (double)tam_bt : 1.0;

        printf("%-4d %-9d | %-8d %-14.2f | %-8d %-14.2f | %-8s %-8.2f\n",
               n, grafo_contar_arestas(g), tam_bt, t_bt, tam_gu, t_gu,
               ok ? "sim" : "nao", razao);

        free(cob_bt);
        free(cob_gu);
        grafo_destruir(g);
    }

    return 0;
}