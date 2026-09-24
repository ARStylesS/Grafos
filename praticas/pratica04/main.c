#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conectividade.h"
#include "planaridade.h"

static void analisar(GrafoLista *g) {
    int n = g->n;
    int m = g->m;
    int *eh_art = malloc((n > 0 ? n : 1) * sizeof(int));
    int (*pontes)[2] = malloc((m > 0 ? m : 1) * sizeof(int[2]));
    int qtd = analisar_conectividade(g, eh_art, pontes);

    printf("Articulacoes:");
    int achou = 0;
    for (int i = 0; i < n; i++)
        if (eh_art[i]) {
            printf(" %d", i);
            achou = 1;
        }
    if (!achou) printf(" nenhuma");
    printf("\n");

    printf("Pontes:");
    if (qtd == 0) printf(" nenhuma");
    for (int i = 0; i < qtd; i++)
        printf(" (%d,%d)", pontes[i][0], pontes[i][1]);
    printf("\n");

    printf("Euler (m <= 3n-6): %s\n",
           eh_planar_euler(g) ? "passou" : "falhou");

    int r = eh_planar(g);
    if (r == 1) printf("Planar\n");
    else if (r == 0) printf("Nao planar\n");
    else printf("Indefinido (n > 10)\n");

    free(eh_art);
    free(pontes);
}

static int ler_e_analisar(FILE *f) {
    int n, m;
    if (fscanf(f, "%d %d", &n, &m) != 2 || n < 0 || m < 0) return 0;

    GrafoLista *g = criar_grafo(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        if (fscanf(f, "%d %d", &u, &v) != 2 || u < 0 || u >= n ||
            v < 0 || v >= n) {
            liberar_grafo(g);
            return 0;
        }
        adicionar_aresta(g, u, v);
    }
    analisar(g);
    liberar_grafo(g);
    return 1;
}

static void demo(const char *nome, int n, int m, const int (*arestas)[2]) {
    GrafoLista *g = criar_grafo(n);
    for (int i = 0; i < m; i++)
        adicionar_aresta(g, arestas[i][0], arestas[i][1]);
    printf("=== %s ===\n", nome);
    analisar(g);
    printf("\n");
    liberar_grafo(g);
}

static void rodar_demos(void) {
    static const int k4_cauda[][2] = {
        {0,1},{0,2},{0,3},{1,2},{1,3},{2,3},{3,4},{4,5}};
    static const int k5[][2] = {
        {0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
    static const int k33[][2] = {
        {0,3},{0,4},{0,5},{1,3},{1,4},{1,5},{2,3},{2,4},{2,5}};
    static const int petersen[][2] = {
        {0,1},{1,2},{2,3},{3,4},{4,0},{0,5},{1,6},{2,7},{3,8},{4,9},
        {5,7},{7,9},{9,6},{6,8},{8,5}};

    demo("K4 com cauda", 6, 8, k4_cauda);
    demo("K5", 5, 10, k5);
    demo("K3,3", 6, 9, k33);
    demo("Petersen", 10, 15, petersen);
}

int main(int argc, char **argv) {
    FILE *f = NULL;

    if (argc > 1 && strcmp(argv[1], "-") == 0) f = stdin;
    else if (argc > 1) f = fopen(argv[1], "r");
    else f = fopen("entrada.txt", "r");

    if (!f) {
        if (argc > 1) {
            fprintf(stderr, "Nao foi possivel abrir %s\n", argv[1]);
            return 1;
        }
        rodar_demos();
        return 0;
    }

    int ok = ler_e_analisar(f);
    if (f != stdin) fclose(f);
    if (!ok) {
        fprintf(stderr, "Entrada invalida\n");
        return 1;
    }
    return 0;
}