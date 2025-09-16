#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack {
    int* content;
    int currentSize;
    int totalSize;
    struct stack* (*push)(struct stack*, int);
    int (*pop)(struct stack*);
    bool (*isFull)(struct stack*);
    bool (*isEmpty)(struct stack*);
    void (*free)(struct stack*);
};

int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize);
int getGCD(int smaller, int bigger);
struct stack* newStack(int totalSize);
struct stack* stackPush(struct stack* self, int x);
int stackPop(struct stack* self);
bool stackIsFull(struct stack* self);
bool stackIsEmpty(struct stack* self);
void stackFree(struct stack* self);

int main()
{
    int numsSize = 7, returnSize = 0;
    int* nums = malloc(numsSize * sizeof(int));
    nums[0] = 6;
    nums[1] = 4;
    nums[2] = 3;
    nums[3] = 2;
    nums[4] = 7;
    nums[5] = 6;
    nums[6] = 2;
    int* res = replaceNonCoprimes(nums, numsSize, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d,", res[i]);
    }
    free(nums);
    /* free(res); res == nums */
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize)
{
    struct stack* theProcessingStack = newStack(numsSize);
    for (int i = 0; i < numsSize; i++) {
        theProcessingStack->push(theProcessingStack, nums[i]);
        while (theProcessingStack->currentSize > 1) {
            int x = theProcessingStack->content[theProcessingStack->currentSize - 1];
            int y = theProcessingStack->content[theProcessingStack->currentSize - 2];
            int gcdOfXY = getGCD(x, y);
            if (gcdOfXY > 1) {
                theProcessingStack->pop(theProcessingStack);
                theProcessingStack->pop(theProcessingStack);
                theProcessingStack->push(theProcessingStack, x * (y / gcdOfXY));
            }
            else {
                break;
            }
        }
    }

    *returnSize = theProcessingStack->currentSize;
    for (int i = 0; i < *returnSize; i++) {
        nums[i] = theProcessingStack->content[i];
    }
    theProcessingStack->free(theProcessingStack);
    return nums;
}

int getGCD(int a, int b) {
    return a ? getGCD(b % a, a) : b;
}

/* ___________Stack________________ */
struct stack* newStack(int totalSize)
{
    struct stack* res = malloc(sizeof(struct stack));
    res->content = malloc(totalSize * sizeof(int));
    res->currentSize = 0;
    res->totalSize = totalSize;
    res->push = stackPush;
    res->pop = stackPop;
    res->isFull = stackIsFull;
    res->isEmpty = stackIsEmpty;
    res->free = stackFree;
    return res;
}

struct stack* stackPush(struct stack* self, int x)
{
    if (self->isFull(self)) {
        perror("Stack is full. Stay unchanged.");
        return self;
    }
    self->content[self->currentSize] = x;
    self->currentSize++;
    return self;
}

int stackPop(struct stack* self)
{
    if (self->isEmpty(self)) {
        perror("Stack is empty!!");
        exit(EXIT_FAILURE);
    }
    self->currentSize--;
    return self->content[self->currentSize];
}

bool stackIsFull(struct stack* self)
{
    return self->currentSize == self->totalSize;
}

bool stackIsEmpty(struct stack* self)
{
    return !self->currentSize;
}

void stackFree(struct stack* self)
{
    free(self->content);
    free(self);
}
