#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmp(const void *, const void *);
int timePointToMinutes(char *);
int findMinDifference(char **, int);

int cmp(const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}

int timePointToMinutes(char *timePoint)
{
    int hour, minute;
    if (sscanf(timePoint, "%d:%d", &hour, &minute) == 2)
        return hour * 60 + minute;
    return -1;
}

int findMinDifference(char **timePoints, int timePointsSize)
{
    int res = INT_MAX, *minutes = (int *)malloc(timePointsSize * sizeof(int));
    if (!minutes) return INT_MIN;

    for (int i = 0; i < timePointsSize; i++)
        minutes[i] = timePointToMinutes(timePoints[i]);

    qsort(minutes, timePointsSize, sizeof(int), cmp);
    for (int i = 1; i < timePointsSize; i++)
        if (res > (minutes[i] - minutes[i - 1]))
            res = (minutes[i] - minutes[i - 1]);

    if (res > (24 * 60 + minutes[0] - minutes[timePointsSize - 1]))
        res = (24 * 60 + minutes[0] - minutes[timePointsSize - 1]);
    free(minutes);
    return res;
}

int main()
{
    char *timePoints[] = {"23:59", "00:00"};
    printf("%d\n", findMinDifference(timePoints, 2));
    return 0;
}
