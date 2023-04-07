#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    printf("Grafo con %u vertices, %u lados, Delta %u.\n",
            NumeroDeVertices(g),NumeroDeLados(g),Delta(g));
    
    DestruirGrafo(g);
    return 0;
}