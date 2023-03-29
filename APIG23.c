#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"
#include <math.h>


inline static u32 hash_func(u32 a, u32 size){
    return a%size;
}

static u32 get_index(u32 a){

}
/* Constructores */

u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;   
}
Grafo ConstruirGrafo() {

    vector con1 = vector_init();
    vector con2 = vector_init();
    vector v = vector_init();

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
    //abrir el archivo leerlo hacer binary y encontrar el primo siguiente a g-V
    u32 ht_size,i,hash,x,y;
    u32* hash_table = (u32*)calloc(ht_size,sizeof(u32));

    for(i=0; i<g->E; i++) {

        if(i!=g->E-1)
            scanf("%c %d %d\n",&c,&x,&y);
        else
            scanf("%c %d %d",&c,&x,&y);

        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        hash = hash_func(x,ht_size);
        
        if (!hash_table[hash])
            hash_table[hash] = x;
        
        else if (hash_table[hash] == x)
            continue;

        else
            vector_pushback(v,x);
        
        hash = hash_func(y,ht_size);
        if (!hash_table[hash])
            hash_table[hash] = y;

        else if (hash_table[hash] == y)
            continue;

        else
            vector_pushback(v,y);
    }

    for (i = 0; i < vector_size(v); i++){
        u32 vi = vector_i(v,i);
        hash = hash_func(vi+1,ht_size);
        while(!hash_table[hash] && hash_table[hash] != hash)
            i = hash_func(i+1,ht_size);

        if (!hash_table[hash])
            hash_table[hash] = vi;

    }
    //rearmar conexiones
    for (i = 0; i < g->E; i++){
        x = hash_func(vector_i(con1,i),ht_size);
        y = hash_func(vector_i(con2,i),ht_size);
    }


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
    //completar
}
u32 Grado(u32 i,Grafo G){
    return vector_size(G->vertex[i]);
}
u32 IndiceVecino(u32 j,u32 i,Grafo G){
    if (i < MAX_RANGE && j < vector_size(G->vertex[i]))
        return vector_i(G->vertex[i],j);
    else
        return MAX_RANGE;
}