#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coloracao.h"

static void imprimir(const char *titulo, int *cor, int n, int k) {
    printf("%s: %d cores |", titulo, k);
    for (int i = 0; i < n; i++) printf(" %d:%d", i, cor[i]);
    printf("\n");
}
 
static void analisar(GrafoLista *g) {
    int k1, k2;
    int *c1 = coloracao_gulosa(g, &k1);
    int *c2 = coloracao_welsh_powell(g, &k2);
 
    imprimir("Gulosa       ", c1, g->n, k1);
    imprimir("Welsh-Powell ", c2, g->n, k2);
    printf("Bipartido: %s\n", eh_bipartido(g) ? "sim" : "nao");
 
    free(c1);
    free(c2);
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
    static const int ciclo5[][2] = {{0,1},{1,2},{2,3},{3,4},{4,0}};
    static const int k4[][2] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
    static const int k33[][2] = {
        {0,3},{0,4},{0,5},{1,3},{1,4},{1,5},{2,3},{2,4},{2,5}};
    static const int petersen[][2] = {
        {0,1},{1,2},{2,3},{3,4},{4,0},{0,5},{1,6},{2,7},{3,8},{4,9},
        {5,7},{7,9},{9,6},{6,8},{8,5}};
    static const int caminho[][2] = {{1,3},{3,4},{4,2}};
 
    demo("Ciclo C5", 5, 5, ciclo5);
    demo("K4", 4, 6, k4);
    demo("K3,3", 6, 9, k33);
    demo("Petersen", 10, 15, petersen);
    demo("Caminho 1-3-4-2 (0 e 5 isolados)", 6, 3, caminho);
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
 



