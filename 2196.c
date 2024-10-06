#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *createBinaryTree(int **, int, int *);
void preorderTraversal(struct TreeNode *);

struct TreeNode *createBinaryTree(int **descriptions, int descriptionsSize, int *descriptionsColSize)
{
    struct TreeNode **nodes = (struct TreeNode **)calloc(100001, sizeof(struct TreeNode *)), *res = NULL;
    bool *children = (bool *)calloc(100001, sizeof(bool));
    if (!(nodes && children)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 0; i < descriptionsSize; i++) {
        if (!nodes[descriptions[i][0]]) {
            nodes[descriptions[i][0]] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            if (!nodes[descriptions[i][0]]) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return NULL;
            }
            nodes[descriptions[i][0]]->val = descriptions[i][0];
            nodes[descriptions[i][0]]->left = NULL;
            nodes[descriptions[i][0]]->right = NULL;
        }
        if (!nodes[descriptions[i][1]]) {
            nodes[descriptions[i][1]] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            if (!nodes[descriptions[i][1]]) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return NULL;
            }
            nodes[descriptions[i][1]]->val = descriptions[i][1];
            nodes[descriptions[i][1]]->left = NULL;
            nodes[descriptions[i][1]]->right = NULL;
        }

        if (descriptions[i][2])
            nodes[descriptions[i][0]]->left = nodes[descriptions[i][1]];
        else
            nodes[descriptions[i][0]]->right = nodes[descriptions[i][1]];
        children[descriptions[i][1]] = true;
    }
    for (int i = 0; i <= 100000; i++)
        if (nodes[i] && !children[i]) {
            res = nodes[i];
            break;
        }
    free(nodes);
    free(children);
    return res;
}

void preorderTraversal(struct TreeNode *root)
{
    if (!root)  return;

    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    free(root);
}

int main()
{
    int description1[] = {20, 15, 1}, \
        description2[] = {20, 17, 0}, \
        description3[] = {50, 20, 1}, \
        description4[] = {50, 80, 0}, \
        description5[] = {80, 19, 1}, \
        *descriptions[] = {
            description1,
            description2,
            description3,
            description4,
            description5}, \
        descriptionsColSize[] = {3, 3, 3, 3, 3};
    struct TreeNode *res = createBinaryTree(descriptions, 5, descriptionsColSize);
    preorderTraversal(res);
    printf("\n");
    return 0;
}
