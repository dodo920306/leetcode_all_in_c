#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int findMinArrowShots(int **points, int pointsSize, int *pointsColSize);

int cmp(const void *a, const void *b)
{
    /* sort by end */
    return ((*(int **)a)[1] > (*(int **)b)[1]);
}

int findMinArrowShots(int **points, int pointsSize, int *pointsColSize)
{
    /* at least one arrow will be used */
    int res = 1;

    qsort(points, pointsSize, sizeof(int) << 1, cmp);
    for (int i = 1, minEnd = points[0][1]; i < pointsSize; i++)
        /* points[i][1] > minEnd by sorting, so if minEnd < points[i][0], there is no overlap */
        if (minEnd < points[i][0]) {
            /* no overlap => increase arrows to shoot 2 groups of them */
            res++;
            minEnd = points[i][1];
        }

    return res;
}

int main()
{
    int point1[] = {10, 16}, point2[] = {2, 8}, point3[] = {1, 6}, point4[] = {7, 12}, pointsColSize[] = {2, 2, 2, 2}, *points[] = {point1, point2, point3, point4};
    printf("%d\n", findMinArrowShots(points, 4, pointsColSize));
    return 0;
}
