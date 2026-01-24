#include <stdio.h>
#include <stdlib.h>

int countCoveredBuildings(int n, int** buildings, int buildingsSize, int* buildingsColSize);

int main()
{
    int building1[] = {1,2};
    int building2[] = {2,2};
    int building3[] = {3,2};
    int building4[] = {2,1};
    int building5[] = {2,3};
    int* buildings[] = {building1, building2, building3, building4, building5};
    int buildingsColSize[] = {2, 2, 2, 2, 2};
    printf("%d\n", countCoveredBuildings(3, buildings, 5, buildingsColSize));
    return 0;
}

int countCoveredBuildings(int n, int** buildings, int buildingsSize, int* buildingsColSize)
{
    n++;
    int *minYOfEveryX = malloc(n * sizeof(int));
    int *maxYOfEveryX = calloc(n, sizeof(int));
    int *minXOfEveryY = malloc(n * sizeof(int));
    int *maxXOfEveryY = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        minYOfEveryX[i] = n;
        minXOfEveryY[i] = n;
    }
    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];
        if (y < minYOfEveryX[x]) {
            minYOfEveryX[x] = y;
        }
        if (y > maxYOfEveryX[x]) {
            maxYOfEveryX[x] = y;
        }
        if (x < minXOfEveryY[y]) {
            minXOfEveryY[y] = x;
        }
        if (x > maxXOfEveryY[y]) {
            maxXOfEveryY[y] = x;
        }
    }
    int res = 0;
    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];
        if (y > minYOfEveryX[x] && y < maxYOfEveryX[x] && x > minXOfEveryY[y] && x < maxXOfEveryY[y]) {
            res++;
        }
    }
    free(minYOfEveryX);
    free(maxYOfEveryX);
    free(minXOfEveryY);
    free(maxXOfEveryY);
    return res;
}
