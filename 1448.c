#include <stdio.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void dfs(struct TreeNode *node, int localMaximum, int *count);
int goodNodes(struct TreeNode *root);

void dfs(struct TreeNode *node, int localMaximum, int *count)
{
    if (localMaximum <= node->val) {
        localMaximum = node->val;
        (*count)++;
    }
    if (node->left) dfs(node->left, localMaximum, count);
    if (node->right)    dfs(node->right, localMaximum, count);
}

int goodNodes(struct TreeNode *root)
{
    int res = 0;
    dfs(root, INT_MIN, &res);
    return res;
}

int main()
{
    struct TreeNode node5 = {5, NULL, NULL}, node4 = {1, NULL, NULL}, node3 = {3, NULL, NULL}, node2 = {4, &node4, &node5}, node1 = {1, &node3, NULL}, head = {3, &node1, &node2};
    printf("%d\n", goodNodes(&head));
    return 0;
}
