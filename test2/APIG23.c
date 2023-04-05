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

int comp(const void* num1, const void* num2) {  
    return *(int*)num1 - *(int*)num2;
} 

/* Constructores */
Grafo ConstruirGrafo() {
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
    
    vector con1 = vector_init(g->E);
    vector con2 = vector_init(g->E);
    u32* v = calloc(2*g->E,sizeof(u32));

    /* Pedir los lados y ubicar los primeros vertices */
    for(u32 i=0,x,y; i<g->E; i++) {
        if (!scanf("%c %d %d\n",&c,&x,&y))
            printf("Error leyendo los valores");
        vector_pushback(con1,x);
        vector_pushback(con2,y);
        v[2*i]=x; v[2*i+1]=y;
    }

    /* Ordeno el v y seteo un indice */
    qsort(v,2*g->E,sizeof(u32),comp);
    g->name[0] = v[0];
    for (u32 i=1, j=1, e=v[0]; i<2*g->E; ++i) {
        if (v[i]!=e) {
            g->name[j] = v[i];
            e = v[i];
            ++j;
        }
    }
    
    free(v);
    v = NULL;

    /* Armar conexiones */
    for (u32 i=0,p,q,b,e,x; i<g->E; ++i) {
        p = vector_i(con1,i);
        b = 0; e = g->V-1;
        x = (e+b)/2;
        while (g->name[x]!=p) {
            if(g->name[x]>p) {
                e = x;
            } else {
                b = x;
            }
            x = (e+b)/2;
            if (e-b==1 && g->name[x]!=p)
                ++x;
        }

        q = vector_i(con2,i);
        b = 0; e = g->V-1;
        x = (e+b)/2;
        while (g->name[x]!=q) {
            if(g->name[x]>q) {
                e = x;
            } else {
                b = x;
            }
            x = (e+b)/2;
            if (e-b==1 && g->name[x]!=q)
                ++x;
        }

        if (!g->init[p]) {
            g->vertex[p] = vector_init(1);
            g->init[p] = true;
        }
        vector_pushback(g->vertex[p],q);

        if (!g->init[q]) {
            g->vertex[q] = vector_init(1);
            g->init[q] = true;
        }
        vector_pushback(g->vertex[q],p);
    }
    
    vector_destroy(con1);
    vector_destroy(con2);

    /* Calcular el delta del grafo */
    for (u32 i=0; i<g->V; ++i) {
        if(g->init[i])
            g->degree = max(g->degree,vector_size(g->vertex[i]));
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