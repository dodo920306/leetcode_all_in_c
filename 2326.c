#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

void rotateRight(enum direction *direction)
{
    (*direction) = ((*direction) + 1) % 4;
}

void move(int **res, int *i, int *j, enum direction *direction)
{
    int _i = (*i), _j = (*j);

    switch (*direction) {
        case NORTH:
            if (res[_i - 1][_j] != -1) {
                rotateRight(direction);
                _j++;
            }
            else
                _i--;
            break;
        case EAST:
            if (res[_i][_j + 1] != -1) {
                rotateRight(direction);
                _i++;
            }
            else
                _j++;
            break;
        case SOUTH:
            if (res[_i + 1][_j] != -1) {
                rotateRight(direction);
                _j--;
            }
            else
                _i++;
            break;
        case WEST:
            if (res[_i][_j - 1] != -1) {
                rotateRight(direction);
                _i--;
            }
            else
                _j--;
        default:
            break;
    }
    (*i) = _i;
    (*j) = _j;
}

int **spiralMatrix(int m, int n, struct ListNode *head, int *returnSize, int **returnColumnSizes)
{
    int **res = NULL;
    enum direction direction = EAST;

    (*returnColumnSizes) = (int *)calloc(m, sizeof(int));
    res = (int **)calloc((m + 2), sizeof(int *));
    if (!((*returnColumnSizes) && res)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    res[0] = (int *)calloc((n + 2), sizeof(int));
    res[m + 1] = (int *)calloc((n + 2), sizeof(int));
    if (!(res[0] && res[m + 1])) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 1; i <= m; i++) {
        res[i] = (int *)calloc((n + 2), sizeof(int));
        if (!(res[i])) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return NULL;
        }

        for (int j = 1; j <= n; j++)    res[i][j] = -1;
        (*returnColumnSizes)[i - 1] = n;
    }

    *returnSize = m;
    for (int i = 1, j = 1; head; head = head->next) {
        res[i][j] = head->val;
        move(res, &i, &j, &direction);
    }

    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++)
            res[i][j] = res[i + 1][j + 1];

    free(res[m + 1]);
    free(res[m]);
    return res;
}

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%d]\n", arr[arrSize]);
    else
        printf("]\n");
}

int main()
{
    /* 3,0,2,6,8,1,7,9,4,2,5,5,0 */
    struct ListNode node13 = {0, NULL}, \
                    node12 = {5, &node13}, \
                    node11 = {5, &node12}, \
                    node10 = {2, &node11}, \
                    node9 = {4, &node10}, \
                    node8 = {9, &node9}, \
                    node7 = {7, &node8}, \
                    node6 = {1, &node7}, \
                    node5 = {8, &node6}, \
                    node4 = {6, &node5}, \
                    node3 = {2, &node4}, \
                    node2 = {0, &node3}, \
                    node1 = {3, &node2};
    int returnSize = 0, *returnColumnSizes = NULL, **res = spiralMatrix(3, 5, &node1, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        printIntArray(res[i], returnColumnSizes[i]);
        free(res[i]);
    }
    free(returnColumnSizes);
    free(res);
    return 0;
}
