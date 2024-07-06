#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

enum Direction {
    left,
    right
};

void maxZigZag(struct TreeNode *node, enum Direction direction, int count, int *res);
int longestZigZag(struct TreeNode *root);

void maxZigZag(struct TreeNode *node, enum Direction direction, int count, int *res)
{
    if (node)
        if (direction == left) {
            /* continue this zigzag path */
            maxZigZag(node->left, right, count + 1, res);
            /* consider begin a new zigzag path */
            maxZigZag(node->right, left, 0, res);
        }
        else {
            /* consider begin a new zigzag path */
            maxZigZag(node->left, right, 0, res);
            /* continue this zigzag path */
            maxZigZag(node->right, left, count + 1, res);
        }
    /* check if the length of this path is the maximum in the end of the path */
    else if ((*res) < count)
        (*res) = count;
}

int longestZigZag(struct TreeNode *root)
{
    int res = 0;
    maxZigZag(root->left, right, 0, &res);
    maxZigZag(root->right, left, 0, &res);
    return res;
}

int main()
{
    struct TreeNode node7 = {1, NULL, NULL}, node6 = {1, NULL, &node7}, node5 = {1, NULL, NULL}, node4 = {1, NULL, &node6}, node3 = {1, &node4, &node5}, node2 = {1, NULL, NULL}, node1 = {1, &node2, &node3}, head = {1, NULL, &node1};
    printf("%d\n", longestZigZag(&head));
    return 0;
}
