#ifndef RBT_H
#define RBT_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef struct node* set;

// Initialize set
set set_init();

// Utility function to insert newly node in RedBlack tree
void set_insert(set *root, u32 data);

// Utility function to check if a node belongs to a tree
bool set_belong(set *root, u32 num);

#endif