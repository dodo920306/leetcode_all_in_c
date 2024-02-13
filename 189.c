#include <stdio.h>
#include <stdlib.h>

/* Byte-wise swap two items of size SIZE. */
/* This macro comes from https://sourceware.org/git/?p=glibc.git;a=blob_plain;f=stdlib/qsort.c;hb=6d7e8eda9b85b08f207a6dc6f187e94e4817270f */
#define SWAP(a, b, size)                          \
    do {									      \
        size_t __size = (size);				      \
        char *__a = (a), *__b = (b);		      \
        do {								      \
            char __tmp = *__a;					  \
            *__a++ = *__b;						  \
            *__b++ = __tmp;						  \
        } while (--__size > 0);					  \
    } while (0)

void rotate(int* nums, int numsSize, int k);

int main()
{
    int nums[7] = {1, 2, 3, 4, 5, 6, 7}, numsSize = 7, k = 3;
    rotate(nums, numsSize, k);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    
}

void rotate(int* nums, int numsSize, int k){
    void *begin_ptr = nums, *end_ptr = nums + numsSize;
    
    for (int i = 0; i < k; i++) {
        end_ptr -= sizeof(int);
        SWAP(begin_ptr, end_ptr, sizeof(int));
        begin_ptr += sizeof(int);
    }
}
