#include <stdio.h>

void sortColors(int* nums, int numsSize);

int main()
{
    int nums[6] = {2,0,2,1,1,0};
    sortColors(nums, 6);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", nums[i]);
    }

    return 0;
}

void sortColors(int* nums, int numsSize){
    int count[3] = {0};
    for (int i = 0; i < numsSize; i++){
        count[nums[i]]++;
    }
    for (int i = 0, j = 0; i < 3; i++){
        while (count[i]--){
            nums[j++] = i;
        }
    }
}
