#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct stack {
    int *arr, size;
};

bool isOperator(char);
int OperatorToFunction(char, int, int);
void push(struct stack *self, int k);
bool isEmpty(struct stack *self);
struct stack *new(int size);
struct stack *_diffWaysToCompute(char *expression, int length);

void printIntArray(int *, int);

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*';
}

int OperatorToFunction(char c, int x, int y)
{
    switch (c) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        default:
            return INT_MIN;
    }
}

void push(struct stack *self, int k)
{
    self->arr[self->size] = k;
    self->size++;
}

bool isEmpty(struct stack *self)
{
    return !(self->size);
}

struct stack *new(int size)
{
    struct stack *res = (struct stack *)malloc(sizeof(struct stack));
    if (!res) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    res->arr = (int *)malloc(size * sizeof(int));
    if (!(res->arr)) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    res->size = 0;
    return res;
}

struct stack *_diffWaysToCompute(char *expression, int length)
{
    struct stack *res = new(10000), *_res1, *_res2;
    int tmp;

    if (!res) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < length; i++) {

        if (isOperator(expression[i])) {
            _res1 = _diffWaysToCompute(expression, i);
            _res2 = _diffWaysToCompute(expression + i + 1, length - i - 1);

            for (int j = 0; j < _res1->size; j++)
                for (int k = 0; k < _res2->size; k++)
                    push(res, OperatorToFunction(expression[i], _res1->arr[j], _res2->arr[k]));
            free(_res1->arr);
            free(_res1);
            free(_res2->arr);
            free(_res2);
        }
    }

    if (isEmpty(res)) {
        sscanf(expression, "%d", &tmp);
        push(res, tmp);
    }

    return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *diffWaysToCompute(char *expression, int *returnSize)
{
    struct stack *_res = NULL;
    int *res;

    _res = _diffWaysToCompute(expression, strlen(expression));
    *returnSize = _res->size;
    res = _res->arr;

    free(_res);
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
    char *expression = "2-1-1";
    int returnSize = 0, *res = diffWaysToCompute(expression, &returnSize);
    printIntArray(res, returnSize);
    return 0;
}
