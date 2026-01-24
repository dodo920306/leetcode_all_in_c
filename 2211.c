#include <stdio.h>

int countCollisions(char* directions);

int main() {
    printf("%d\n", countCollisions("RLRSLL"));
    return 0;
}

int countCollisions(char* directions) {
    int firstNotL = -1, lastNotR = -1;
    for (int i = 0; directions[i] != '\0'; i++) {
        if (directions[i] != 'L') {
            firstNotL = i;
            break;
        }
    }
    if (firstNotL == -1) {
        return 0;
    }
    for (int i = 0; directions[i] != '\0'; i++) {
        if (directions[i] != 'R') {
            lastNotR = i;
        }
    }
    if (lastNotR == -1) {
        return 0;
    }
    int res = 0;
    for (int i = firstNotL; i <= lastNotR; i++) {
        if (directions[i] != 'S') {
            res++;
        }
    }
    return res;
}
