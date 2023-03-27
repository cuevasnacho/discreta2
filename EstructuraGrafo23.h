#ifndef ESTRUC_GRAF_H
#define ESTRUC_GRAF_H

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct GrafoSt {
    vector* vertex;
    bool* init;
    u32 V;
    u32 E;
    u32 degree;
} GrafoSt;

/**********CONSTRUCTORES***************/

Grafo ConstruirGrafo(void);

void DestruirGrafo(Grafo G);

/**********FUNCIONES GRAFO*************/

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeLados(Grafo G);

u32 Delta(Grafo G);

/*******FUNCIONES VERTICES*************/

u32 Nombre(u32 i,Grafo G);

u32 Grado(u32 i,Grafo G);

u32 IndiceVecino(u32 j,u32 i,Grafo G);

#endif