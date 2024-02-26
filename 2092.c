#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXIMUM 100001

struct union_find {
    int parent[MAXIMUM], rank[MAXIMUM];
};

void init(struct union_find *self, int n);
int find(struct union_find *self, int x);
void unite(struct union_find *self, int x, int y);
bool connected(struct union_find *self, int x, int y);
void reset(struct union_find *self, int x);
int cmp(const void *a, const void *b);

void init(struct union_find *self, int n)
{
    /* make each node point itself */
    for (int i = 0; i < n; self->rank[i++] = 0)
        self->parent[i] = i;
}

int find(struct union_find *self, int x)
{
    /* find the root of x in dsu while compressing the path */
    if (self->parent[x] != x)  self->parent[x] = find(self, self->parent[x]);
    return self->parent[x];
}

void unite(struct union_find *self, int x, int y)
{
    int px = find(self, x), py = find(self, y);
    /* If two args are actually belonging to different components, merge them. */
    if (px != py)
        if (self->rank[px] < self->rank[py])
            self->parent[px] = py;
        else {
            self->parent[py] = px;
            if (self->rank[px] == self->rank[py])
                self->rank[px]++;
        }
}

bool connected(struct union_find *self, int x, int y)
{
    return find(self, x) == find(self, y);
}

void reset(struct union_find *self, int x)
{
    self->parent[x] = x;
    self->rank[x] = 0;
}

int cmp(const void *a, const void *b)
{
    return (*(int **)a)[2] - (*(int **)b)[2];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findAllPeople(int n, int **meetings, int meetingsSize, int *meetingsColSize, int firstPerson, int *returnSize)
{
    qsort(meetings, meetingsSize, sizeof(int *), cmp);

    int *res = (int *)malloc(n * sizeof(int));
    if (!res) {
        perror("Error");
        return NULL;
    }

    struct union_find *graph = (struct union_find *)malloc(sizeof(struct union_find));
    if (!graph) {
        perror("Error");
        return NULL;
    }

    init(graph, n);
    unite(graph, 0, firstPerson);

    for (int start = 0, end = 0; end < meetingsSize; end++)
        if (end == (meetingsSize - 1) || meetings[end][2] != meetings[end + 1][2]) {
            /* this is the end of a moment */
            for (int i = start; i <= end; i++)
                unite(graph, meetings[i][0], meetings[i][1]);
            for (int i = start; i <= end; i++)
                if (!connected(graph, meetings[i][0], 0)) {
                    reset(graph, meetings[i][0]);
                    reset(graph, meetings[i][1]);
                }
            start = end + 1;
        }

    *returnSize = 0;
    for (int i = 0; i < n; i++)
        if (connected(graph, i, 0))    res[(*returnSize)++] = i;

    free(graph);
    return res;
}

int main()
{
    int meeting1[] = {1, 2, 5}, meeting2[] = {2,3,8}, meeting3[] = {1,5,10}, meetingsColSize[] = {3, 3, 3}, returnSize, **meetings = (int **)malloc(3 * sizeof(int *)), *res;
    if (!meetings) {
        perror("Error");
        return -1;
    }
    meetings[0] = meeting1;
    meetings[1] = meeting2;
    meetings[2] = meeting3;

    res = findAllPeople(6, meetings, 3, meetingsColSize, 1, &returnSize);
    for (int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);

    free(meetings);
    free(res);
    return 0;
}
