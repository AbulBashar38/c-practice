#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// ---------------- STACK FOR CHAR ----------------
char stack[MAX];
int top = -1;

void push(char c)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

char peek()
{
    return stack[top];
}

int isEmpty()
{
    return top == -1;
}

// ---------------- STACK FOR STRING ----------------
char strStack[MAX][MAX];
int strTop = -1;

void pushStr(char *str)
{
    strcpy(strStack[++strTop], str);
}

char *popStr()
{
    return strStack[strTop--];
}

// ----------------- Precedence --------------------
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    return -1;
}

// ---------------- INFIX TO POSTFIX ----------------
void infixToPostfix(char *infix, char *postfix)
{
    int k = 0;
    for (int i = 0; i < strlen(infix); i++)
    {
        char c = infix[i];
        if (isalnum(c))
            postfix[k++] = c;
        else if (c == '(')
            push(c);
        else if (c == ')')
        {
            while (!isEmpty() && peek() != '(')
                postfix[k++] = pop();
            pop();
        }
        else
        {
            while (!isEmpty() && precedence(peek()) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (!isEmpty())
        postfix[k++] = pop();
    postfix[k] = '\0';
}

// ---------------- INFIX TO PREFIX ----------------
void reverseStr(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix)
{
    char rev[MAX], temp[MAX];
    strcpy(rev, infix);
    reverseStr(rev);

    // swap brackets
    for (int i = 0; i < strlen(rev); i++)
    {
        if (rev[i] == '(')
            rev[i] = ')';
        else if (rev[i] == ')')
            rev[i] = '(';
    }

    infixToPostfix(rev, temp);
    reverseStr(temp);
    strcpy(prefix, temp);
}

// ---------------- POSTFIX TO INFIX ----------------
void postfixToInfix(char *postfix, char *infix)
{
    for (int i = 0; i < strlen(postfix); i++)
    {
        char c = postfix[i];
        if (isalnum(c))
        {
            char op[2] = {c, '\0'};
            pushStr(op);
        }
        else
        {
            char op2[MAX], op1[MAX], exp[MAX];
            strcpy(op2, popStr());
            strcpy(op1, popStr());
            sprintf(exp, "(%s%c%s)", op1, c, op2);
            pushStr(exp);
        }
    }
    strcpy(infix, popStr());
}

// ---------------- PREFIX TO INFIX ----------------
void prefixToInfix(char *prefix, char *infix)
{
    int n = strlen(prefix);
    for (int i = n - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if (isalnum(c))
        {
            char op[2] = {c, '\0'};
            pushStr(op);
        }
        else
        {
            char op1[MAX], op2[MAX], exp[MAX];
            strcpy(op1, popStr());
            strcpy(op2, popStr());
            sprintf(exp, "(%s%c%s)", op1, c, op2);
            pushStr(exp);
        }
    }
    strcpy(infix, popStr());
}

// ---------------- POSTFIX TO PREFIX ----------------
void postfixToPrefix(char *postfix, char *prefix)
{
    for (int i = 0; i < strlen(postfix); i++)
    {
        char c = postfix[i];
        if (isalnum(c))
        {
            char op[2] = {c, '\0'};
            pushStr(op);
        }
        else
        {
            char op2[MAX], op1[MAX], exp[MAX];
            strcpy(op2, popStr());
            strcpy(op1, popStr());
            sprintf(exp, "%c%s%s", c, op1, op2);
            pushStr(exp);
        }
    }
    strcpy(prefix, popStr());
}

// ---------------- PREFIX TO POSTFIX ----------------
void prefixToPostfix(char *prefix, char *postfix)
{
    int n = strlen(prefix);
    for (int i = n - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if (isalnum(c))
        {
            char op[2] = {c, '\0'};
            pushStr(op);
        }
        else
        {
            char op1[MAX], op2[MAX], exp[MAX];
            strcpy(op1, popStr());
            strcpy(op2, popStr());
            sprintf(exp, "%s%s%c", op1, op2, c);
            pushStr(exp);
        }
    }
    strcpy(postfix, popStr());
}

// ---------------- MAIN ----------------
int main()
{
    char infix[MAX] = "(A+B)*(C-D)/E";
    char postfix[MAX], prefix[MAX], result[MAX];

    printf("Infix Expression: %s\n", infix);

    infixToPostfix(infix, postfix);
    printf("Infix to Postfix: %s\n", postfix);

    infixToPrefix(infix, prefix);
    printf("Infix to Prefix: %s\n", prefix);

    postfixToInfix(postfix, result);
    printf("Postfix to Infix: %s\n", result);

    prefixToInfix(prefix, result);
    printf("Prefix to Infix: %s\n", result);

    postfixToPrefix(postfix, result);
    printf("Postfix to Prefix: %s\n", result);

    prefixToPostfix(prefix, result);
    printf("Prefix to Postfix: %s\n", result);

    return 0;
}
