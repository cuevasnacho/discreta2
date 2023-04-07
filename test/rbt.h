#ifndef RBT_H
#define RBT_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "APIG23.h"

typedef unsigned int u32;

typedef struct set_r {
    struct node* root;
    u32 size;
} set_r;

typedef struct set_r* set;

// Initialize set
set set_init();

// Utility function to insert newly node in RedBlack tree
void set_insert(set s, u32 data);

// Utility function to check if a node belongs to a tree
bool set_belong(set s, u32 num);

// Utility function to check the size of a tree
u32 set_size(set s);

void inorder(struct node* root, Grafo g, u32* next_free,
             vector* find_index);

#endif