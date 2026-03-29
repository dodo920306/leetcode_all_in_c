#include <stdio.h>
#include <stdbool.h>

bool canBeEqual(char* s1, char* s2);

int main() {
    printf(canBeEqual("abcd", "cdab") ? "true\n" : "false\n");
    printf(canBeEqual("abcd", "dacb") ? "true\n" : "false\n");
    return 0;
}

bool canBeEqual(char* s1, char* s2) {
    return ((s1[0] == s2[0] && s1[2] == s2[2]) || 
            (s1[0] == s2[2] && s1[2] == s2[0])) && 
        ((s1[1] == s2[1] && s1[3] == s2[3]) || 
            (s1[1] == s2[3] && s1[3] == s2[1]));
}
