#include <stdlib.h>
#include "vector.h"

typedef struct vector_head {
    u32* values;
    u32 size;
    u32 capacity;
} vector_head;

vector vector_init(void) {
    vector v = malloc(sizeof(vector_head));
    v->size = 0;
    v->capacity = 1;
    v->values = malloc(sizeof(u32)*v->capacity);
    return v;
}

void vector_pushback(vector v, u32 value) {
    if(v->size==v->capacity) {
        v->capacity *= 2;
        v->values = realloc(v->values,sizeof(u32)*(v->capacity));
    }
    v->values[v->size] = value;
    v->size++;
}

u32 vector_i(vector v, u32 i) {
    return v->values[i];
}

u32 vector_size(vector v) {
    return v->size;
}

void vector_destroy(vector v) {
    free(v->values);
    v->values=NULL;
    free(v);
    v=NULL;
}