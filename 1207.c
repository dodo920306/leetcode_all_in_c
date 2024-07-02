#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool uniqueOccurrences(int *arr, int arrSize);

bool uniqueOccurrences(int *arr, int arrSize)
{
    int occurence[2001] = {0};
    bool *table;
    if (!(table = (bool *)calloc(arrSize + 1, sizeof(bool))))
        return false;
    for (int i = 0; i < arrSize; i++)
        occurence[arr[i] + 1000]++;
    for (int i = 0; i <= 2000; i++)
        if (occurence[i]) {
            if (table[occurence[i]])
                return false;
            else
                table[occurence[i]] = true;
        }
    free(table);
    return true;
}

int main()
{
    int arr[] = {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0};
    printf("%s\n", uniqueOccurrences(arr, 10) ? "true" : "false");
    return 0;
}
