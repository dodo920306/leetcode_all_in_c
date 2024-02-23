#include <stdio.h>
#include <stdlib.h>

int findJudge(int n, int **trust, int trustSize, int *trustColSize);

int findJudge(int n, int **trust, int trustSize, int *trustColSize)
{
    int *count = (int *)calloc(n + 1, sizeof(int)), res = -1;
    if (!count) {
        perror("Error");
        return res;
    }

    for (int i = 0; i < trustSize; i++) {
        count[trust[i][0]]--;
        count[trust[i][1]]++;
    }

    for (int i = 1; i <= n; i++)
        if (count[i] == n - 1) {
            res = i;
            break;
        }

    free(count);
    return res;
}

int main()
{
    int **trust = (int **)malloc(2 * sizeof(int *)), trustColSize[] = {2, 2};
    if (!trust) {
        perror("Error");
        return -1;
    }
    trust[0] = (int *)malloc(2 * sizeof(int));
    trust[1] = (int *)malloc(2 * sizeof(int));
    if (!trust[0] || !trust[1]) {
        perror("Error");
        return -1;
    }
    trust[0][0] = 1;
    trust[0][1] = 3;
    trust[1][0] = 2;
    trust[1][1] = 3;
    printf("%d", findJudge(3, trust, 2, trustColSize));
    free(trust[0]);
    free(trust[1]);
    free(trust);
    return 0;
}
