#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int size;
    char *array;
};

struct Stack *create(int size);
void push(struct Stack *s, char c);
char pop(struct Stack *s);
void freeStack(struct Stack *s);
char* reverseParentheses(char* s);

struct Stack *create(int size)
{
    struct Stack *res;
    if (!(res = (struct Stack *)malloc(sizeof(struct Stack))) || !(res->array = (char *)malloc(size * sizeof(char))))
        return NULL;
    res->size = 0;
    return res;
}

void push(struct Stack *s, char c)
{
    s->array[s->size++] = c;
}

char pop(struct Stack *s)
{
    return s->array[--s->size];
}

void freeStack(struct Stack *s)
{
    free(s->array);
    free(s);
}

char *reverseParentheses(char *s)
{
    struct Stack *l, *r;
    int size = strlen(s);
    char t;
    if (!(l = create(size)) || !(r = create(size)))
        return NULL;
    for (int i = 0; i < size; i++) {
        if (s[i] == ')') {
            t = pop(l);
            while (t != '(') {
                push(r, t);
                t = pop(l);
            }
            for (int j = 0; j < r->size; j++)
                push(l, r->array[j]);
            r->size = 0;
        }
        else
            push(l, s[i]);
    }
    strncpy(s, l->array, l->size);
    s[l->size] = '\0';
    freeStack(l);
    freeStack(r);
    return s;
}

int main()
{
    char s[] = "(ed(et(oc))el)";
    printf("%s\n", reverseParentheses(s));
    return 0;
}
