#include <stdio.h>

#define MIN(a, b)           \
    ({                      \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _b : _a;  \
    })

int countSquares(int **matrix, int matrixSize, int *matrixColSize);

int main() {
    int row1[] = {0,1,1,1};
    int row2[] = {1,1,1,1};
    int row3[] = {0,1,1,1};
    int* matrix[] = {row1, row2, row3};
    int matrixColSize[] = {4, 4, 4};
    printf("%d\n", countSquares(matrix, 3, matrixColSize));
    return 0;
}

int countSquares(int **matrix, int matrixSize, int *matrixColSize)
{
    int res = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < *matrixColSize; j++) {
            if (!matrix[i][j])  continue;
            if (!i || !j)   res++;
            else {
                /**
                 * matrix[i][j] is the minimun values of left, top, and top-left elements plus 1,
                 * which means the number of squares that can be formed with matrix[i][j] as the
                 * bottom-right element.
                 * For example, for matrix,
                 * 1 1
                 * 1 1,
                 * the result will be
                 * 1 1
                 * 1 2,
                 * and the sum of them is our answer,
                 * in this case it's 5.
                 */
                matrix[i][j] = MIN(matrix[i - 1][j - 1], MIN(matrix[i - 1][j], matrix[i][j - 1])) + 1;
                res += matrix[i][j];
            }
        }
    }
    return res;
}
