#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack {
    int size;
    struct TreeNode *array[100];
};

bool isEmpty(struct Stack *s)
{
    return !s->size;
}

void push(struct Stack *s, struct TreeNode *k)
{
    s->array[s->size++] = k;
}

struct TreeNode *pop(struct Stack *s)
{
    if (!isEmpty(s))
        return s->array[--s->size];
    else
        return NULL;
}

void leafSequence(struct TreeNode *root, struct Stack *s)
{
    if (!(root->left) && !(root->right))
        push(s, root);
    else {
        if (root->left) leafSequence(root->left, s);
        if (root->right)    leafSequence(root->right, s);
    }
}

bool leafSimilar(struct TreeNode *root1, struct TreeNode *root2)
{
    struct Stack *s1, *s2;
    bool res = true;
    if (!(s1 = (struct Stack *)malloc(sizeof(struct Stack))) || !(s2 = (struct Stack *)malloc(sizeof(struct Stack))))
        return NULL;
    s1->size = s2->size = 0;
    leafSequence(root1, s1);
    leafSequence(root2, s2);
    if (s1->size == s2->size) {
        while (!isEmpty(s1) && !isEmpty(s2))
            if (pop(s1)->val != pop(s2)->val) {
                res = false;
                break;
            }
    }
    else
        res = false;
    free(s1);
    free(s2);
    return res;
}

int main()
{
    struct TreeNode node16 = {8, NULL, NULL}, node15 = {9, NULL, NULL}, node14 = {2, &node15, &node16}, node13 = {4, NULL, NULL}, node12 = {7, NULL, NULL}, node11 = {6, NULL, NULL}, node10 = {1, &node13, &node14}, node9 = {5, &node11, &node12}, head2 = {3, &node9, &node10}, node8 = {4, NULL, NULL}, node7 = {7, NULL, NULL}, node6 = {8, NULL, NULL}, node5 = {9, NULL, NULL}, node4 = {2, &node7, &node8}, node3 = {6, NULL, NULL}, node2 = {1, &node5, &node6}, node1 = {5, &node3, &node4}, head1 = {3, &node1, &node2};
    printf("%s\n", leafSimilar(&head1, &head2) ? "true" : "false");
    return 0;
}
