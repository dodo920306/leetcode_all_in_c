#include <stdio.h>
#include <stdlib.h>

int pivotInteger(int n);

int pivotInteger(int n)
{
    int *prefix_sum = (int *)malloc((n + 1) * sizeof(int)), i = 0;
    if (!prefix_sum) {
        perror("Error");
        return INT_MIN;
    }
    for (int sum = 0; i <= n; i++) {
        sum += i;
        prefix_sum[i] = sum;
    }

    for (i = 1; i <= n; i++)
        if (prefix_sum[i] == prefix_sum[n] - prefix_sum[i - 1]) break;
    
    free(prefix_sum);
    return i > n ? -1 : i;
}

int main()
{
    printf("%d", pivotInteger(8));
    return 0;
}
