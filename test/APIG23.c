#include <stdlib.h>
#include <math.h>
#include "APIG23.h"
#include "vector.h"

inline static u32 hash_func(u32 a, u32 size){
    return a%size;
}

inline static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;   
}

/* Constructores */
Grafo ConstruirGrafo() {
    u32 v_size,i,hash,x,y;
    char c;
    Grafo g = (Grafo)malloc(sizeof(GrafoSt));
    if (g == NULL)
        printf("Error pidiendo memoria \n");
    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        }
        else if (c == 'p') {
            char word[5];
            if (!scanf("%4s %d %d\n",word,&g->V,&g->E))
                printf("Error leyendo los valores");
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
    vector*  find_index = (vector*)calloc(g->V, sizeof(vector));
    bool* init_fi = (bool*)calloc(g->V, sizeof(bool));
    /* Pedir los lados y ubicar los primeros vertices */
    for(i=0; i<g->E; i++) {
        if (!scanf("%c %d %d\n",&c,&x,&y))
            printf("Error leyendo los valores");
        
        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        hash = hash_func(x,v_size);
        if (!g->name[hash])
            g->name[hash] = x;
        else if (g->name[hash] != x){
            vector_pushback(v,x);
            find_index[hash] = vector_init(1);
            init_fi[hash] = true;
        }
        
        hash = hash_func(y,v_size);
        if (!g->name[hash])
            g->name[hash] = y;
        else if (g->name[hash] != y){
            vector_pushback(v,y);
            find_index[hash] = vector_init(1);
            init_fi[hash] = true;
        }
    }

    /* Encontrar un lugar para las coliciones */
    for (i = 0; i < vector_size(v); i++){
        u32 vi = vector_i(v,i);
        hash = hash_func(vi+1,v_size);
        while(g->name[hash] && g->name[hash]!=vi)
            hash = hash_func(hash+1,v_size);
        g->name[hash] = vi;
        vector_pushback(find_index[vi%v_size],hash);
    }
    vector_destroy(v);
    u32 k;
    /* Armar conexiones con el nuevo mapeo */
    double coneccion_qty = ceil((0.0001*g->E)/100);
    for (i = 0; i < g->E; i++) {
        x = hash_func(vector_i(con1,i),v_size);
        
        if (g->name[x] != vector_i(con1,i)){
            for (k = 0; k < vector_size(find_index[x]); k++){
                if (g->name[vector_i(find_index[x],k)] == vector_i(con1,i)){
                    x = vector_i(find_index[x],k);
                    break;
                }
            }
        }

        if (!g->init[x]){
            g->vertex[x] = vector_init((int)coneccion_qty);
            g->init[x] = true;
        }

        y = hash_func(vector_i(con2,i),v_size);

        if (g->name[y] != vector_i(con2,i)){
            for (k = 0; k < vector_size(find_index[y]); k++){
                if (g->name[vector_i(find_index[y],k)] == vector_i(con2,i)){
                    y = vector_i(find_index[y],k);
                    break;
                }
            }
        }

        
        if (!g->init[y]){
            g->vertex[y] = vector_init((int)coneccion_qty);
            g->init[y] = true;
        }
            
        vector_pushback(g->vertex[x],y);
        vector_pushback(g->vertex[y],x);
        g->name[x] = vector_i(con1,i);
        g->name[y] = vector_i(con2,i);
    }
    vector_destroy(con1);
    vector_destroy(con2);

    /* Calcular el delta del grafo */
    for (i=0; i<g->V; ++i) {
        if(g->init[i])
            g->degree = max(g->degree,vector_size(g->vertex[i]));
        
        //if (init_fi[i])
        //    vector_destroy(finde_index[i]);
        free(find_index);
        free(init_fi);
        
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
    free(G->name);
    G->name = NULL;
    free(G->init);
    G->init = NULL;
    free(G);
    G = NULL;
}

/* Informacion del Grafo */
u32 NumeroDeVertices(Grafo G) {
    return G->V;
}

u32 NumeroDeLados(Grafo G) {
    return G->E;
}

u32 Delta(Grafo G){
    return G->degree;
}

/* Informacion de los Vertices */

u32 Nombre(u32 i,Grafo G){
    return G->name[i];
}

u32 Grado(u32 i,Grafo G){
    if(G->init[i])
        return vector_size(G->vertex[i]);
    return 0;
}

u32 IndiceVecino(u32 j,u32 i,Grafo G){
    if (i < G->V && j < vector_size(G->vertex[i]))
        return vector_i(G->vertex[i],j);
    else
        return MAX_RANGE;
}