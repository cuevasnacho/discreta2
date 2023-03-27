#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"

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
            g->init = (bool*)calloc(sizeof(g->V), sizeof(bool));
            g->vertex = (vector*)calloc(g->V, sizeof(vector));
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

        if(!g->init[x])
            g->vertex[x] = vector_init();
        if(!g->init[y])
            g->vertex[y] = vector_init();

        vector_pushback(g->vertex[x], y);
        vector_pushback(g->vertex[y], x);
    }

    for(u32 i=0; i<g->V; ++i) {
        printf("%u ", i);
        for(u32 j=0; j<vector_size(g->vertex[i]); ++j) {
            printf("%u ",vector_i(g->vertex[i],j));
        }
        printf("\n");
    }

    return g;
}