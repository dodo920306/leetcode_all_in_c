#include <stdio.h>

int findDuplicate(int *nums, int numsSize);

int findDuplicate(int *nums, int numsSize)
{
    /**
     * If we think of nums as a list,
     * where nums[i] means what i points to,
     * since there are duplicate numbers by pigeonhole principle,
     * there must be two indices point to the same number,
     * which is the answer.
     *
     * For a linear list,
     * there won't be any pair of nodes point to a same node
     * like o -- o -- o -- o -- o.
     * However, if there are a pair of nodes point to a same node,
     * a cycle must exist.
     * Like in  o
     *        /   \
     * o -- o      o
     *        \   /
     *          o,
     * the beginning of the cycle is been pointed by two different node.
     */
    int j = nums[nums[0]];
    for (int i = nums[0]; i != j; j = nums[nums[j]])   i = nums[i];

    /**
     * Knowing that i meets j isn't enough because
     * we want "the beginning of the cycle" as the answer
     * not where they meet.
     * What relationship can be found between the meeting point and the beginning of the cycle?
     *
     * Let us say that the cycle has m node.
     * Since the list has numsSize nodes, the part not in the cycle must has (numsSize - m) nodes.
     * Since j always be ahead of i for 1 node per step, when i enters the cycle,
     * j should be (numsSize - m) nodes ahead of i.
     * Since j is in a cycle, we must add module here,
     * so j must be (numsSize - m) % m nodes ahead of i.
     * 
     * In such a cycle, j can catches up and meets i after m - ((numsSize - m) % m) steps
     * i.e. i and j will meet each other in k-th nodes clockwisely
     * after the beginning where k = m - ((numsSize - m) % m).
     * Thus, there will be m - k nodes between i (or j) and the beginning clockwisely.
     * Moreover, m - k = m - m + ((numsSize - m) % m)
     *                 = ((numsSize - m) % m)
     * Therefore, for i starts to walk from the head of the list
     * and enters the cycle after (numsSize - m) steps,
     * j will meet in the beginning of the cycle if j also walks (numsSize - m) steps
     * at the same speed since j will only move for ((numsSize - m) % m) nodes clockwisely
     * for j is in a cycle, and
     * j is exactly ((numsSize - m) % m) steps from the beginning of the cycle clockwisely.
     */
    for (int i = 0; i != j; j = nums[j])   i = nums[i];

    return j;
}

int main()
{
    int nums[] = {1, 3, 4, 2, 2};
    printf("%d\n", findDuplicate(nums, 5));
    return 0;
}
