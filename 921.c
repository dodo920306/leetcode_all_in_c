#include <stdio.h>

int minAddToMakeValid(char *);

int minAddToMakeValid(char *s)
{
    int numOfLeftParenthesis = 0, numOfRightParenthesis = 0;
    for (int i = 0; s[i]; i++)
        if (s[i] == '(')    numOfLeftParenthesis++;
        else
            if (numOfLeftParenthesis)   numOfLeftParenthesis--;
            else    numOfRightParenthesis++;

    return numOfLeftParenthesis + numOfRightParenthesis;
}

int main()
{
    printf("%d\n", minAddToMakeValid("()))"));
    return 0;
}
