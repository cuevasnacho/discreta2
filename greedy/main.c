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
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        printf("%u ",Color[i]);
    }
    printf("\n");
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        printf("%u ",Orden[i]);
    }
    printf("\n");
    char c = OrdenImparPar(NumeroDeVertices(g),Orden,Color);
    colores = Greedy(g,Orden,Color);
    printf("%u\n",colores);
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        printf("%u ",Color[i]);
    }
    printf("\n");
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        printf("%u ",Orden[i]);
    }
    printf("\n");

    DestruirGrafo(g);
    free(Color);
    Color = NULL;
    free(Orden);
    Orden = NULL;

    return 0;
}