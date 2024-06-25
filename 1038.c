#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs(int prefix_sum, struct TreeNode* root);
struct TreeNode* bstToGst(struct TreeNode* root);

int dfs(int prefix_sum, struct TreeNode* root)
{
    if (root) {
        /* update root value with the sum of the right subtree and the prefix sum */
        root->val += dfs(prefix_sum, root->right);
        /* update root value with the sum of the left subtree with root value as the prefix sum */
        return dfs(root->val, root->left);
    }
    return prefix_sum;
}

struct TreeNode* bstToGst(struct TreeNode* root)
{
    dfs(0, root);
    return root;
}

int main()
{
    struct TreeNode node0, node1, node2, node3, node4, node5, node6, node7, node8;
    node0.val = 0;
    node0.left = NULL;
    node0.right = NULL;
    node1.val = 1;
    node1.left = &node0;
    node1.right = &node2;
    node2.val = 2;
    node2.left = NULL;
    node2.right = &node3;
    node3.val = 3;
    node3.left = NULL;
    node3.right = NULL;
    node4.val = 4;
    node4.left = &node1;
    node4.right = &node6;
    node5.val = 5;
    node5.left = NULL;
    node5.right = NULL;
    node6.val = 6;
    node6.left = &node5;
    node6.right = &node7;
    node7.val = 7;
    node7.left = NULL;
    node7.right = &node8;
    node8.val = 8;
    node8.left = NULL;
    node8.right = NULL;
    bstToGst(&node4);
    printf("[%d,%d,%d,%d,%d,%d,%d,null,null,null,%d,null,null,null,%d]\n", node4.val, node1.val, node6.val, node0.val, node2.val, node5.val, node7.val, node3.val, node8.val);
    return 0;
}
