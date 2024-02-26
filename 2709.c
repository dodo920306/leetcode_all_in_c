#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* the maximum value possibly in nums */
#define MAXIMUM 100001

/* disjoint set union */
struct dsu {
    int *dsu, *size;
};

struct dsu *init(int n);
void _free(struct dsu *self);
int find(struct dsu *self, int x);
void merge(struct dsu *self, int x, int y);
bool canTraverseAllPairs(int *nums, int numsSize);

struct dsu *init(int n)
{
    struct dsu *res = (struct dsu *)malloc(sizeof(struct dsu));
    res->dsu = (int *)malloc(n * sizeof(int));
    res->size = (int *)malloc(n * sizeof(int));
    /* make each node point itself */
    for (int i = 0; i < n; res->size[i++] = 1)  res->dsu[i] = i;
    return res;
}

void _free(struct dsu *self)
{
    free(self->size);
    free(self->dsu);
    free(self);
}

int find(struct dsu *self, int x)
{
    /* find the root of x in dsu while compressing the path */
    if (self->dsu[x] != x)  self->dsu[x] = find(self, self->dsu[x]);
    return self->dsu[x];
}

void merge(struct dsu *self, int x, int y)
{
    int fx = find(self, x), fy = find(self, y), temp;
    /* If two args are actually belonging to different components, merge them. */
    if (fx != fy) {
        if (self->size[fx] > self->size[fy]) {
            temp = fx;
            fx = fy;
            fy = temp;
        }
        /* merge two components in to one with larger one as root */
        self->dsu[fx] = fy;
        self->size[fy] += self->size[fx];
    }
}

bool canTraverseAllPairs(int *nums, int numsSize)
{
    if (numsSize == 1)  return true;
    /* sieve of Eratosthenes */
    int *sieve = (int *)calloc(MAXIMUM, sizeof(int)), res = 0;
    /* a set of elements in nums */
    bool *has = (bool *)calloc(MAXIMUM, sizeof(bool));

    if (!sieve || !has) {
        perror("Error");
        return false;
    }

    for (int i = 0; i < numsSize; has[nums[i++]] = true);
    if (has[1]) return false;

    /* mark every number with its minimum prime factor */
    for (int i = 2; i < MAXIMUM; i++)
        if (!sieve[i])
            for (int j = i; j < MAXIMUM; j += i)   sieve[j] = i;

    /* The first half is for the nums, and the second half is for primes. */
    struct dsu *_union = init(2 * MAXIMUM);
    for (int i = 0, val, prime, root; i < numsSize; i++) {
        val = nums[i];
        while(val > 1) {
            /* get the minimum prime factor of val */
            prime = sieve[val];
            /* find the node of the minimum prime factor of val in dsu */
            root = prime + MAXIMUM - 1;
            /* If the node isn't in the same component with nums[i], merge them. */
            if (find(_union, root) != find(_union, nums[i]))
                /**
                 * The nums[i] is the third argment, 
                 * so the component of root will be merged into the component of nums[i]
                 * if they have the same size.
                 * In this way, 
                 * only the size of the component of nums[i] will be increased through loops.
                 */
                merge(_union, root, nums[i]);
            /**
             * delete prime from the val
             * If val = 2^x * 3^y * 5^z * ...,
             * val will be 3^y * 5^z * ... after the first loop.
             * Thus, sieve[val] = 3 in the next loop for x, y, z > 0.
             */
            while (!(val % prime))  val /= prime;

            /**
             * Through loops, we make every prime factor of nums[i] point to nums[i],
             * so it will be like
             * 2 ---------------> nums[0]
             *    --------------⬈
             *   /
             * 3
             *   \
             *    --------------⬊
             * 5 ---------------> nums[1]
             * ...
             * 
             * However, since the root of 3 is nums[0] while i = 1,
             * merging 3 with nums[1] will actually merge nums[0] into nums[1]
             * since merging is between the roots of two element is dsu,
             * so it turns out like
             * 
             * 2 ---------------> nums[0]
             *    --------------⬈  |
             *   /                  |
             * 3                    ⬇
             * 5 ---------------> nums[1]
             * ...
             * 
             * Thus, once the two numbers has a same prime factor, 
             * they will be in the same component, so their root will be the same.
             */
        }
    }

    for (int i = 2; i < MAXIMUM; i++)
        /**
         * If the element can still points to itself in dsu, 
         * it must either be the root of a big component, or 
         * it just has no component to stay like default.
         * 
         * A set is use here to prevent considering elements with same values
         * causing considering a same component twice.
         */
        if (has[i] && find(_union, i) == i) res++;

    free(has);
    free(sieve);
    _free(_union);

    return res == 1;
}

int main()
{
    int nums[] = {4, 3, 12, 8};
    printf("%s", canTraverseAllPairs(nums, 4) ? "true" : "false");
    return 0;
}
