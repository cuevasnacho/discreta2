#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    //printf("delta %u\n",Delta(g));
    //printf("numero de lados %u\n",NumeroDeLados(g));
    //printf("numero de vertices %u\n",NumeroDeVertices(g));
    //for (int i = 0; i < 6; i++){
    //    printf("Lado %u, grado %u \n",Nombre(i,g),Grado(i,g));
    //}
    DestruirGrafo(g);
    return 0;
}