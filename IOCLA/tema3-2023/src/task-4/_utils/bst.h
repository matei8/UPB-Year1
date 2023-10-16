#ifndef BST_H

#define BST_H
#define LEN 1000

struct node {
    int value;
    struct node *left;
    struct node *right;
} __attribute__((packed));

struct BST {
    struct node *root;
    int size;
} __attribute__((packed));

void insert_node(struct node *root, struct node *new_node);

void add_node(struct BST *tree, int value);

void do_some_mess(struct node *root, struct node *parent, int hash);

void free_tree(struct node *tree);

#endif
