#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max(int a, int b);
int depth(struct TreeNode *root, int *res);
int diameterOfBinaryTree(struct TreeNode *root);

int max(int a, int b)
{
    return a > b ? a : b;
}

int depth(struct TreeNode *root, int *res)
{
    if (!root)  return 0;
    int left = depth(root->left, res), right = depth(root->right, res);
    if (left + right > *res) *res = left + right;
    return 1 + (left > right ? left : right);
}

int diameterOfBinaryTree(struct TreeNode *root)
{
    int res = 0;
    depth(root, &res);
    return res;
}

int main()
{
    struct TreeNode *node1 = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *node2 = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *node3 = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *node4 = (struct TreeNode *)malloc(sizeof(struct TreeNode)), *node5 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (!node1 || !node2 || !node3 || !node4 || !node5) {
        perror("Error");
        return -1;
    }

    node1->val = 1;
    node2->val = 2;
    node3->val = 3;
    node4->val = 4;
    node5->val = 5;

    node1->left = node2;
    node2->left = node4;
    node1->right = node3;
    node2->right = node5;
    node3->left = NULL;
    node4->left = NULL;
    node5->left = NULL;
    node3->right = NULL;
    node4->right = NULL;
    node5->right = NULL;

    printf("%d", diameterOfBinaryTree(node1));

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    return 0;
}
