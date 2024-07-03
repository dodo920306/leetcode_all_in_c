#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize)
{
    *returnSize = 1;
    for (int i = 1; i < asteroidsSize; i++) {
        /* It's not possible for asteroids[i] to be 0. */
        while ((*returnSize) && asteroids[(*returnSize) - 1] > 0 && asteroids[i] < 0) {
            /* Collisions only happpen when asteroids[(*returnSize) - 1] and asteroids[i] approach each other. */
            if (asteroids[(*returnSize) - 1] < -asteroids[i])
                /* asteroids[(*returnSize) - 1] explodes. */
                (*returnSize)--;
            else {
                /* asteroids[i] explodes. */
                if (asteroids[(*returnSize) - 1] == -asteroids[i])
                    /* asteroids[(*returnSize) - 1] also explodes. */
                    (*returnSize)--;
                goto pass;
            }
        }
        /* No collision happened. Add asteroids[i]. */
        asteroids[(*returnSize)++] = asteroids[i];
        /* asteroids[i] explodes. Don't add asteroids[i]. */
        pass: ;
    }
    return asteroids;
}

int main()
{
    int *asteroids, returnSize, *res;
    /**
     * To allow callers to call free() while performing the algoithm in place,
     * we malloc the input array here like Leetcode did.
     */
    if (!(asteroids = (int *)malloc(3 * sizeof(int))))
        return errno;
    asteroids[0] = 5;
    asteroids[1] = 10;
    asteroids[2] = -5;
    res = asteroidCollision(asteroids, 3, &returnSize);
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        if (i)
            printf(", ");
        printf("%d", res[i]);
    }
    printf("]\n");
    free(res);
    return 0;
}
