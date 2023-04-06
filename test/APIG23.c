#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"
#include "rbt.c"

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
    vector* find_index = (vector*)calloc(g->V, sizeof(vector));
    u32* next_free = (u32*)calloc(g->V, sizeof(u32));
    bool* init_fi = (bool*)calloc(g->V, sizeof(bool));
    /* Pedir los lados y ubicar los primeros vertices */
    node *root = NULL;
    for(i=0; i<g->E; i++) {
        if (!scanf("%c %d %d\n",&c,&x,&y))
            printf("Error leyendo los valores");
        
        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        hash = hash_func(x,v_size);
        if (!g->name[hash]){
            g->name[hash] = x;
            next_free[hash] = hash;
        }
        else if (g->name[hash] != x){
            if (!belong(root,x)){
                vector_pushback(v,x);
                insert(root,x);
            }
            
            if (!init_fi[hash]){
                find_index[hash] = vector_init(1);
                init_fi[hash] = true;
            }
        }
        
        hash = hash_func(y,v_size);
        if (!g->name[hash]){
            g->name[hash] = y;
            next_free[hash] = hash;
        }
        else if (g->name[hash] != y){
            if (!belong(root,x)){
                vector_pushback(v,y);
                insert(root,x);
            }
            if (!init_fi[hash]){
                find_index[hash] = vector_init(1);
                init_fi[hash] = true;
            }
        }
    }
    
    /* Encontrar un lugar para las coliciones */
    for (u32 i = 0,h; i < vector_size(v); i++){
        u32 vi = vector_i(v,i);
        hash = hash_func(vi,v_size);
        h = next_free[hash];
        while(g->name[h])
            h = hash_func(h+1,v_size);
        next_free[hash] = h;
        g->name[h] = vi;
        vector_pushback(find_index[hash],h);    
    }
    vector_destroy(v);
    
    /* Armar conexiones con el nuevo mapeo */
    double coneccion_qty = ceil((0.0001*g->E)/100);
    for (u32 i = 0,k,n,bound; i < g->E; i++) {
        x = hash_func(vector_i(con1,i),v_size);
        
        if (g->name[x] != vector_i(con1,i)){
            n = vector_size(find_index[x]);
            bound = (n % 2 == 0) ? n/2 : (n+1)/2;
            for (k = 0; k < bound; k++){
                if (g->name[vector_i(find_index[x],k)] == vector_i(con1,i)){
                    x = vector_i(find_index[x],k);
                    break;
                }
                if (g->name[vector_i(find_index[x],(n-k-1))] == vector_i(con1,(n-k-1))){
                    x = vector_i(find_index[x],(n-k-1));
                    break;
                }
            }
        }

        if (!g->init[x]){
            g->vertex[x] = vector_init((u32)coneccion_qty);
            g->init[x] = true;
        }

        y = hash_func(vector_i(con2,i),v_size);

        if (g->name[y] != vector_i(con2,i)){
            n = vector_size(find_index[y]);
            bound = (n % 2 == 0) ? n/2 : (n+1)/2;
            for (k = 0; k < bound; k++){
                if (g->name[vector_i(find_index[y],k)] == vector_i(con2,i)){
                    y = vector_i(find_index[y],k);
                    break;
                }
                if (g->name[vector_i(find_index[y],(n-k-1))] == vector_i(con2,(n-k-1))){
                    y = vector_i(find_index[y],(n-k-1));
                    break;
                }
            }
        }

        if (!g->init[y]){
            g->vertex[y] = vector_init((u32)coneccion_qty);
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
        
        if (init_fi[i])
            vector_destroy(find_index[i]);        
    }
    destroy_tree(root);
    free(next_free);
    free(find_index);
    free(init_fi);
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