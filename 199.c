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
    struct TreeNode **array;
};

struct Queue *create(int size);
int size(struct Queue *q);
bool isEmpty(struct Queue *q);
void push(struct Queue *q, struct TreeNode *k);
struct TreeNode *pop(struct Queue *q);
void qFree(struct Queue *q);

struct Queue *create(int size)
{
    struct Queue *res;
    if (!(res = (struct Queue *)malloc(sizeof(struct Queue))) || !(res->array = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *))))
        return NULL;
    res->start = res->end = 0;
    return res;
}

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

struct TreeNode *pop(struct Queue *q)
{
    return q->array[q->start++];
}

void qFree(struct Queue *q)
{
    free(q->array);
    free(q);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rightSideView(struct TreeNode *root, int *returnSize) {
    struct Queue *q;
    struct TreeNode *t = NULL;
    int *res = NULL;
    *returnSize = 0;
    if (root && (q = create(128)) && (res = (int *)malloc(32 * sizeof(int)))) {
        push(q, root);
        while (!isEmpty(q)) {
            for (int i = 0, loop = size(q); i < loop; i++) {
                t = pop(q);
                if (t->left)
                    push(q, t->left);
                if (t->right)
                    push(q, t->right);
            }
            res[(*returnSize)++] = t->val;
        }
        qFree(q);
    }
    return res;
}

int main()
{
    struct TreeNode node4 = {4, NULL, NULL}, node3 = {5, NULL, NULL}, node2 = {3, NULL, &node4}, node1 = {2, NULL, &node3}, head = {1, &node1, &node2};
    int returnSize, *res = rightSideView(&head, &returnSize);
    printf("[%d", *res);
    for (int i = 1; i < returnSize; i++)
        printf(", %d", res[i]);
    printf("]\n");
    return 0;
}
