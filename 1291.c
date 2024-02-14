#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int* sequentialDigits(int low, int high, int* returnSize);

int* sequentialDigits(int low, int high, int* returnSize)
{
    char *s = "123456789", *digits;
    int log_low = (int)log10((double)low), log_high = (int)log10((double)high), *res = (int *)malloc(36 * sizeof(int));
    if (!res) {
        perror("Error");
        return NULL;
    }

    (*returnSize) = 0;
    for (int i = log_low, k = 0, l = 0; i <= log_high; i++) {
        digits = (char *)malloc((i + 2) * sizeof(char));
        if (!digits) {
            perror("Error");
            return NULL;
        }
        for (char *iter = s; iter[i] != '\0'; iter++) {
            strncpy(digits, iter, (i + 1));
            digits[i + 1] = '\0';
            sscanf(digits, "%d", &k);
            if (k >= low && k <= high) {
                res[l++]= k;
                (*returnSize)++;
            }
        }
        free(digits);
    }
    return res;
}

int main()
{
    int low = 100, high = 300, returnSize, *res = sequentialDigits(low, high, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", res[i]);
    }
    free(res);
    return 0;
}
