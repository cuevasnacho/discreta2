#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef unsigned int u32;

typedef struct node {
    u32 value;
    struct node *left;
    struct node *right;
    struct node *parent;
    u32 color; // 0 for black, 1 for red
} node;

node* create_node(u32 value) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = 1; // new nodes are always red
    return new_node;
}

void rotate_left(node **root, node *x) {
    node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rotate_right(node **root, node *y) {
    node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } 
    else if (y == y->parent->left) {
        y->parent->left = x;
    } 
    else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void fix_violation(node **root, node *z) {
    while (z != *root && z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            node *y = z->parent->parent->right;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotate_right(root, z->parent->parent);
            }
        } 
        else {
            node *y = z->parent->parent->left;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 0;
}

void insert(node **root, u32 value) {
    node *new_node = create_node(value);
    node *x = *root;
    node *y = NULL;
    while (x != NULL) {
        y = x;
        if (new_node->value < x->value) {
            x = x->left;
        } 
        else {
            x = x->right;
        }
    }
    new_node->parent = y;
    if (y == NULL) {
        *root = new_node;
    } 
    else if (new_node->value < y->value) {
        y->left = new_node;
    } 
    else {
        y->right = new_node;
    }
    fix_violation(root, new_node);
}

bool belong(node *root, u32 value) {
    while (root != NULL) {
        if (value == root->value) {
            return true;
        } else if (value < root->value) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return false;
}
void destroy_tree(node *root) {
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}

/*
u32 main() {
    node *root = NULL;
    insert(&root, 7);
    insert(&root, 6);
    insert(&root, 5);
    insert(&root, 4);
    insert(&root, 3);
    insert(&root, 2);
    insert(&root, 1);
    printf("Inorder traversal of the red-black tree: ");
    //inorder_traversal(root);
    printf("El elemento %d\n",belong(root,7));
    printf("EL elemento 1222 %d\n",belong(root,1222));
    return 0;
}
*/