#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct robot {
    int index, position, health;
    char direction;
};

struct stack {
    int size;
    struct robot **val;
};

bool isEmpty(struct stack *s);
void push(struct stack *s, struct robot *k);
struct robot *pop(struct stack *s);
struct robot *peek(struct stack *s);
struct stack *newStack(int size);
void freeStack(struct stack *s);
int ascByPosition(const void *a, const void *b);
int ascByIndex(const void *a, const void *b);
int *survivedRobotsHealths(int *positions, int positionsSize, int *healths, int healthsSize, char *directions, int *returnSize);

bool isEmpty(struct stack *s)
{
    return !(s->size);
}

void push(struct stack *s, struct robot *k)
{
    s->val[s->size++] = k;
}

struct robot *pop(struct stack *s)
{
    s->size--;
    return s->val[s->size];
}

struct robot *peek(struct stack *s)
{
    return s->val[s->size - 1];
}

struct stack *newStack(int size)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    if (!s || !(s->val = (struct robot **)malloc(size * sizeof(struct robot *))))
        return NULL;
    s->size = 0;
    return s;
}

void freeStack(struct stack *s)
{
    free(s->val);
    free(s);
}

int ascByPosition(const void *a, const void *b)
{
    struct robot *_a = *((struct robot **)a), *_b = *((struct robot **)b); 
    return _a->position - _b->position;
}

int ascByIndex(const void *a, const void *b)
{
    struct robot *_a = *((struct robot **)a), *_b = *((struct robot **)b); 
    return _a->index - _b->index;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *survivedRobotsHealths(int *positions, int positionsSize, int *healths, int healthsSize, char *directions, int *returnSize)
{
    int *res = (int *)malloc(healthsSize * sizeof(int));
    struct robot **robots = (struct robot **)malloc(positionsSize * sizeof(struct robot *));
    struct stack *s = newStack(positionsSize);
    *returnSize = 0;
    if (!(res && robots && s))
        return NULL;

    for (int i = 0; i < positionsSize; i++) {
        robots[i] = (struct robot *)malloc(sizeof(struct robot));
        if (!(robots[i]))   return NULL;
        robots[i]->index = i;
        robots[i]->position = positions[i];
        robots[i]->health = healths[i];
        robots[i]->direction = directions[i];
    }
    qsort(robots, positionsSize, sizeof(struct robot *), ascByPosition);
    for (int i = 0; i < positionsSize; i++)
        if (robots[i]->direction == 'R')
            push(s, robots[i]);
        else
            while (!isEmpty(s) && robots[i]->health)
                if (peek(s)->health < robots[i]->health) {
                    (robots[i]->health)--;
                    (pop(s)->health) = 0;
                }
                else if (peek(s)->health == robots[i]->health) {
                    (robots[i]->health) = 0;
                    (pop(s)->health) = 0;
                }
                else {
                    (robots[i]->health) = 0;
                    (peek(s)->health)--;
                    if (!(peek(s)->health))  pop(s);
                }

    qsort(robots, healthsSize, sizeof(struct robot *), ascByIndex);
    for (int i = 0; i < healthsSize; i++) {
        if (robots[i]->health)  res[(*returnSize)++] = robots[i]->health;
        free(robots[i]);
    }

    free(robots);
    freeStack(s);
    return res;
}

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%d]\n", arr[arrSize]);
    else
        printf("]\n");
}

int main()
{
    char *directions = "RLRL";
    int positions[] = {3, 5, 2, 6}, healths[] = {10, 10, 15, 12}, returnSize = 0, *res = survivedRobotsHealths(positions, 4, healths, 4, directions, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
