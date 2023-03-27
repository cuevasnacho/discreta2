#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"

/* Constructores */

Grafo ConstruirGrafo() {
    Grafo g = (Grafo)malloc(sizeof(GrafoSt));
    char c;

    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        }
        else if (c == 'p') {
            char word[5];
            scanf("%4s %d %d\n",word,&g->V,&g->E);
            g->init = (bool*)calloc(g->V, sizeof(bool));
            g->vertex = (vector*)calloc(g->V, sizeof(vector));
            g->degree = 0;
            break;
        }
        else 
            return NULL;
    }
    for(u32 i=0; i<g->E; i++) {
        u32 x,y;
        if(i!=g->E-1)
            scanf("%c %d %d\n",&c,&x,&y);
        else
            scanf("%c %d %d",&c,&x,&y);

        x--; y--; // para que los nodos arranquen en 0

        if(!g->init[x]) {
            g->vertex[x] = vector_init();
            g->init[x] = true;
        }
        if(!g->init[y]) {
            g->vertex[y] = vector_init();
            g->init[y] = true;
        }

        vector_pushback(g->vertex[x], y);
        vector_pushback(g->vertex[y], x);
        g->degree = max(g->degree,max(vector_size(g->vertex[y]),
                                      vector_size(g->vertex[x])));
    }

    /*
    for(u32 i=0; i<g->V; ++i) {
        printf("%u ", i);
        for(u32 j=0; j<vector_size(g->vertex[i]); ++j) {
            printf("%u ",vector_i(g->vertex[i],j));
        }
        printf("\n");
    }
    */

    return g;
}

void DestruirGrafo(Grafo G) {
    for(u32 i=0; i<G->V; ++i) {
        if(G->init[i])
            vector_destroy(G->vertex[i]);
    }
    free(G->vertex);
    G->vertex = NULL;
    free(G->init);
    G->init = NULL;
    free(G);
    G = NULL;
}

/* Grafo info */

u32 NumeroDeVertices(Grafo G) {
    return G->V;
}
u32 NumeroDeLados(Grafo G) {
    return G->E;
}
u32 Delta(Grafo G){
    return G->degree;
}

/* Vertices info*/

u32 Nombre(u32 i,Grafo G){
    
}
u32 Grado(u32 i,Grafo G);
u32 IndiceVecino(u32 j,u32 i,Grafo G);