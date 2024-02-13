#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool containsDuplicate(int* nums, int numsSize);
int cmp(const void *a, const void *b);

int main()
{
    int nums[4] = {1,2,3,4};
    printf("%d\n", containsDuplicate(nums, 4));
    return 0;
}

bool containsDuplicate(int* nums, int numsSize)
{
    if (numsSize <= 1){
        return false;
    }
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    for (int i = 1; i < numsSize; i++){
      if (!(nums[i] ^ nums[i - 1])) return true;
    }
    return false;
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
