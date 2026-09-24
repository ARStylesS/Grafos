#include <string.h>
#include "planaridade.h"
 
#define MAX 10
 
static int mat[MAX][MAX];
static int usado[MAX];
static int ramo[MAX];
static int pares[15][2];
static int npares;
static int N;
 
int eh_planar_euler(GrafoLista *g) {
    if (g->n < 3) return 1;
    return g->m <= 3 * g->n - 6;
}
 
static int achar_caminhos(int idx);
 
static int caminho(int atual, int destino, int idx) {
    if (mat[atual][destino] && achar_caminhos(idx + 1)) return 1;
 
    for (int w = 0; w < N; w++) {
        if (mat[atual][w] && !usado[w] && !ramo[w]) {
            usado[w] = 1;
            if (caminho(w, destino, idx)) return 1;
            usado[w] = 0;
        }
    }
    return 0;
}
 
static int achar_caminhos(int idx) {
    if (idx == npares) return 1;
    return caminho(pares[idx][0], pares[idx][1], idx);
}
 
static int testar(int *v, int k) {
    memset(usado, 0, sizeof(usado));
    memset(ramo, 0, sizeof(ramo));
    for (int i = 0; i < k; i++) ramo[v[i]] = 1;
    return achar_caminhos(0);
}
 
static int tem_k5(void) {
    for (int mask = 0; mask < (1 << N); mask++) {
        if (__builtin_popcount(mask) != 5) continue;
 
        int v[5], k = 0;
        for (int i = 0; i < N; i++)
            if (mask & (1 << i)) v[k++] = i;
 
        npares = 0;
        for (int i = 0; i < 5; i++)
            for (int j = i + 1; j < 5; j++) {
                pares[npares][0] = v[i];
                pares[npares][1] = v[j];
                npares++;
            }
        if (testar(v, 5)) return 1;
    }
    return 0;
}
 
static int tem_k33(void) {
    for (int mask = 0; mask < (1 << N); mask++) {
        if (__builtin_popcount(mask) != 6) continue;
 
        int v[6], k = 0;
        for (int i = 0; i < N; i++)
            if (mask & (1 << i)) v[k++] = i;
 
        for (int sub = 0; sub < 64; sub++) {
            if (__builtin_popcount(sub) != 3) continue;
 
            int a[3], b[3], ia = 0, ib = 0;
            for (int i = 0; i < 6; i++) {
                if (sub & (1 << i)) a[ia++] = v[i];
                else b[ib++] = v[i];
            }
 
            npares = 0;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    pares[npares][0] = a[i];
                    pares[npares][1] = b[j];
                    npares++;
                }
            if (testar(v, 6)) return 1;
        }
    }
    return 0;
}
 
int tem_subdivisao_k5_k33(GrafoLista *g) {
    N = g->n;
    memset(mat, 0, sizeof(mat));
    for (int u = 0; u < N; u++)
        for (No *p = g->adj[u]; p; p = p->prox)
            mat[u][p->v] = 1;
 
    return tem_k5() || tem_k33();
}
 
int eh_planar(GrafoLista *g) {
    if (!eh_planar_euler(g)) return 0;
    if (g->n <= MAX) return !tem_subdivisao_k5_k33(g);
    return -1;
}
 