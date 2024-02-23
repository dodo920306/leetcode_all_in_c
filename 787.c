#include <stdio.h>
#include <stdlib.h>

int findCheapestPrice(int n, int **flights, int flightsSize, int *flightsColSize, int src, int dst, int k);

int findCheapestPrice(int n, int **flights, int flightsSize, int *flightsColSize, int src, int dst, int k)
{
    int *costs[2], res = -1;

    costs[0] = (int *)malloc(n * sizeof(int));
    costs[1] = (int *)malloc(n * sizeof(int));
    if (!costs[0] || !costs[1]) {
        perror("Error");
        return INT_MIN;
    }

    for (int i = 0; i < n; costs[1][i++] = INT_MAX);
    costs[1][src] = 0;

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n; costs[0][j++] = costs[1][j]);
        /* If there are i stops, what's the cheapest price from src to each city? */
        for (int j = 0, cost; j < flightsSize; j++)
            if (costs[0][flights[j][0]] != INT_MAX) {
                cost = flights[j][2] + costs[0][flights[j][0]];
                /**
                 * cost may be compared with the result of the last loop.
                 * In this case, we consider whether to take this number of stops or not.
                 * Or, cost may be compared with the current result of this loop.
                 * In this case, we consider whether to take this city as a new stop or not.
                 */
                if (cost < costs[1][flights[j][1]])
                    /* relax */
                    costs[1][flights[j][1]] = cost;
            }

        /**
         * for (int j = 0; j < n; printf("%d ", costs[1][j++]));
         * printf("\n");
         */
    }
    if (costs[1][dst] != INT_MAX)   res = costs[1][dst];
    free(costs[1]);
    free(costs[0]);

    return res;
}

int main()
{
    int *flights[5], flightsColSize[] = {3, 3, 3, 3, 3};
    for (int i = 0; i < 5; i++) {
        flights[i] = (int *)malloc(3 * sizeof(int));
        if (!flights[i]) {
            perror("Error");
            return -1;
        }
    }
    flights[0][0] = 0;
    flights[0][1] = 1;
    flights[0][2] = 100;
    flights[1][0] = 1;
    flights[1][1] = 2;
    flights[1][2] = 100;
    flights[2][0] = 2;
    flights[2][1] = 0;
    flights[2][2] = 100;
    flights[3][0] = 1;
    flights[3][1] = 3;
    flights[3][2] = 600;
    flights[4][0] = 2;
    flights[4][1] = 3;
    flights[4][2] = 200;
    printf("%d", findCheapestPrice(4, flights, 5, flightsColSize, 0, 3, 1));
    for (int i = 0; i < 5; free(flights[i++]));
    return 0;
}
