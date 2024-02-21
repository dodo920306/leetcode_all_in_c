#include <stdio.h>
#include <stdlib.h>

struct pair {
    long key;
    int value;
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
void insert(struct heap *h, long key, int value);
void freeHeap(struct heap *h);
int mostBooked(int n, int **meetings, int meetingsSize, int *meetingsColSize);

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

void insert(struct heap *h, long key, int value)
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

void freeHeap(struct heap *h)
{
	free(h->arr);
	free(h);
}

int mostBooked(int n, int **meetings, int meetingsSize, int *meetingsColSize)
{
    struct heap *sort, *idle, *busy;
    struct pair meeting;
    int *rooms = (int *)calloc(n, sizeof(int)), res = 0;
    if (!rooms) {
        perror("Error");
        return -1;
    }
    sort = createHeap(meetingsSize);
    for (int i = 0; i < meetingsSize; i++) insert(sort, meetings[i][0], meetings[i][1]);
    idle = createHeap(n);
    for (int i = 0; i < n; i++) insert(idle, i, 0);
    busy = createHeap(n);
    for (int i = 0, room; i < meetingsSize; i++) {
        meeting = extractMin(sort);
        while (busy->size && peek(busy).key <= meeting.key)
            insert(idle, extractMin(busy).value, 0);
        if (idle->size) {
            room = extractMin(idle).key;
            rooms[room]++;
            insert(busy, meeting.value, room);
        }
        else {
            room = peek(busy).value;
            rooms[room]++;
            insert(busy, extractMin(busy).key + meeting.value - meeting.key, room);
        }
    }
    for (int i = 0; i < n; i++) if (rooms[res] < rooms[i]) res = i;
    free(rooms);
    freeHeap(sort);
    freeHeap(idle);
    freeHeap(busy);
    return res;
}

int main()
{
    int **meetings = (int **)malloc(4 * sizeof(int *)), meetingsColSize[] = {2, 2, 2, 2};
    for (int i = 0; i < 4; i++)
        meetings[i] = (int *)malloc(2 * sizeof(int));
    meetings[0][0] = 0;
    meetings[0][1] = 10;
    meetings[1][0] = 1;
    meetings[1][1] = 5;
    meetings[2][0] = 2;
    meetings[2][1] = 7;
    meetings[3][0] = 3;
    meetings[3][1] = 4;
    printf("%d", mostBooked(2, meetings, 4, meetingsColSize));
    return 0;
}
