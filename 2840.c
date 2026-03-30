#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkStrings(char* s1, char* s2);

int main() {
    printf(checkStrings("abcdba", "cabdab") ? "true\n" : "false\n");
    printf(checkStrings("abe", "bea") ? "true\n" : "false\n");
    return 0;
}

bool checkStrings(char* s1, char* s2) {
    int s1EvenCharSet[26];
    int s1OddCharSet[26];
    int s2EvenCharSet[26];
    int s2OddCharSet[26];

    for (int i = 0; i < 26; i++) {
        s1EvenCharSet[i] = 0;
        s1OddCharSet[i] = 0;
        s2EvenCharSet[i] = 0;
        s2OddCharSet[i] = 0;
    }

    int n = strlen(s1);
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            s1OddCharSet[s1[i] - 'a']++;
            s2OddCharSet[s2[i] - 'a']++;
        } else {
            s1EvenCharSet[s1[i] - 'a']++;
            s2EvenCharSet[s2[i] - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (s1OddCharSet[i] != s2OddCharSet[i] || 
            s1EvenCharSet[i] != s2EvenCharSet[i]) {
            return false;
        }
    }
    return true;
}
