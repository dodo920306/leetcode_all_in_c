#include <stdio.h>
#include <stdlib.h>

#define ONCE_RETURN_ROW_SIZE 512
#define COLUMN_SIZE 3

int cmp(const void *a, const void *b);
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

int main()
{
    int nums[6] = {-1, 0, 1, 2, -1, -4}, returnSize, *returnColumnSizes;
    int **res = threeSum(nums, 6, &returnSize, &returnColumnSizes);
    printf("%d\n", returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

int cmp(const void *a,const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    /**
     * There is only call-by-value in C.
     * Hence, when there is a function parameter as an integer, it should be inputted as a pointer to this integer
     * s.t. the modification of this integer in the function can be kept outside the function. Otherwise, we have to return it.
     * Likewise, when there is a function parameter as an integer array,
     * it should be inputted as a pointer to a pointer to the array.
     * That's why returnSize and returnColumnSizes are inputted in this way.
     */

    /**
     * returnSize: pointer to a integer amount of sets.
     * e.g. *returnSize = 2;
     */
    *returnSize = 0;

    /**
     * res: The result sets. Allocated as 512 integer arrays large first.
     * Since the question is 3Sum, the content should be an array of arrays whose size is 3. 
     * e.g. *returnColumnSizes = {{-1, 0, 1}, {-1, -1, 2}};
     */
    int **res = (int**)malloc(sizeof(int*) * ONCE_RETURN_ROW_SIZE);

    /**
     * Sort the array to make the search algorithm executable.
     */
    qsort(nums, numsSize, sizeof(nums[0]), cmp);

    for (int i = 0; i < numsSize-2; i++){
        /**
         * if nums[i] == nums[i - 1], there's no need to calculate again.
         */
        if (!i || (i > 0 && nums[i] != nums[i - 1])){
            /**
             * nums[j] + nums[k] = -nums[i] since their sum should be zero.
             * nums[j] is in the head, while nums[k] is in the tail, meaning that
             * binary search algorithm is used here.
             */
            int j = i + 1, k = numsSize - 1, target = 0 - nums[i];
            /* The loop ends when j == k, meaning the searching ends.*/
            while (j < k){
                if (nums[j] + nums[k] == target){

                    if (*returnSize && !(*returnSize % ONCE_RETURN_ROW_SIZE)){
                        /** 
                         *  The amount of sets is larger than the size of the current res.
                         *  Hence, we allocate 512 integer arrays more.
                         */
                        res = (int**)realloc(res, sizeof(int*) * ((*returnSize) + ONCE_RETURN_ROW_SIZE));
                    }
                    res[*returnSize] = (int*)malloc(sizeof(int) * COLUMN_SIZE);
                    res[*returnSize][0] = nums[i];
                    res[*returnSize][1] = nums[j];
                    res[*returnSize][2] = nums[k];
                    /* One can get a bug here if typing *returnSize++; instead. Don't omit parentheses here. */
                    (*returnSize)++;

                    /* Keep searching from a new pair of nums[j] and nums[k] */
                    while (j < k && nums[j] == nums[j + 1]) j++;
                    while (j < k && nums[k] == nums[k - 1]) k--;
                    j++;
                    k--;
                }
                else if (nums[j] + nums[k] < target) j++;
                else k--;
            }
        }
    }

    /**
     * returnColumnSizes: Size of each sets.
     * Since the question is 3Sum, the content should be an array containing some integer 3. 
     * e.g. *returnColumnSizes = {3, 3, 3, 3, 3, ..., 3};
     */
    *returnColumnSizes = (int*)malloc(sizeof(int*) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = COLUMN_SIZE;
    }

    res = (int**)realloc(res, sizeof(int*) * (*returnSize));

    return res;
}
