#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct node {
    int key, value;
    struct node *parent, *left, *right;
};

struct bst {
    struct node *root;
    /* nil = All leaves of the tree. */
    struct node *nil;
};

struct node *get(struct bst *tree, int key);
void insert(struct bst *tree, int key, int value);
void delete(struct bst *tree, int key);
void inorderNodes(struct bst *tree, struct node *node);
void inorder(struct bst *tree);
struct bst *new();
void freeNodes(struct bst *tree, struct node *node);
void free_(struct bst *t);

struct node *get(struct bst *tree, int key)
{
    struct node *current = tree->root;

    while (current != tree->nil && key != current->key)
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    return current;
}

void insert(struct bst *tree, int key, int value)
{
    struct node *node = get(tree, key);
    if (node == tree->nil) {
        struct node *z = (struct node *)malloc(sizeof(struct node)), *y = tree->nil, *x = tree->root;
        if (!z) {
            perror("Error");
            return;
        }
        z->key = key;
        z->value = value;
        z->left = z->right = tree->nil;

        while (x != tree->nil) {
            /* The tree isn't empty. */
            /* Keep y as x's parent. */
            y = x;
            /* Use x to find the position for z. */
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        /* Insert z. */
        z->parent = y;
        if (y == tree->nil)
            /* Tree was empty */
            tree->root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
    else    node->value = value;
}

void delete(struct bst *tree, int key)
{
    struct node *x = get(tree, key);
    if (x != tree->nil) {
        struct node *y = NULL, *z = NULL;
        /* Make the number of y's children smaller or equals to 1. */
        if (x->left == tree->nil || x->right == tree->nil)
            /* If x has only one child, just delete x and let its child replace itself. */
            y = x;
        else{
            /* x->right != tree->nil, so y must be the leftmost of x's right subtree. */
            /* If x has two child, overwrite x with its leftmost node in its right subtree, and delete it. */
            y = x->right;
            while (y->left != tree->nil)
                y = y->left;
        }
        /* Make z y's child. */
        if (y->left != tree->nil)
            z = y->left;
        else
            /* z could be tree->nil if y has no child. */
            z = y->right;

        /* Replace y with z. */
        z->parent = y->parent;
        if (y->parent == tree->nil)
            /* y is root */
            tree->root = z;
        else if (y == y->parent->left)
            y->parent->left = z;
        else
            y->parent->right = z;

        if (y != x)
            /**
             * y = successor(x);
             * move y to x. 
             */
            x->key = y->key;

        /* Now y can be saftly removed. */
        free(y);
    }
}

void inorderNodes(struct bst *tree, struct node *node)
{
    if (node == tree->nil)   return;
    inorderNodes(tree, node->left);
    printf("%d ", node->key);
    inorderNodes(tree, node->right);
}

void inorder(struct bst *tree)
{
    inorderNodes(tree, tree->root);
    printf("\n");
}

struct bst *new()
{
    /* nil must be hold as one last node before accessing NULL, or a segfault will happen for directly accessing NULL. */
    struct node *nil = (struct node *)calloc(1, sizeof(struct node));
    struct bst *res = (struct bst *)malloc(sizeof(struct bst));
    if (!nil || !res) {
        perror("Error");
        return NULL;
    }

    res->root = nil;
    res->nil = nil;

    return res;
}

void freeNodes(struct bst *tree, struct node *node)
{
    if (node == tree->nil)  return;
    freeNodes(tree, node->left);
    freeNodes(tree, node->right);
    free(node);
}

void free_(struct bst *tree)
{
    freeNodes(tree, tree->root);
    free(tree->nil);
    free(tree);
}

int main(int argc, char* argv[])
{
    struct bst *tree = new();
    if (!tree) {
        perror("Error");
        return errno;
    }
    insert(tree, 5, 5);
    insert(tree, 8, 8);
    printf("%d\n", get(tree, 5)->value);
    inorder(tree);
    delete(tree, 5);
    inorder(tree);

    free_(tree);
    return 0;
}
