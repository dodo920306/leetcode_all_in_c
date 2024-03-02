#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int furthestBuilding(int *heights, int heightsSize, int bricks, int ladders);

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int furthestBuilding(int *heights, int heightsSize, int bricks, int ladders)
{
    if (heightsSize <= ladders) return heightsSize - 1;
    int res = 0, *max = (int *)calloc(ladders + 1, sizeof(int)), length = ladders, sign = ((sizeof(int) * CHAR_BIT) - 1);
    if (!max) {
        perror("Error");
        return -1;
    }
    max[ladders] = INT_MAX;
    heightsSize--;
    for (int i = 0, diff; i < heightsSize; i++) {
        diff = (heights[i + 1] - heights[i]);
        if (!diff || (diff >> sign))  res++;
        else {
            if (ladders-- > 0) {
                /* greedy: if there are ladders, use ladders. */
                max[ladders] = diff;
                res++;
            }
            else {
                /* First entrance: ladders == -1 and max isn't sorted. */
                if (!(~ladders) && length > 1)    qsort(max, length, sizeof(int), cmp);
                /**
                 * Since there is no ladders, we replace the shortest ladder with bricks if 
                 * it's shorter than the current diff.
                 * Otherwise, we just use bricks to cross the current diff.
                 */
                bricks -= diff > *max ? *max : diff;
                /* no bricks left */
                if (bricks >> sign) break;
                else    res++;

                /* update max if it has been changed while maintaining it as sorted */
                if (diff > *max)
                    for (int j = 0; j < length; j++)
                        if (max[j + 1] > diff) {
                            max[j] = diff;
                            break;
                        }
                        else    max[j] = max[j + 1];
            }
        }
    }
    free(max);
    return res;
}

int main()
{
    int heights[] = {4,2,7,6,9,14,12};
    printf("%d", furthestBuilding(heights, 7, 5, 1));
    return 0;
}
