#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Queue {
    int start;
    int end;
    struct TreeNode *array[10000];
};

int size(struct Queue *q);
bool isEmpty(struct Queue *q);
void push(struct Queue *q, struct TreeNode *k);
void pop(struct Queue *q);
struct TreeNode *peek(struct Queue *q);

int size(struct Queue *q)
{
    return q->end - q->start;
}

bool isEmpty(struct Queue *q)
{
    return !size(q);
}

void push(struct Queue *q, struct TreeNode *k)
{
    q->array[q->end++] = k;
}

void pop(struct Queue *q)
{
    if (!isEmpty(q))    q->start++;
}

struct TreeNode *peek(struct Queue *q)
{
    return q->array[q->start];
}

int maxDepth(struct TreeNode *root)
{
    struct Queue *q;
    struct TreeNode *n;
    int qSize, res = 0;
    if (root) {
        if (!(q = (struct Queue *)malloc(sizeof(struct Queue))))
            return -1;
        q->start = q->end = 0;
        push(q, root);
        while (!isEmpty(q)) {
            res++;
            qSize = size(q);
            for (int i = 0; i < qSize; i++) {
                n = peek(q);
                if (n->left)    push(q, n->left);
                if (n->right)   push(q, n->right);
                pop(q);
            }
        }
        free(q);
    }
    return res;
}

int main()
{
    struct TreeNode node4 = {7, NULL, NULL}, node3 = {15, NULL, NULL}, node2 = {20, &node3, &node4}, node1 = {9, NULL, NULL}, head = {3, &node1, &node2};
    printf("%d\n", maxDepth(&head));
    return 0;
}
