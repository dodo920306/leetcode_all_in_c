#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct dequeNode {
    int value;
    struct dequeNode *next, *prev;
};

typedef struct {
    int size, maximumSize;
    struct dequeNode *root;
} MyCircularDeque;

bool myCircularDequeIsEmpty(MyCircularDeque* obj);
bool myCircularDequeIsFull(MyCircularDeque* obj);
MyCircularDeque *myCircularDequeCreate(int k);
bool myCircularDequeInsertFront(MyCircularDeque *obj, int value);
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value);
bool myCircularDequeDeleteFront(MyCircularDeque* obj);
bool myCircularDequeDeleteLast(MyCircularDeque *obj);
int myCircularDequeGetFront(MyCircularDeque* obj);
int myCircularDequeGetRear(MyCircularDeque* obj);
void myCircularDequeFree(MyCircularDeque *obj);

bool myCircularDequeIsEmpty(MyCircularDeque* obj)
{
    return !(obj->size);
}

bool myCircularDequeIsFull(MyCircularDeque* obj)
{
    return (obj->size == obj->maximumSize);
}

MyCircularDeque *myCircularDequeCreate(int k)
{
    MyCircularDeque *res = (MyCircularDeque *)malloc(sizeof(MyCircularDeque));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Error.");
        return NULL;
    }

    res->root = (struct dequeNode *)malloc(sizeof(struct dequeNode));
    if (!(res->root)) {
        fprintf(stderr, "Error: Memory Allocation Error.");
        return NULL;
    }

    res->size = 0;
    res->maximumSize = k;
    res->root->value = 0;
    res->root->next = res->root;
    res->root->prev = res->root;
    return res;
}

bool myCircularDequeInsertFront(MyCircularDeque *obj, int value)
{
    if (myCircularDequeIsFull(obj)) return false;

    struct dequeNode *newNode = (struct dequeNode *)malloc(sizeof(struct dequeNode));
    if (!newNode) {
        fprintf(stderr, "Error: Memory Allocation Error.");
        return false;
    }

    newNode->value = value;
    newNode->next = obj->root->next;
    newNode->prev = obj->root;
    obj->root->next = newNode;
    newNode->next->prev = newNode;
    obj->size++;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value)
{
    if (myCircularDequeIsFull(obj)) return false;

    struct dequeNode *newNode = (struct dequeNode *)malloc(sizeof(struct dequeNode));
    if (!newNode) {
        fprintf(stderr, "Error: Memory Allocation Error.");
        return false;
    }

    newNode->value = value;
    newNode->next = obj->root;
    newNode->prev = obj->root->prev;
    obj->root->prev = newNode;
    newNode->prev->next = newNode;
    obj->size++;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) return false;

    struct dequeNode *deleteNode = obj->root->next;
    obj->root->next = deleteNode->next;
    deleteNode->next->prev = obj->root;
    free(deleteNode);
    obj->size--;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque *obj)
{
    if (myCircularDequeIsEmpty(obj)) return false;

    struct dequeNode *deleteNode = obj->root->prev;
    obj->root->prev = deleteNode->prev;
    deleteNode->prev->next = obj->root;
    free(deleteNode);
    obj->size--;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) return -1;

    return obj->root->next->value;
}

int myCircularDequeGetRear(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) return -1;

    return obj->root->prev->value;
}

void myCircularDequeFree(MyCircularDeque *obj)
{
    while ((myCircularDequeDeleteFront(obj)) && (myCircularDequeDeleteLast(obj)));
    free(obj->root);
    free(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 
 * bool param_3 = myCircularDequeDeleteFront(obj);
 
 * bool param_4 = myCircularDequeDeleteLast(obj);
 
 * int param_5 = myCircularDequeGetFront(obj);
 
 * int param_6 = myCircularDequeGetRear(obj);
 
 * bool param_7 = myCircularDequeIsEmpty(obj);
 
 * bool param_8 = myCircularDequeIsFull(obj);
 
 * myCircularDequeFree(obj);
*/

int main()
{
    printf("[");
    MyCircularDeque *myCircularDeque = myCircularDequeCreate(3);
    printf("null");
    printf(", %s", myCircularDequeInsertLast(myCircularDeque, 1) ? "true" : "false");
    printf(", %s", myCircularDequeInsertLast(myCircularDeque, 2) ? "true" : "false");
    printf(", %s", myCircularDequeInsertFront(myCircularDeque, 3) ? "true" : "false");
    printf(", %s", myCircularDequeInsertFront(myCircularDeque, 4) ? "true" : "false");
    printf(", %d", myCircularDequeGetRear(myCircularDeque));
    printf(", %s", myCircularDequeIsFull(myCircularDeque) ? "true" : "false");
    printf(", %s", myCircularDequeDeleteLast(myCircularDeque) ? "true" : "false");
    printf(", %s", myCircularDequeInsertFront(myCircularDeque, 4) ? "true" : "false");
    printf(", %d", myCircularDequeGetFront(myCircularDeque));
    myCircularDequeFree(myCircularDeque);
    printf("]\n");
    return 0;
}
