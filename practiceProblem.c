#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------- ARRAY ----------------------------
void arraySimple()
{
    int A[10] = {10, 20, 30, 40, 60};
    int n = 5;
    printf("Before insertion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    for (int i = n; i > 2; i--)
        A[i] = A[i - 1];
    A[2] = 50;
    n++;

    printf("\nAfter insertion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void arrayMedium()
{
    int A[10] = {5, 10, 15, 20, 25, 30};
    int n = 6;

    // Insert 12 at index 2
    for (int i = n; i > 2; i--)
        A[i] = A[i - 1];
    A[2] = 12;
    n++;
    printf("After insertion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    // Delete element at index 4
    for (int i = 4; i < n - 1; i++)
        A[i] = A[i + 1];
    n--;
    printf("\nAfter deletion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// ---------------------------- BINARY SEARCH ----------------------------
void binarySearchSimple()
{
    int A[] = {5, 10, 15, 20, 25, 30, 35};
    int low = 0, high = 6, mid, target = 25;

    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("low=%d, high=%d, mid=%d\n", low, high, mid);
        if (A[mid] == target)
        {
            printf("Found %d at index %d\n", target, mid);
            return;
        }
        else if (A[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    printf("Element not found\n");
}

void binarySearchMedium()
{
    int A[] = {3, 8, 12, 17, 25, 30, 42, 56};
    int targets[2] = {30, 40};

    for (int t = 0; t < 2; t++)
    {
        int low = 0, high = 7, mid, target = targets[t];
        printf("Searching for %d:\n", target);
        while (low <= high)
        {
            mid = (low + high) / 2;
            printf("low=%d, high=%d, mid=%d\n", low, high, mid);
            if (A[mid] == target)
            {
                printf("Found %d at index %d\n", target, mid);
                break;
            }
            else if (A[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        if (low > high)
            printf("%d not found\n", target);
        printf("\n");
    }
}

// ---------------------------- STACK ----------------------------
#define MAX 10
int stack[MAX], top = -1;

void push(int x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = x;
    printf("After Push(%d): ", x);
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

void pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return;
    }
    top--;
    printf("After Pop(): ");
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

void stackSimple()
{
    push(5);
    push(10);
    push(15);
    pop();
    push(20);
}

// ---------------------------- INFIX TO POSTFIX ----------------------------
char stack2[MAX];
int top2 = -1;

void push2(char c) { stack2[++top2] = c; }
char pop2() { return stack2[top2--]; }
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return -1;
}

void infixToPostfix()
{
    char infix[] = "(A+B)*(C-D)/E";
    char postfix[50];
    int k = 0;
    printf("Infix: %s\n", infix);

    for (int i = 0; i < strlen(infix); i++)
    {
        char c = infix[i];
        if ((c >= 'A' && c <= 'Z'))
            postfix[k++] = c;
        else if (c == '(')
            push2(c);
        else if (c == ')')
        {
            while (top2 != -1 && stack2[top2] != '(')
                postfix[k++] = pop2();
            pop2();
        }
        else
        {
            while (top2 != -1 && precedence(stack2[top2]) >= precedence(c))
                postfix[k++] = pop2();
            push2(c);
        }
        printf("Stack: ");
        for (int j = 0; j <= top2; j++)
            printf("%c ", stack2[j]);
        printf("\n");
    }
    while (top2 != -1)
        postfix[k++] = pop2();
    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

// ---------------------------- QUEUE ----------------------------
int queue[MAX], front = 0, rear = -1;

void enqueue(int x)
{
    if (rear == MAX - 1)
    {
        printf("Queue Overflow\n");
        return;
    }
    queue[++rear] = x;
    printf("After Enqueue(%d): ", x);
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

void dequeue()
{
    if (front > rear)
    {
        printf("Queue Underflow\n");
        return;
    }
    front++;
    printf("After Dequeue(): ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

void queueSimple()
{
    enqueue(5);
    enqueue(10);
    enqueue(15);
    dequeue();
}

void queueMedium()
{
    int init[] = {7, 9, 11};
    front = 0;
    rear = -1;
    for (int i = 0; i < 3; i++)
        enqueue(init[i]);

    enqueue(13);
    enqueue(15);
    dequeue();
    enqueue(20);
    dequeue();
}

// ---------------------------- LINKED LIST ----------------------------
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int val)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = val;
    n->next = NULL;
    return n;
}

void printList(Node *head)
{
    while (head)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void linkedListSimple()
{
    Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    printf("Before: ");
    printList(head);

    Node *newNode = createNode(15);
    newNode->next = head->next;
    head->next = newNode;

    printf("After: ");
    printList(head);
}

void linkedListMedium()
{
    Node *head = createNode(5);
    head->next = createNode(12);
    head->next->next = createNode(18);
    head->next->next->next = createNode(25);

    // Insert 20 after 18
    Node *temp = head;
    while (temp && temp->data != 18)
        temp = temp->next;
    Node *newNode = createNode(20);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("After inserting 20: ");
    printList(head);

    // Delete node with value 12
    temp = head;
    Node *prev = NULL;
    while (temp && temp->data != 12)
    {
        prev = temp;
        temp = temp->next;
    }
    if (prev)
        prev->next = temp->next;
    else
        head = head->next;
    free(temp);
    printf("After deleting 12: ");
    printList(head);
}

// ---------------------------- MAIN ----------------------------
int main()
{
    printf("===== Array Simple =====\n");
    arraySimple();
    printf("\n===== Array Medium =====\n");
    arrayMedium();

    printf("\n===== Binary Search Simple =====\n");
    binarySearchSimple();
    printf("\n===== Binary Search Medium =====\n");
    binarySearchMedium();

    printf("\n===== Stack Simple =====\n");
    stackSimple();
    printf("\n===== Infix to Postfix (Medium) =====\n");
    infixToPostfix();

    printf("\n===== Queue Simple =====\n");
    queueSimple();
    printf("\n===== Queue Medium =====\n");
    queueMedium();

    printf("\n===== Linked List Simple =====\n");
    linkedListSimple();
    printf("\n===== Linked List Medium =====\n");
    linkedListMedium();

    return 0;
}