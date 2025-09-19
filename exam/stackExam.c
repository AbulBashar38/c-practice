#include <stdio.h>
#include <ctype.h>

#define MAX 20

char stack[MAX];
int top = -1;

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if (top == -1)
        return -1;
    return stack[top--];
}

int precedence(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return -1;
}

int main()
{
    char exp[] = "(A+B)*(C-D)/E";
    char *e = exp, x;

    printf("Infix: %s\nPostfix: ", exp);
    while (*e != '\0')
    {
        if (isalnum(*e))
        {
            printf("%c", *e);
        }
        else if (*e == '(')
        {
            push(*e);
        }
        else if (*e == ')')
        {
            while ((x = pop()) != '(')
                printf("%c", x);
        }
        else
        {
            while (precedence(stack[top]) >= precedence(*e))
                printf("%c", pop());
            push(*e);
        }
        e++;
    }

    while (top != -1)
    {
        printf("%c", pop());
    }
    printf("\n");
    return 0;
}
