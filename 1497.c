#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canArrange(int *arr, int arrSize, int k);

bool canArrange(int *arr, int arrSize, int k)
{
    int *freq = (int *)calloc(k, sizeof(int));
    if (!freq)  return false;

    for (int i = 0; i < arrSize; i++) {
        arr[i] = ((arr[i] % k) + k) % k;
        freq[arr[i]]++;
    }

    /* Check if there is odd number of multiple of k */
    if ((*freq) & 0x01) return false;

    for (int i = 1; i < k; i++)
        if (freq[i] != freq[k - i]) return false;

    return true;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 10, 6, 7, 8, 9};
    printf("%s\n", canArrange(arr, 10, 5) ? "true" : "false");
    return 0;
}
