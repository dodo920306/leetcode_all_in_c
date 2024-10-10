#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct stack {
    int *elements, size;
};

struct stack *newStack(int size)
{
    struct stack *res = (struct stack *)malloc(sizeof(struct stack));
    int *elements = (int *)malloc(size * sizeof(int));
    if (!(elements && res))   return NULL;
    res->elements = elements;
    res->size = 0;
    return res;
}

bool isEmpty(struct stack *self)
{
    return !(self->size);
}

void push(struct stack *self, int k)
{
    self->elements[self->size++] = k;
}

int peek(struct stack *self)
{
    return self->elements[self->size - 1];
}

int pop(struct stack *self)
{
    self->size--;
    return self->elements[self->size];
}

void freeStack(struct stack *self)
{
    free(self->elements);
    free(self);
}

int maxWidthRamp(int *nums, int numsSize)
{
    
    int res = 0;
    struct stack *strictlyDecreasingElementsInNums = newStack(numsSize);
    if (!(strictlyDecreasingElementsInNums)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    push(strictlyDecreasingElementsInNums, 0);
    for (int i = 1; i < numsSize; i++)
        if (nums[i] < nums[peek(strictlyDecreasingElementsInNums)])
            /* nums[i] will be the smalling number between nums[0] and num[i] */
            push(strictlyDecreasingElementsInNums, i);

    numsSize--;
    for (int i = numsSize, _res; i >= 0; i--) {
        while (!isEmpty(strictlyDecreasingElementsInNums) && nums[peek(strictlyDecreasingElementsInNums)] <= nums[i]) {
            /**
             * try finding the longest ramp ending at i.
             * We can pop here because it's impossible for ramps between i and peek(strictlyDecreasingElementsInNums)
             * to be wider than this.
             */
            _res = i - pop(strictlyDecreasingElementsInNums);
            if (res < _res) res = _res;
        }
        if (isEmpty(strictlyDecreasingElementsInNums))  break;
    }
    freeStack(strictlyDecreasingElementsInNums);
    return res;
}

int main()
{
    int nums[] = {9, 8, 1, 0, 1, 9, 4, 0, 4, 1};
    printf("%d\n", maxWidthRamp(nums, 10));
    return 0;
}
