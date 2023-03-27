#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    DestruirGrafo(g);

    return 0;
}