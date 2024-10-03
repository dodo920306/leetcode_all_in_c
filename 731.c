#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash/include/uthash.h"

struct bookingCount {
    int timing, count;
    UT_hash_handle hh;
};

typedef struct {
    struct bookingCount *map;
} MyCalendarTwo;

int cmp(const struct bookingCount *a, const struct bookingCount *b);
MyCalendarTwo *myCalendarTwoCreate();
bool myCalendarTwoBook(MyCalendarTwo *obj, int start, int end);
void myCalendarTwoFree(MyCalendarTwo *obj);

int cmp(const struct bookingCount *a, const struct bookingCount *b)
{
    return a->timing - b->timing;
}

MyCalendarTwo *myCalendarTwoCreate()
{
    MyCalendarTwo *res = (MyCalendarTwo *)malloc(sizeof(MyCalendarTwo));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed");
        return NULL;
    }

    res->map = NULL;
    return res;
}

bool myCalendarTwoBook(MyCalendarTwo *obj, int start, int end)
{
    struct bookingCount *startCount = NULL, *endCount = NULL;
    int overlappingBooking = 0;

    HASH_FIND_INT(obj->map, &start, startCount);
    HASH_FIND_INT(obj->map, &end, endCount);

    if (!startCount) {
        startCount = (struct bookingCount *)malloc(sizeof(struct bookingCount));
        if (!startCount) {
            fprintf(stderr, "Error: Memory Allocation Failed");
            return false;
        }
        startCount->timing = start;
        startCount->count = 0;
        HASH_ADD_INORDER(hh, obj->map, timing, sizeof(int), startCount, cmp);
    }
    if (!endCount) {
        endCount = (struct bookingCount *)malloc(sizeof(struct bookingCount));
        if (!endCount) {
            fprintf(stderr, "Error: Memory Allocation Failed");
            return false;
        }
        endCount->timing = end;
        endCount->count = 0;
        HASH_ADD_INORDER(hh, obj->map, timing, sizeof(int), endCount, cmp);
    }

    startCount->count++;
    endCount->count--;

    for (struct bookingCount *iter = obj->map; iter; iter = iter->hh.next) {
        overlappingBooking += iter->count;

        if (overlappingBooking > 2) {
            startCount->count--;
            endCount->count++;

            if (!(startCount->count)) {
                HASH_DEL(obj->map, startCount);
                free(startCount);
            }
            if (!(endCount->count)) {
                HASH_DEL(obj->map, endCount);
                free(endCount);
            }

            return false;
        }
    }

    return true;
}

void myCalendarTwoFree(MyCalendarTwo *obj)
{
    struct bookingCount *iter, *tmp;

    HASH_ITER(hh, obj->map, iter, tmp) {
        free(iter);
    }

    free(obj);
}

/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 
 * myCalendarTwoFree(obj);
*/

int main()
{
    MyCalendarTwo *myCalendarTwo;
    printf("[null");
    myCalendarTwo = myCalendarTwoCreate();
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 10, 20) ? "true" : "false");
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 50, 60) ? "true" : "false");
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 10, 40) ? "true" : "false");
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 5, 15) ? "true" : "false");
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 5, 10) ? "true" : "false");
    printf(", %s", myCalendarTwoBook(myCalendarTwo, 25, 55) ? "true" : "false");
    myCalendarTwoFree(myCalendarTwo);
    printf("]\n");
    return 0;
}
