#include <stdio.h>

int countPermutations(int* complexity, int complexitySize);
int factorial(int n);

int main() {
    int complexity[] = {1, 2, 3};
    printf("%d\n", countPermutations(complexity, 3));
    return 0;
}

int countPermutations(int* complexity, int complexitySize) {
    int rootComplexity = complexity[0];
    for (int i = 1; i < complexitySize; i++) {
        if (complexity[i] <= rootComplexity) {
            return 0;
        }
    }
    return factorial(complexitySize - 1);
}

int factorial(int n) {
    return n > 1 ? (long) n * factorial(n - 1) % 1000000007 : 1;
}
