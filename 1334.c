#include <stdio.h>
#include <stdlib.h>

int findTheCity(int n, int **edges, int edgesSize, int *edgesColSize, int distanceThreshold);

int findTheCity(int n, int **edges, int edgesSize, int *edgesColSize, int distanceThreshold)
{
    int **distances = (int **)malloc(n * sizeof(int *)), max = n, res = -1;
    if (!(distances)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        distances[i] = (int *)malloc(n * sizeof(int));
        if (!(distances[i])){
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return -1;
        }

        for (int j = 0; j < n; j++)
            distances[i][j] = 10001;
        distances[i][i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        distances[edges[i][0]][edges[i][1]] = edges[i][2];
        distances[edges[i][1]][edges[i][0]] = edges[i][2];
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0, sum; j < n; j++) {
                sum = distances[i][k] + distances[k][j];
                if (distances[i][j] > sum)
                    distances[i][j] = sum;
            }

    for (int i = 0, count; i < n; i++) {
        count = 0;
        for (int j = 0; j < n; j++)
            if (i != j && distances[i][j] <= distanceThreshold)
                count++;
        free(distances[i]);
        if (count <= max) {
            max = count;
            res = i;
        }
    }

    free(distances);
    return res;
}

int main()
{
    int edge1[] = {0, 1, 3}, \
        edge2[] = {1, 2, 1}, \
        edge3[] = {1, 3, 4}, \
        edge4[] = {2, 3, 1}, \
        *edges[] = {edge1, edge2, edge3, edge4}, \
        edgesColSize[] = {3, 3, 3, 3};
    printf("%d\n", findTheCity(4, edges, 4, edgesColSize, 4));
    return 0;
}
