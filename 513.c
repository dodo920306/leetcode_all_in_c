#include <stdio.h>

/* This number is gotten through experiments. */
#define MAXIMUM_NUMBER_OF_NODE_PER_LEVEL 1000

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int findBottomLeftValue(struct TreeNode *root);

int findBottomLeftValue(struct TreeNode *root)
{
    /**
     * stack1 is for the reversal next level we need to process 
     * while stack2 is for the current level we are processing.
     *
     * Use different stacks so that we can focus on the current level
     * while recording the next level.
     */
    struct TreeNode *stack1[MAXIMUM_NUMBER_OF_NODE_PER_LEVEL], *stack2[MAXIMUM_NUMBER_OF_NODE_PER_LEVEL], *top;
    int size1 = 1, size2 = 0;
    /**
     * Consider a tree like
     *            1
     *          /   \
     *         2     3
     *        /     / \
     *       4     5   6
     *            /
     *           7
     *
     * stack1 = [1]
     * stack2 = []
     */
    *stack1 = root;
    while (size1){
        /**
         * stack1 = []
         * stack2 = [1]
         *
         * stack1 = []
         * stack2 = [2 3]
         *
         * stack1 = []
         * stack2 = [4 5 6]
         *
         * stack1 = []
         * stack2 = [7]
         */
        while (size1--) stack2[size2++] = stack1[size1];
        /**
         * stack1 = [3 2]
         * stack2 = []
         *
         * stackl = [6 5 4]
         * stack2 = []
         *
         * stack1 = []
         * stack2 = [7]
         * 
         * (end)
         */
        /**
         * By the end of the last loop, size1 will be turned from 0 to -1
         * so we need to add it back.
         */
        size1++;
        while (size2--) {
            top = stack2[size2];
            if (top->right)
                stack1[size1++] = top->right;
            if (top->left)
                stack1[size1++] = top->left;
        }
        /**
         * By the end of the last loop, size2 will be turned from 0 to -1
         * so we need to add it back.
         */
        size2++;
    }
    /**
     * To escape the loop:
     * size1 is 0 => No next level yet
     * size2 is 0 => No more node on the left this level
     * top->left and right are NULL => No next level ever
     *
     * => the result
     */
    return top->val;
}

int main()
{
    struct TreeNode node1, node2, node3, node4, node5, node6, node7;

    node1.val = 1;
    node2.val = 2;
    node3.val = 3;
    node4.val = 4;
    node5.val = 5;
    node6.val = 6;
    node7.val = 7;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = NULL;

    node3.left = &node5;
    node3.right = &node6;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = &node7;
    node5.right = NULL;

    node6.left = NULL;
    node6.right = NULL;

    node7.left = NULL;
    node7.right = NULL;

    printf("%d", findBottomLeftValue(&node1));
    return 0;
}
