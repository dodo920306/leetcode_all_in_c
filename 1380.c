#include <stdio.h>
#include <stdlib.h>

int minimumOfRow(int **, int, int);
int maximumOfColumn(int **, int, int);
int *luckyNumbers(int **, int, int *, int *);
void printIntArray(int *, int);

int minimumOfRow(int **matrix, int m, int index)
{
    int res = matrix[index][0];
    for (int i = 1; i < m; i++)
        if (res > matrix[index][i])
            res = matrix[index][i];
    return res;
}

int maximumOfColumn(int **matrix, int n, int index)
{
    int res = matrix[0][index];
    for (int i = 1; i < n; i++)
        if (res < matrix[i][index])
            res = matrix[i][index];
    return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *luckyNumbers(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    /**
     * 3 different facts have to be proved here:
     *     1. The lucky number is the only one lucky number if it exists.
     *     2. The lucky number is the maximum of minimums of rows if it exists.
     *     3. The lucky number is the minimum of maximums of columns if it exists.
     *
     * First, consider two lucky numbers, x and y, in a matrix m.
     * Assume m[i][j] = x and m[k][l] = y.
     * Thus, y <= m[k][j] <= x and x <= m[i][l] <= y.
     * Therefore, x = y.
     *
     * Second, consider two minimums of rows, x and y, in a matrix m.
     * Assume m[i][j] = x, m[k][l] = y, and one of them is the lucky number.
     * Thus, y < m[k][j] and x < m[i][l].
     * If y is the lucky number, x < m[i][l] < y.
     * If x is the lucky number, y < m[k][j] < x.
     * Therefore, the lucky number = max(x, y).
     *
     * Third, consider two maximums of columns, x and y, in a matrix m.
     * Assume m[i][j] = x, m[k][l] = y, and one of them is the lucky number.
     * Thus, x > m[k][j] and y > m[i][l].
     * If x is the lucky number, x < m[i][l] < y.
     * If y is the lucky number, y < m[k][j] < x.
     * Therefore, the lucky number = min(x, y).
     *
     * In conclusion, the lucky number must be the maximum of minimums and
     * the minimum of maximums, and there will only be one such a number.
     */
    int rowMinMax = minimumOfRow(matrix, *matrixColSize, 0), colMaxMin = maximumOfColumn(matrix, matrixSize, 0), *res = (int *)malloc(sizeof(int));
    if (!res)
        return NULL;
    for (int i = 1, temp; i < matrixSize; i++) {
        temp = minimumOfRow(matrix, *matrixColSize, i);
        if (rowMinMax < temp)
            rowMinMax = temp;
    }
    for (int i = 1, temp; i < *matrixColSize; i++) {
        temp = maximumOfColumn(matrix, matrixSize, i);
        if (colMaxMin > temp)
            colMaxMin = temp;
    }
    *res = rowMinMax;
    *returnSize = (rowMinMax == colMaxMin);
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
    int row1[] = {3, 7, 8}, \
        row2[] = {9, 11, 13}, \
        row3[] = {15, 16, 17}, \
        *matrix[] = {row1, row2, row3}, \
        matrixColSize[] = {3, 3, 3}, \
        returnSize = 0, \
        *res = luckyNumbers(matrix, 3, matrixColSize, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
