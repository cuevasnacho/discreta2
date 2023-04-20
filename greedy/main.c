#include <stdio.h>
#include "APIParte2.h"

int main(void) {
    Grafo g = ConstruirGrafo();
    u32* Color = calloc(NumeroDeVertices(g), sizeof(u32));
    u32* Orden = calloc(NumeroDeVertices(g), sizeof(u32));
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        Orden[i]=i;
    }

    u32 colores = Greedy(g,Orden,Color);

    printf("%u\n",colores);

    return 0;
}