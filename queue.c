#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // maximum size of queue

int queue[MAX];
int front = -1, rear = -1;

// Function to check if queue is empty
int isEmpty()
{
    return (front == -1 && rear == -1);
}

// Function to check if queue is full
int isFull()
{
    return (rear + 1) % MAX == front;
}

// Enqueue operation
void enqueue(int value)
{
    if (isFull())
    {
        printf("Queue Overflow! Cannot insert %d\n", value);
        return;
    }
    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }
    queue[rear] = value;
    printf("%d enqueued to queue.\n", value);
}

// Dequeue operation
void dequeue()
{
    if (isEmpty())
    {
        printf("Queue Underflow! Cannot dequeue.\n");
        return;
    }
    printf("%d dequeued from queue.\n", queue[front]);
    if (front == rear)
    {
        // only one element
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

// Peek (front element)
void peek()
{
    if (isEmpty())
    {
        printf("Queue is empty!\n");
    }
    else
    {
        printf("Front element: %d\n", queue[front]);
    }
}

// Display queue elements
void display()
{
    if (isEmpty())
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1)
    {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main()
{
    int choice, value;
    printf("hi");

    while (1)
    { // Infinite loop to keep the menu running
        printf("\n--- Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            peek();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
