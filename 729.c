#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct event {
    int start, end;
    struct event *left, *right;
};

typedef struct {
    struct event *root;
} MyCalendar;

struct event *initEvent(int start, int end);
void freeEvent(struct event *root);
MyCalendar *myCalendarCreate();
bool myCalendarBook(MyCalendar *obj, int start, int end);
void myCalendarFree(MyCalendar *obj);

struct event *initEvent(int start, int end)
{
    struct event *node = (struct event *)malloc(sizeof(struct event));
    if (!node) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    node->start = start;
    node->end = end;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeEvent(struct event *root)
{
    if (!root)  return;

    freeEvent(root->left);
    freeEvent(root->right);
    free(root);
}

MyCalendar *myCalendarCreate()
{
    MyCalendar *res = (MyCalendar *)malloc(sizeof(MyCalendar));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    res->root = NULL;
    return res;
}

bool myCalendarBook(MyCalendar *obj, int start, int end)
{
    struct event *iter = obj->root;

    while (iter)
        if (iter->end <= start)
            if (iter->right)
                iter = iter->right;
            else
                return (iter->right = initEvent(start, end));
        else if (end <= iter->start)
            if (iter->left)
                iter = iter->left;
            else
                return (iter->left = initEvent(start, end));
        else
            return false;

    return (obj->root = initEvent(start, end));
}

void myCalendarFree(MyCalendar *obj)
{
    freeEvent(obj->root);
    free(obj);
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 
 * myCalendarFree(obj);
*/

int main()
{
    MyCalendar *myCalendar = myCalendarCreate();
    if (!myCalendar)    return -1;

    printf("[null");
    printf(", %s", myCalendarBook(myCalendar, 10, 20) ? "true" : "false");
    printf(", %s", myCalendarBook(myCalendar, 15, 25) ? "true" : "false");
    printf(", %s", myCalendarBook(myCalendar, 20, 30) ? "true" : "false");
    myCalendarFree(myCalendar);
    printf("]\n");
    return 0;
}
