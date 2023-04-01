#ifndef ESTRUC_GRAF_H
#define ESTRUC_GRAF_H

#include <stdbool.h>
#include "vector.h"

typedef unsigned int u32;

typedef struct GrafoSt {
    vector* vertex;
    bool* init;
    u32 V;
    u32 E;
    u32 degree;
    u32* hash_table;
    u32* fix_index;
    u32 init_name;
} GrafoSt;

#endif