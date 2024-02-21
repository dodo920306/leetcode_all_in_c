#include <stdio.h>
#include <stdlib.h>

struct pair {
    int key, value;
};

struct heap {
	struct pair *arr;
	int size;
	int capacity;
};

struct heap* createHeap(int capacity);
void insertHelper(struct heap *h, int index);
void heapify(struct heap *h, int index);
struct pair peek(struct heap *h);
struct pair extractMin(struct heap *h);
void insert(struct heap *h, int key, int value);
void printHeap(struct heap *h);
void freeHeap(struct heap *h);

struct heap *createHeap(int capacity)
{
	struct heap *h = (struct heap *)malloc(sizeof(struct heap));
	if (!h) {
		perror("Error");
		return NULL;
	}

	h->size = 0;
	h->capacity = capacity;

	h->arr = (struct pair *)malloc(capacity * sizeof(struct pair));
	if (!(h->arr)) {
		perror("Error");
		return NULL;
	}

	return h;
}

void insertHelper(struct heap *h, int index)
{
    struct pair temp;
	int parent = (index - 1) / 2;

	if (h->arr[parent].key > h->arr[index].key || (h->arr[parent].key == h->arr[index].key && h->arr[parent].value > h->arr[index].value)) {
		temp = h->arr[parent];
		h->arr[parent] = h->arr[index];
		h->arr[index] = temp;
		insertHelper(h, parent);
	}
}

/* Maintain the subtree whose root is on the index. */
void heapify(struct heap *h, int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int min = index;
	struct pair temp;

	if (left >= h->size || left < 0)    left = -1;
	if (right >= h->size || right < 0)  right = -1;

	if ((left != -1) && ((h->arr[left].key < h->arr[index].key) || (h->arr[left].key == h->arr[index].key && h->arr[left].value < h->arr[index].value)))
        min = left;
	if ((right != -1) && ((h->arr[right].key < h->arr[min].key) || (h->arr[right].key == h->arr[min].key && h->arr[right].value < h->arr[min].value)))
        min = right;

	if (min != index) {
		temp = h->arr[min];
		h->arr[min] = h->arr[index];
		h->arr[index] = temp;

		heapify(h, min);
	}
}

struct pair peek(struct heap *h)
{
	struct pair deleteItem = {INT_MIN, INT_MIN};
	return h->size ? h->arr[0] : deleteItem;
}

struct pair extractMin(struct heap *h)
{
	struct pair deleteItem = {INT_MIN, INT_MIN};

	if (h->size) {
		deleteItem = h->arr[0];

		h->arr[0] = h->arr[h->size - 1];
		h->size--;

		heapify(h, 0);
	}
	return deleteItem;
}

void insert(struct heap *h, int key, int value)
{
	if (h->size < h->capacity) {
		h->arr[h->size].key = key;
        h->arr[h->size].value = value;
		insertHelper(h, h->size);
		h->size++;
	}
	else if ((2 * h->capacity) <= INT_MAX) {
		h = realloc(h, 2 * h->capacity);
		h->capacity <<= 1;
		insert(h, key, value);
	}
}

void printHeap(struct heap *h)
{
	for (int i = 0; i < h->size; i++)
		printf("(%d, %d) ", h->arr[i].key, h->arr[i].value);
	printf("\n");
}

void freeHeap(struct heap *h)
{
	free(h->arr);
	free(h);
}

int main()
{
	int arr[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	struct heap *hp = createHeap(9);
    for (int i = 0; i < 9; i++)
        insert(hp, arr[i], 0);

    for (int i = 0; i < 9; i++)
	    printf("%d ", extractMin(hp).key);

	freeHeap(hp);
	return 0;
}
