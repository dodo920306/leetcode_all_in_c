#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int request[10000];
} RecentCounter;

RecentCounter *recentCounterCreate();
int recentCounterPing(RecentCounter* obj, int t);
void recentCounterFree(RecentCounter* obj);

RecentCounter *recentCounterCreate()
{
    RecentCounter *res;
    if (!(res = (RecentCounter *)calloc(1, sizeof(RecentCounter))))
        return NULL;
    return res;
}

int recentCounterPing(RecentCounter* obj, int t)
{
    obj->request[obj->end++] = t;
    t -= 3000;
    while (obj->request[obj->start] < t)
        /**
         * Since t will be strictly increasing,
         * we can abandon all old requests.
         */
        obj->start++;
    return obj->end - obj->start;
}

void recentCounterFree(RecentCounter* obj)
{
    free(obj);
}

/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);
 
 * recentCounterFree(obj);
*/

int main()
{
    RecentCounter* obj;
    int t[] = {1, 100, 3001, 3002};
    if (!(obj = recentCounterCreate()))
        return -1;
    printf("[null");
    for (int i = 0; i < 4; i++)
        printf(", %d", recentCounterPing(obj, t[i]));
    printf("]\n");
    recentCounterFree(obj);
    return 0;
}
