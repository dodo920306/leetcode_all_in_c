#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool areSimilar(int** mat, int matSize, int* matColSize, int k);
void shiftLeft(int* arr, int size);
void shiftRight(int* arr, int size);

int main() {
    printf(areSimilar(
        (int*[]){
            (int[]){1, 2, 3}, 
            (int[]){4, 5, 6}, 
            (int[]){7, 8, 9}}, 
        3, 
        (int[]){3, 3, 3}, 
        4) ? "true\n" : "false\n");
    printf(areSimilar(
        (int*[]){
            (int[]){1, 2, 1, 2}, 
            (int[]){5, 5, 5, 5}, 
            (int[]){6, 3, 6, 3}}, 
        3, 
        (int[]){4, 4, 4}, 
        2) ? "true\n" : "false\n");
    return 0;
}

bool areSimilar(int** mat, int matSize, int* matColSize, int k) {
    k %= matColSize[0];
    int* tmp = (int*)malloc(matColSize[0] * sizeof(int));
    for (int i = 0; i < matSize; i++) {
        size_t size = matColSize[i] * sizeof(int);
        memcpy(tmp, mat[i], size);

        for (int j = 0; j < k; j++) {
            if (i % 2) {
                shiftLeft(mat[i], matColSize[i]);
            } else {
                shiftRight(mat[i], matColSize[i]);
            }
        }

        if (memcmp(tmp, mat[i], size)) {
            return false;
        }
    }
    free(tmp);
    return true;
}

void shiftLeft(int* arr, int size) {
    int tmp = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = tmp;
}

void shiftRight(int* arr, int size) {
    int tmp = arr[size - 1];
    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = tmp;
}
