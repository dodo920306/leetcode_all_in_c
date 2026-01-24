#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** rangeAddQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize, int** returnColumnSizes);

int main() {
    int query1[] = {1, 1, 2, 2};
    int query2[] = {0, 0, 1, 1};
    int* queries[] = {query1, query2};
    int queriesColSize[] = {4, 4};
    int returnSize = 0;
    int* returnColSized = NULL;
    int** res = rangeAddQueries(3, queries, 2, queriesColSize, &returnSize, &returnColSized);
    printf("[\n");
    for (int i = 0; i < returnSize; i++) {
        printf("    [");
        for (int j = 0; j < returnColSized[i]; j++) {
            printf("%d", res[i][j]);
            if (j + 1 != returnColSized[i]) {
                printf(",");
            }
        }
        free(res[i]);
        printf("]");
        if (i + 1 != returnSize) {
            printf(",");
        }
        printf("\n");
    }
    free(returnColSized);
    free(res);
    printf("]\n");
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** rangeAddQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize, int** returnColumnSizes) {
    int** res = (int**)malloc(n * sizeof(int*));
    int** diff = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        res[i] = (int*)malloc(n * sizeof(int));
        diff[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            diff[i][j] = 0;
        }
    }
    for (int i = 0; i < queriesSize; i++) {
        diff[queries[i][0]][queries[i][1]]++;
        bool isNotLastCol = queries[i][3] < n - 1;
        bool isNotLastRow = queries[i][2] < n - 1;
        if (isNotLastCol) {
            diff[queries[i][0]][queries[i][3] + 1]--;
        }
        if (isNotLastRow) {
            diff[queries[i][2] + 1][queries[i][1]]--;
        }
        if (isNotLastCol && isNotLastRow) {
            diff[queries[i][2] + 1][queries[i][3] + 1]++;
        }
    }
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            res[i][j] = diff[i][j];
            if (i) {
                res[i][j] += res[i - 1][j];
            }
            if (j) {
                res[i][j] += res[i][j - 1];
            }
            if (i && j) {
                res[i][j] -= res[i - 1][j - 1];
            }
        }
        free(diff[i]);
    }
    free(diff);
    *returnSize = n;
    return res;
}
