#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b);
int triangleNumber(int* nums, int numsSize);

int main() {
    int nums[] = {2, 2, 3, 4};
    printf("%d\n", triangleNumber(nums, 4));
    return 0;
}

int triangleNumber(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int res = 0;
    for (int edge1, edge2, edge3 = numsSize - 1; edge3 > 1; edge3--) {
        edge1 = 0;
        edge2 = edge3 - 1;
        while (edge1 < edge2) {
            if (nums[edge3] < nums[edge1] + nums[edge2]) {
                res += edge2 - edge1;
                edge2--;
            }
            else {
                edge1++;
            }
        }
    }
    return res;
}

int cmp(const void* a, const void* b) {
    return(*(int *)a - *(int *)b);
}
