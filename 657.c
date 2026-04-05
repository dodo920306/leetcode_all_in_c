#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool judgeCircle(char* moves);

int main() {
    printf(judgeCircle("UD") ? "true" : "false");
    printf("\n");
    printf(judgeCircle("LL") ? "true" : "false");
    printf("\n");
    return 0;
}

bool judgeCircle(char* moves) {
    int verticalDelta = 0;
    int horizontalDelta = 0;
    int length = strlen(moves);
    for (int i = 0; i < length; i++) {
        switch (moves[i]) {
            case 'U':
                verticalDelta++;
                break;
            case 'D':
                verticalDelta--;
                break;
            case 'L':
                horizontalDelta--;
                break;
            case 'R':
                horizontalDelta++;
        }
    }
    return !verticalDelta && !horizontalDelta;
}
