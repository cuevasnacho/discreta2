#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"
#include <math.h>


inline static u32 hash_func(u32 a, u32 size){
    return a%size;
}

/* Constructores */

u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;   
}
Grafo ConstruirGrafo() {
    u32 j,fixing,ht_size,i,hash,x,y;
    char c;
    Grafo g = (Grafo)malloc(sizeof(GrafoSt));
    if (g == NULL)
        printf("Eror pidiendo memoria \n");
    g->init_name = false;
    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        }
        else if (c == 'p') {
            char word[5];
            scanf("%4s %d %d\n",word,&g->V,&g->E);
            g->init = (bool*)calloc(g->V+1, sizeof(bool));
            g->vertex = (vector*)calloc(g->V+1, sizeof(vector));
            if (g->init == NULL || g->vertex == NULL)
                printf("Error pidiendo memoria \n");
            g->degree = 0;
            break;
        }
        else 
            return NULL;
    }
    
    ht_size = g->V+1;
    vector con1 = vector_init(g->V+1);
    vector con2 = vector_init(g->V+1);
    vector v = vector_init(g->V);
    g->hash_table = (u32*)calloc(ht_size,sizeof(u32));
    g->fix_index = (u32*)calloc(ht_size,sizeof(u32));
    if (g->hash_table == NULL || g->fix_index == NULL)
        printf("Error pidiendo memoria \n");

    for(i=0; i<g->E; i++) {

        if(i!=g->E-1)
            scanf("%c %d %d\n",&c,&x,&y);
        else
            scanf("%c %d %d",&c,&x,&y);

        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        hash = hash_func(x,ht_size);
        if (!g->hash_table[hash])
            g->hash_table[hash] = x;
        else if (g->hash_table[hash] == x)
            continue;
        else
            vector_pushback(v,x);
        
        hash = hash_func(y,ht_size);
        if (!g->hash_table[hash])
            g->hash_table[hash] = y;
        else if (g->hash_table[hash] == y)
            continue;
        else
            vector_pushback(v,y);
    }
    printf("Cantidad de coliciones: %d\n",vector_size(v));
    /* Encontrar un lugar para las coliciones */
    for (i = 0; i < vector_size(v); i++){
        u32 vi = vector_i(v,i);
        hash = hash_func(vi+1,ht_size);
        while(g->hash_table[hash] && g->hash_table[hash] != vi)
            hash = hash_func(hash+1,ht_size);

        if (!g->hash_table[hash])
            g->hash_table[hash] = vi;
    }
    printf("Acomodo indice \n");

    vector_destroy(v);
    printf("Reaarmo connecciones \n");
    /* armar conexiones con el nuevo mapeo */
    double coneccion_qty = ceil((0.1*g->E)/100);
    for (i = 0; i < (g->E); i++){
        x = hash_func(vector_i(con1,i),ht_size);
        y = hash_func(vector_i(con2,i),ht_size);
     
        //lo tiene que buscar                 
        while(g->hash_table[x] != vector_i(con1,i)){
            x = hash_func(x+1,ht_size);
        }
                     
        while(g->hash_table[y] != vector_i(con2,i)){
            y = hash_func(y+1,ht_size);
        }
    
        if (!g->init[x]){
            g->vertex[x] = vector_init((int)coneccion_qty);
            g->init[x] = true;
        }
            
        if (!g->init[y]){
            g->vertex[y] = vector_init((int)coneccion_qty);
            g->init[y] = true;
        }
        vector_pushback(g->vertex[x],y);
        vector_pushback(g->vertex[y],x);
        g->degree = max(max(g->degree,vector_size(g->vertex[x])),vector_size(g->vertex[y]));
    }

    /* Muestra conecciones */ 
    /*
    for (i = 0; i <= g->V; i++){
        if (g->init[i]){
            printf("%d :",i);
            for (j = 0; j < vector_size(g->vertex[i]); j++){        
                printf("%d ",vector_i(g->vertex[i],j));
            }
            printf("\n");
        }
    }
    */
    printf("Destruyo \n");
    //falta hacer los frees
    vector_destroy(con1);
    vector_destroy(con2);
    return g;
}

void DestruirGrafo(Grafo G) {
    for(u32 i=0; i<G->V; ++i) {
        if(G->init[i])
            vector_destroy(G->vertex[i]);
    }
    free(G->hash_table);
    G->hash_table = NULL;
    free(G->fix_index);
    G->fix_index = NULL;
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
    /* Acomoda los indices */
    if (!G->init_name){
        u32 fixing,ht_size,j,k;
        ht_size = G->V+1;
        k = 0;
        fixing = 0;
        while(k < ht_size && fixing < ht_size){
            if (!G->hash_table[k]){
                j = k;
                while(!G->hash_table[j]){
                    j = (j+1) % ht_size;
                }
                G->fix_index[fixing] = j;
                k = (j+1) % ht_size;
            }
            else{
                G->fix_index[fixing] = k;
                k = (k+1) % ht_size;
            }       
            fixing++;
        }
        G->init_name = true;
    }    
    //ahora si quiero obtener el nodo i en el orden natural tengo que hacer
    //hash_table[fix_index[i]]
    G->hash_table[G->fix_index[i]];
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