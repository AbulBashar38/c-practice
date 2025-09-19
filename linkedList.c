#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node *next;
};

struct Node *createNewNode(int val)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void addAtFirst(struct Node **head_ref, int val)
{
    struct Node *newNode = createNewNode(val);
    newNode->next = *head_ref;
    *head_ref = newNode;
}

void addAtLast(struct Node **head_ref, int val)
{
    struct Node *newNode = createNewNode(val);

    if (head_ref == NULL)
    {
        *head_ref = newNode;
        return;
    }

    struct Node *temp = *head_ref;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void addAfter(struct Node *prev, int val)
{

    if (prev == NULL)
    {
        printf("Previous Node is Null\n");
        return;
    }

    struct Node *newNode = createNewNode(val);
    newNode->next = prev->next;
    prev->next = newNode;
}

void deleteNode(struct Node **head_ref, int val)
{

    struct Node *current = *head_ref;
    struct Node *prev = NULL;

    if (current != NULL && current->val == val)
    {
        *head_ref = current->next;
        free(current);
        printf("%d is deleted from List\n", val);
        return;
    }

    while (current != NULL && current->val != val)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("%d is not found in List\n", val);
        return;
    }

    prev->next = current->next;

    free(current);
    printf("%d is deleted from the list\n", val);
}

void reversedList(struct Node **head)
{
    struct Node *current = *head;
    struct Node *prev = NULL;
    struct Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}
void printList(struct Node *head)
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

void deleteGraterThenValue(struct Node **head_ref, int val)
{

    struct Node *current = *head_ref;
    struct Node *prev = NULL;

    while (current != NULL)
    {

        if (current->val >= val)
        {
            if (prev == NULL)
            {
                *head_ref = current->next;
                free(current);
                current = *head_ref;
            }
            else
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

void findMiddle(struct Node *head_ref)
{
    struct Node *fast = head_ref;
    struct Node *slow = head_ref;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    if (slow != NULL)
        printf("%d is the middle Value\n", slow->val);
}

struct Node *mergeSortedLists(struct Node *l1, struct Node *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    struct Node *result = NULL;

    if (l1->val <= l2->val)
    {
        result = l1;
        result->next = mergeSortedLists(l1->next, l2);
    }
    else
    {
        result = l2;
        result->next = mergeSortedLists(l1, l2->next);
    }
    return result;
}

void removeDuplicates(struct Node *head)
{
    struct Node *current = head;

    while (current != NULL && current->next != NULL)
    {
        if (current->val == current->next->val)
        {
            struct Node *dup = current->next;
            current->next = dup->next;
            free(dup);
        }
        else
        {
            current = current->next;
        }
    }
}

void insertAtPosition(struct Node **head_ref, int index, int value)
{
    struct Node *newNode = createNewNode(value);

    // Case 1: Insert at head
    if (index == 0)
    {
        newNode->next = *head_ref;
        *head_ref = newNode;
        return;
    }

    struct Node *temp = *head_ref;
    int count = 0;

    // Traverse until one node before target index
    while (temp != NULL && count < index - 1)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
    {
        printf("Index out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtPosition(struct Node **head_ref, int index)
{
    if (*head_ref == NULL)
        return;

    struct Node *temp = *head_ref;

    // Case 1: delete head
    if (index == 0)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // Find previous node of the one to be deleted
    for (int i = 0; temp != NULL && i < index - 1; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Index out of range!\n");
        return;
    }

    struct Node *toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}
int isPalindrome(struct Node *head)
{
    if (head == NULL || head->next == NULL)
        return 1;

    // Step 1: Find middle
    struct Node *slow = head, *fast = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse second half
    struct Node *prev = NULL, *current = slow->next, *next;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // Step 3: Compare halves
    struct Node *firstHalf = head;
    struct Node *secondHalf = prev;
    while (secondHalf != NULL)
    {
        if (firstHalf->val != secondHalf->val)
            return 0; // not palindrome
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    return 1; // palindrome
}

int main()
{

    struct Node *head = NULL;

    addAtFirst(&head, 10);
    addAtFirst(&head, 20);
    addAtFirst(&head, 30);
    addAtFirst(&head, 40);
    addAtLast(&head, 2);
    printList(head);
    deleteNode(&head, 90);
    printList(head);
    reversedList(&head);
    addAfter(head->next, 80);
    printf("revers List: \n");
    printList(head);
    findMiddle(head);
    deleteGraterThenValue(&head, 30);
    printf("remove value Greater then 30: \n");
    printList(head);
    return 0;
}