#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct CharStack {
    int size;
    char array[1800];
};

struct Stack {
    int size;
    int array[4];
};

bool isDigit(char c);
bool isLetter(char c);
char *decodeString(char *s);

bool isDigit(char c)
{
    c -= '0';
    return c >= 0 && c < 10;
}

bool isLetter(char c)
{
    c -= 'a';
    return c >= 0 && c < 26;
}

char *decodeString(char *s)
{
    /**
     * l is used to record decoded chars and encoded chars 
     * that haven't been encoded
     * while r, on the other hand, is used to store chars 
     * that are about to be decoded now.
     */
    struct CharStack *l, *r;
    struct Stack *stack;
    int length = strlen(s);
    char *res;
    if (!(l = (struct CharStack *)calloc(1, sizeof(struct CharStack))) || !(r = (struct CharStack *)calloc(1, sizeof(struct CharStack))) || !(stack = (struct Stack *)calloc(1, sizeof(struct Stack))))
        return NULL;
    for (int i = 0; i < length; i++)
        /**
         * push: stack->array[stack->size++] = ...;
         * pop: ... = stack->array[--stack->size];
         */
        if (isDigit(s[i])) {
            /* read the number */
            sscanf(s + i, "%d", &stack->array[stack->size++]);
            /* jump across the number */
            while (isDigit(s[i + 1]))   i++;
        }
        else if (isLetter(s[i]) || s[i] == '[')
            /* read letters and '[' */
            l->array[l->size++] = s[i];
        else {
            /**
             * s[i] must be ']'.
             * 
             * find the string between this ']' and the last '[',
             * pop it, and push it into r
             */
            while (l->array[--l->size] != '[')
                r->array[r->size++] = l->array[l->size];
            r->size--;
            for (int k = stack->array[--stack->size]; k; k--)
                /* push r into l for k times */
                for (int temp = r->size; temp >= 0; temp--)
                    /* pop r and push it into l */
                    l->array[l->size++] = r->array[temp];
            r->size = 0;
        }
    free(r);
    free(stack);
    if (!(res = (char *)calloc(l->size + 1, sizeof(char))))
        return NULL;
    strncpy(res, l->array, l->size);
    free(l);
    return res;
}

int main()
{
    char *res = decodeString("3[a2[c]]");
    printf("%s\n", res);
    free(res);
    return 0;
}
