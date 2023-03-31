#ifndef VECTOR_H
#define VECTOR_H

typedef unsigned int u32;
typedef struct vector_head *vector;

vector vector_init(u32 size);

void vector_pushback(vector v, u32 value);

u32 vector_i(vector v, u32 i);

u32 vector_size(vector v);

void vector_destroy(vector v);

#endif