#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    //printf("%u",Delta(g));
    DestruirGrafo(g);
    return 0;
}