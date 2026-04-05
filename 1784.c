#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkOnesSegment(char* s);

int main() {
    printf(checkOnesSegment("1001") ? "true" : "false");
    printf("\n");
    printf(checkOnesSegment("110") ? "true" : "false");
    printf("\n");
    return 0;
}

bool checkOnesSegment(char* s) {
    /* Since s[0] = 1, if there is a "01" in s,
     * s = 1X01Y with X and Y as arbitrary bits.
     * Thus, s has at least two contiguous segment of 1s.
     * 
     * On the other hand, if there is no "01" in s,
     * s = X or X0 with X as arbitrary length of 1s.
     * Therefore, s has at most one contiguous segment of 1s.
     */
    return !strstr(s, "01");
}
