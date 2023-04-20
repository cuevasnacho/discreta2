#include <stdbool.h>
#include "APIParte2.h"

inline static u32 max(u32 x, u32 y) {
    return (x>y)?x:y;
}

u32 Greedy(Grafo G,u32* Orden,u32* Color) {
    u32 V = NumeroDeVertices(G);
    u32 max_color = 1;
    bool* coloured = calloc(V, sizeof(bool));   // dice si el i-esimo nodo esta coloreado
    bool* num_set = calloc(V, sizeof(bool));    // dice si el i-esimo color esta usado

    Color[Orden[0]] = 0;
    coloured[Orden[0]] = true;

    for (u32 i = 1; i < V; ++i) {
        u32 min_number = 0, max_vec = 0;
        {                                       // busca el minimo color para Orden[i]
            for (u32 j = 0; j < Grado(i,G); j++) {
                if (coloured[IndiceVecino(j,i,G)]) {
                    num_set[Color[IndiceVecino(j,i,G)]] = true;
                    max_vec = max(max_vec, Color[IndiceVecino(j,i,G)]);
                }
            }
            while (num_set[min_number]) {
                min_number++;
            }
        }
        Color[Orden[i]] = min_number;
        coloured[Orden[i]] = true;
        max_color = max(max_color, max_vec+1);

        for (u32 j = 0; j < max_vec; ++j)
            num_set[j] = false;
    }

    free(coloured);
    coloured = NULL;
    free(num_set);
    num_set = NULL;

    return max_color;
}

u32 Greedy(Grafo G,u32* Orden,u32* Color);

char OrdenImparPar(u32 n,u32* Orden,u32* Color);

char OrdenJedi(Grafo G,u32* Orden,u32* Color);
