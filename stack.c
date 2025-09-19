#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // maximum size of stack

int stack[MAX];
int top = -1;

// Check if stack is empty
int isEmpty()
{
    return top == -1;
}

// Check if stack is full
int isFull()
{
    return top == MAX - 1;
}

// Push operation
void push(int value)
{
    if (isFull())
    {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    stack[++top] = value;
    printf("%d pushed to stack.\n", value);
}

// Pop operation
void pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow! Cannot pop.\n");
        return;
    }
    printf("%d popped from stack.\n", stack[top--]);
}

// Peek (Top element)
void peek()
{
    if (isEmpty())
    {
        printf("Stack is empty!\n");
    }
    else
    {
        printf("Top element: %d\n", stack[top]);
    }
}

// Display stack elements
void display()
{
    if (isEmpty())
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = top; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
