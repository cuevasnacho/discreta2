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
            for (u32 j = 0; j < Grado(Orden[i],G); j++) {
                if (coloured[IndiceVecino(j,Orden[i],G)]) {
                    num_set[Color[IndiceVecino(j,Orden[i],G)]] = true;
                    max_vec = max(max_vec, Color[IndiceVecino(j,Orden[i],G)]);
                }
            }
            while (num_set[min_number]) {
                min_number++;
            }
            max_color = max(max_color, min_number);
        }
        Color[Orden[i]] = min_number;
        coloured[Orden[i]] = true;

        for (u32 j = 0; j <= max_vec; ++j)
            num_set[j] = false;
    }

    free(coloured);
    coloured = NULL;
    free(num_set);
    num_set = NULL;

    return max_color+1;
}

/*
Esta funcion asume que Orden y Color apuntan a un sector de memoria con al menos n lugares. Tambien asume que la
imagen de Color[] es un conjunto {0, 1, ..., r − 1} para algun r.
Ordena indices llenando el array Orden poniendo primero los indices i tal que Color[i] sea igual al mayor impar en
{0, 1, ..., r − 1}, luego los indices i tal que Color[i] es igual el segundo mayor impar, etc hasta terminar con los impares. Luego
pone los indices i tal que Color[i] es el mayor par, luego el segundo mayor par, etc.
Observacion: Aca no es necesaria la estructura de G, solo n.
Si todo anduvo bien devuelve el char 0, si no el char 1. (razones por la que podria andar mal es que hagan un alloc de
memoria auxiliar y el mismo falle)
*/
char OrdenImparPar(u32 n,u32* Orden,u32* Color) {
    u32 mayorImpar = (n%2) ? n : n-1;
    u32 j = 0;
    for (u32 i = 0; i < n; ++i) {
        
    }
}

char OrdenJedi(Grafo G,u32* Orden,u32* Color) {
    
}
