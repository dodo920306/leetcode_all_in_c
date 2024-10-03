#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_INT_STR_LENGTH 10
#define MAXIMUM_TWO_INT_STRS_LENGTH 21

int getDigitNumber(int);
char *intToStr(int);
int cmp(const void *, const void *);
char *largestNumber(int *, int);

int getDigitNumber(int k)
{
    int _k = abs(k), res = 0;
    if (!k) return 1;

    while (_k) {
        _k /= 10;
        res++;
    }
    return res;
}

char *intToStr(int k)
{
    char *res = (char *)calloc((getDigitNumber(k) + 1), sizeof(char));
    if (res)    sprintf(res, "%d", k);
    return res;
}

int cmp(const void *a, const void *b)
{
    char *_a = *(char **)a, *_b = *(char **)b, *__a = (char *)calloc((MAXIMUM_INT_STR_LENGTH << 1) + 1, sizeof(char)), *__b = (char *)calloc((MAXIMUM_INT_STR_LENGTH << 1) + 1, sizeof(char));
    int res = 0;
    if (!__a || !__b)   return -1;

    strncpy(__a, _a, MAXIMUM_INT_STR_LENGTH);
    strncpy(__b, _b, MAXIMUM_INT_STR_LENGTH);

    strncat(__a, _b, MAXIMUM_INT_STR_LENGTH);
    strncat(__b, _a, MAXIMUM_INT_STR_LENGTH);

    res = strcmp(__b, __a);
    free(__a);
    free(__b);
    return res;
}

char *largestNumber(int *nums, int numsSize)
{
    char **strNums = (char **)malloc(numsSize * sizeof(char *)), *res = (char *)calloc(MAXIMUM_INT_STR_LENGTH * numsSize + 1, sizeof(char));
    if (!strNums || !res)   return NULL;

    for (int i = 0; i < numsSize; i++)
        strNums[i] = intToStr(nums[i]);

    qsort(strNums, numsSize, sizeof(char *), cmp);
    if (!strcmp(*strNums, "0"))
        return "0";

    for (int i = 0; i < numsSize; i++) {
        strncat(res, strNums[i], 10);
        free(strNums[i]);
    }
    free(strNums);

    return res;
}

int main()
{
    int nums[] = {3, 30, 34, 5, 9};
    printf("%s\n", largestNumber(nums, 5));
    return 0;
}
