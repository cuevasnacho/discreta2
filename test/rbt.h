#ifndef RBT_H
#define RBT_h

#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u32;

//A Red-Black tree node structure
typedef struct node {
    u32 data;
    char color;
    struct node *left, *right, *parent;
} node;

// Left Rotation
void LeftRotate(struct node **root,struct node *x);

// Right Rotation (Similar to LeftRotate)
void rightRotate(struct node **root,struct node *y);

// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct node **root,struct node *z);

// Utility function to insert newly node in RedBlack tree
void insert(struct node **root, u32 data);

bool belong(struct node **root, u32 num);

#endif