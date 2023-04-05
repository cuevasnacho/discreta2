#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    printf("delta %u\n",Delta(g));
    printf("numero de lados %u\n",NumeroDeLados(g));
    printf("numero de vertices %u\n",NumeroDeVertices(g));
    DestruirGrafo(g);
    return 0;
}