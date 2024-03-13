#include <stdio.h>

int pivotInteger(int n);

int pivotInteger(int n)
{
    int prefix_sum[n + 1];
    *prefix_sum = 0;
    for (int i = 1, sum = 0; i <= n; i++) {
        sum += i;
        prefix_sum[i] = sum;
    }

    for (int i = 1; i <= n; i++)
        if (prefix_sum[i] == prefix_sum[n] - prefix_sum[i - 1]) return i;
    return -1;
}

int main()
{
    printf("%d", pivotInteger(8));
    return 0;
}
