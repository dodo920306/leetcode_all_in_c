#include <stdio.h>
#include <stdlib.h>

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize);

int main()
{
    int point1[] = {1, 1};
    int point2[] = {3, 4};
    int point3[] = {-1, 0};
    int** points = (int**)malloc(3 * sizeof(int*));
    int pointsColSize[3] = {2, 2, 2};
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    printf("%d\n", minTimeToVisitAllPoints(points, 3, pointsColSize));
    return 0;
}

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize)
{
    int res = 0;
    for (int i = 1; i < pointsSize; i++) {
        int diffX = abs(points[i][0] - points[i - 1][0]);
        int diffY = abs(points[i][1] - points[i - 1][1]);
        if (diffX < diffY) {
            res += diffY;
        }
        else {
            res += diffX;
        }
    }
    return res;
}
