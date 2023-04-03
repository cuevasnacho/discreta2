#include <stdlib.h>
#include <math.h>
#include "APIG23.h"
#include "vector.h"


inline static u32 hash_func(u32 a, u32 size){
    return a%size;
}

/* Constructores */

static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;   
}
Grafo ConstruirGrafo() {
    u32 v_size,i,hash,x,y;
    char c;
    Grafo g = (Grafo)malloc(sizeof(GrafoSt));
    if (g == NULL)
        printf("Eror pidiendo memoria \n");
    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        }
        else if (c == 'p') {
            char word[5];
            scanf("%4s %d %d\n",word,&g->V,&g->E);
            g->vertex = (vector*)calloc(g->V, sizeof(vector));
            g->name = (u32*)calloc(g->V, sizeof(u32));
            g->init = (bool*)calloc(g->V, sizeof(bool));
            if (g->vertex == NULL || g->name == NULL)
                printf("Error pidiendo memoria \n");
            g->degree = 0;
            break;
        }
        else 
            return NULL;
    }
    
    v_size = g->V;
    vector con1 = vector_init(g->E);
    vector con2 = vector_init(g->E);
    vector v = vector_init(v_size);

    for(i=0; i<g->E; i++) {
        scanf("%c %d %d\n",&c,&x,&y);
        
        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        hash = hash_func(x,v_size);
        if (!g->name[hash])
            g->name[hash] = x;
        else if (g->name[hash] != x)
            vector_pushback(v,x);
        
        hash = hash_func(y,v_size);
        if (!g->name[hash])
            g->name[hash] = x;
        else if (g->name[hash] != y)
            vector_pushback(v,y);
    }
    
    /* Encontrar un lugar para las coliciones */
    printf("Cantidad de coliciones: %d\n",vector_size(v));
    for (i = 0; i < vector_size(v); i++){
        u32 vi = vector_i(v,i);
        hash = hash_func(vi+1,v_size);

        while(g->name[hash])
            hash = hash_func(hash+1,v_size);
        g->name[hash] = vi;
    }
    
    vector_destroy(v);

    /* armar conexiones con el nuevo mapeo */
    //double coneccion_qty = ceil((0.0001*g->E)/100);
    printf("Reaarmo conexiones \n");
    for (i = 0; i < g->E; i++) {
        x = hash_func(vector_i(con1,i),v_size);
        while(g->name[x] != vector_i(con1,i))
            x = hash_func(x+1,v_size);

        if (!g->init[x]){
            g->vertex[x] = vector_init(1);
            g->init[x] = true;
        }
        
        y = hash_func(vector_i(con2,i),v_size);
        while(g->name[y] != vector_i(con2,i))
            y = hash_func(y+1,v_size);

        if (!g->init[y]){
            g->vertex[y] = vector_init(1);
            g->init[y] = true;
        }
            
        vector_pushback(g->vertex[x],y);
        vector_pushback(g->vertex[y],x);
        g->name[x] = vector_i(con1,i);
        g->name[y] = vector_i(con2,i);
    }

    for (i=0; i<g->V; ++i) {
        if(g->init[i])
            g->degree = max(g->degree,vector_size(g->vertex[i]));
    }

    printf("Destruyo \n");
    vector_destroy(con1);
    vector_destroy(con2);

    return g;
}

void DestruirGrafo(Grafo G) {
    for(u32 i=0; i<G->V+1; ++i) {
        if(!G->init[i])
            vector_destroy(G->vertex[i]);
    }
    free(G->vertex);
    G->vertex = NULL;
    free(G->name);
    G->name = NULL;
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
    return G->name[i];
}
u32 Grado(u32 i,Grafo G){
    if(G->init[i])
        return vector_size(G->vertex[i]);
    return 0;
}
u32 IndiceVecino(u32 j,u32 i,Grafo G){
    if (i < MAX_RANGE && j < vector_size(G->vertex[i]))
        return vector_i(G->vertex[i],j);
    else
        return MAX_RANGE;
}