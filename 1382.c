#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXIMUM_NUMBER_OF_NODES 10000

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack {
    int *arr;
    int size;
};

void inOrder(struct Stack *stack, struct TreeNode *root);
struct TreeNode *construct(struct Stack *stack);
struct TreeNode *balanceBST(struct TreeNode *root);
/* for testing only */
void preorderTestOutput(struct TreeNode *root);

void inOrder(struct Stack *stack, struct TreeNode *root)
{
    if (root) {
        inOrder(stack, root->left);
        stack->arr[stack->size++] = root->val;
        inOrder(stack, root->right);
    }
    return;
}

struct TreeNode *construct(struct Stack *stack)
{
    struct TreeNode *res = NULL;
    if (stack->size && (res = (struct TreeNode *)calloc(1, sizeof(struct TreeNode)))) {
        if (stack->size > 1) {
            bool isEven = !(stack->size % 2);
            int rootIndex = stack->size >> 1, *arrRecorder = stack->arr + 1 + rootIndex;
            res->val = stack->arr[rootIndex];
            stack->size = rootIndex;
            res->left = construct(stack);
            stack->arr = arrRecorder;
            stack->size = rootIndex - isEven;
            res->right = construct(stack);
        }
        else
            res->val = *(stack->arr);
    }
    return res;
}

struct TreeNode *balanceBST(struct TreeNode *root)
{
    int *arrRecorder;
    struct Stack *stack;
    struct TreeNode *res;
    if (!(stack = (struct Stack *)calloc(1, sizeof(struct Stack))) || !(stack->arr = (int *)calloc(MAXIMUM_NUMBER_OF_NODES, sizeof(int))))
        return NULL;
    inOrder(stack, root);
    arrRecorder = stack->arr;
    res = construct(stack);
    free(arrRecorder);
    free(stack);
    return res;
}

/* for testing only */
void preorderTestOutput(struct TreeNode *root)
{
    if (root) {
        printf("%d ", root->val);
        preorderTestOutput(root->left);
        preorderTestOutput(root->right);
        free(root);
    }
}

int main()
{
    struct TreeNode node1, node2, node3, node4;
    node1.val = 1;
    node1.left = NULL;
    node1.right = &node2;
    node2.val = 2;
    node2.left = NULL;
    node2.right = &node3;
    node3.val = 3;
    node3.left = NULL;
    node3.right = &node4;
    node4.val = 4;
    node4.left = NULL;
    node4.right = NULL;
    preorderTestOutput(balanceBST(&node1));
    printf("\n");
    return 0;
}
