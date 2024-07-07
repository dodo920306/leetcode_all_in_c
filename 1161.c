#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
int maxLevelSum(struct TreeNode *root);

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
    if (k)  q->array[q->end++] = k;
}

struct TreeNode *pop(struct Queue *q)
{
    return isEmpty(q) ? NULL : q->array[q->start++];
}

void qFree(struct Queue *q)
{
    free(q->array);
    free(q);
}

int maxLevelSum(struct TreeNode *root)
{
    struct Queue *q;
    struct TreeNode *node;
    int res = 1;
    if (!(q = create(10000)))
        return -1;
    push(q, root);
    for (int level = 1, maxSum = INT_MIN, sum; !isEmpty(q); level++) {
        sum = 0;
        for (int i = 0, loop = size(q); i < loop; i++) {
            node = pop(q);
            sum += node->val;
            push(q, node->left);
            push(q, node->right);
        }
        if (maxSum < sum) {
            maxSum = sum;
            res = level;
        }
    }
    qFree(q);
    return res;
}

int main()
{
    struct TreeNode node4 = {-8, NULL, NULL}, node3 = {7, NULL, NULL}, node2 = {0, NULL, NULL}, node1 = {7, &node3, &node4}, head = {1, &node1, &node2};
    printf("%d\n", maxLevelSum(&head));
    return 0;
}
