#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#define min(a, b) ((a) < (b)) ? (a) : (b)

void insert_node(struct node *root, struct node *new_node)
{
    if (new_node->value < root->value) {
        if (!root->left) {
            root->left = new_node;
        } else {
            insert_node(root->left, new_node);
        }
    } else {
        if (!root->right) {
            root->right = new_node;
        } else {
            insert_node(root->right, new_node);
        }
    }
}

void add_node(struct BST *tree, int value)
{
    struct node* new_node = malloc(sizeof (*new_node));
    if (!new_node) {
        fprintf(stderr, "malloc() failed!\n");
        exit(-1);
    }
    new_node->left = NULL;
    new_node->value = value;
    new_node->right = NULL;

    ++tree->size;
    if (!tree->root) {
        tree->root = new_node;
    } else {
        insert_node(tree->root, new_node);
    }
}


void do_some_mess(struct node *root, struct node *parent, int hash)
{
    if (!root) {
        return;
    }

    hash += root->value;
    hash %= 541;

    if (!root->left && !root->right) {
        if ((hash & (1 << 5)) || (hash & (1 << 3))) {
            return;
        }
        if (parent->left == root) {
            root->value = parent->value + hash % parent->value;
        } else {
            root->value = parent->value - hash % parent->value;
        }
    } else {
        do_some_mess(root->left, root, hash);
        do_some_mess(root->right, root, hash);
    }
}

void free_tree(struct node *node)
{
    if (!node) {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

