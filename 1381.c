#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, capacity, *arr;
} CustomStack;

CustomStack *customStackCreate(int maxSize);
void customStackPush(CustomStack *obj, int x);
int customStackPop(CustomStack *obj);
void customStackIncrement(CustomStack *obj, int k, int val);
void customStackFree(CustomStack *obj);

CustomStack *customStackCreate(int maxSize)
{
    CustomStack *res = (CustomStack *)malloc(sizeof(CustomStack));
    if (!res)   return NULL;

    res->arr = (int *)malloc(maxSize * sizeof(int));
    if (!(res->arr))    return NULL;

    res->size = 0;
    res->capacity = maxSize;
    return res;
}

void customStackPush(CustomStack *obj, int x)
{
    if (obj->size != obj->capacity)
        obj->arr[(obj->size)++] = x;
}

int customStackPop(CustomStack *obj)
{
    if (!(obj->size))   return -1;

    (obj->size)--;
    return obj->arr[obj->size];
}

void customStackIncrement(CustomStack *obj, int k, int val)
{
    if (obj->size < k)  k = obj->size;

    for (int i = 0; i < k; i++)
        (obj->arr)[i] += val;
}

void customStackFree(CustomStack *obj)
{
    free(obj->arr);
    free(obj);
}

/**
 * Your CustomStack struct will be instantiated and called as such:
 * CustomStack* obj = customStackCreate(maxSize);
 * customStackPush(obj, x);
 
 * int param_2 = customStackPop(obj);
 
 * customStackIncrement(obj, k, val);
 
 * customStackFree(obj);
*/

int main()
{
    printf("[");
    CustomStack *stk = customStackCreate(3); // Stack is Empty []
    printf("null");
    customStackPush(stk, 1); // stack becomes [1]
    printf(", null");
    customStackPush(stk, 2); // stack becomes [1, 2]
    printf(", null");
    printf(", %d", customStackPop(stk)); // return 2 --> Return top of the stack 2, stack becomes [1]
    customStackPush(stk, 2); // stack becomes [1, 2]
    printf(", null");
    customStackPush(stk, 3); // stack becomes [1, 2, 3]
    printf(", null");
    customStackPush(stk, 4); // stack still [1, 2, 3], Do not add another elements as size is 4
    printf(", null");
    customStackIncrement(stk, 5, 100); // stack becomes [101, 102, 103]
    printf(", null");
    customStackIncrement(stk, 2, 100); // stack becomes [201, 202, 103]
    printf(", null");
    printf(", %d", customStackPop(stk)); // return 103 --> Return top of the stack 103, stack becomes [201, 202]
    printf(", %d", customStackPop(stk)); // return 202 --> Return top of the stack 202, stack becomes [201]
    printf(", %d", customStackPop(stk)); // return 201 --> Return top of the stack 201, stack becomes []
    printf(", %d", customStackPop(stk)); // return -1 --> Stack is empty return -1.
    customStackFree(stk);
    printf("]\n");
    return 0;
}
