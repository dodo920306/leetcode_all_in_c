#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSameTree(struct TreeNode *p, struct TreeNode *q);

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if (!p && !q)   return true;
    if (!p || !q)   return false;

    return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main()
{
    struct TreeNode *p = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *q = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *leftp = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *leftq = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *rightp = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *rightq = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (!p || !q || !leftp || !rightp || !leftq || !rightq)   return -1;

    leftp->val = leftq->val = 2;
    leftp->left = NULL;
    leftp->right = NULL;

    leftq->left = NULL;
    leftq->right = NULL;

    rightp->val = rightq->val = 3;
    rightp->left = NULL;
    rightp->right = NULL;

    rightq->left = NULL;
    rightq->right = NULL;

    p->val = q->val = 1;
    p->left = leftp;
    p->right = rightp;

    q->left = leftq;
    q->right = rightq;

    printf("%s", isSameTree(p, q) ? "true" : "false");

    free(p);
    free(q);
    free(leftp);
    free(leftq);
    free(rightp);
    free(rightq);
    return 0;
}
