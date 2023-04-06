#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
    int color; // 0 for black, 1 for red
} node;

node* create_node(int value) {
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
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
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
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotate_right(root, z->parent->parent);
            }
        } else {
            node *y = z->parent->parent->left;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
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

void insert(node **root, int value) {
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

void inorder_traversal(node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->value);
        inorder_traversal(root->right);
    }
}