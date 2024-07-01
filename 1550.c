#include <stdio.h>
#include <stdbool.h>

bool threeConsecutiveOdds(int *arr, int arrSize);

bool threeConsecutiveOdds(int *arr, int arrSize)
{
    if (arrSize > 2)
        for (int i = 0, count = 0; i < arrSize; i++) {
            if (arr[i] % 2) count++;
            else    count = 0;
            if (count == 3) return true;
        }
    return false;
}

int main()
{
    int arr[] = {1, 2, 34, 3, 4, 5, 7, 23, 12};
    printf("%s\n", threeConsecutiveOdds(arr, 9) ? "true" : "false");
    return 0;
}
