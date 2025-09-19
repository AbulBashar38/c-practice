#include <stdio.h>

#define MAX 100

// Traversal
void traverse(int arr[], int n)
{
    printf("Array elements: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Insertion
int insert(int arr[], int n, int pos, int value)
{
    if (n == MAX)
    {
        printf("Array is full! Cannot insert.\n");
        return n;
    }
    if (pos < 0 || pos > n)
    {
        printf("Invalid position!\n");
        return n;
    }
    for (int i = n; i > pos; i--)
    {
        arr[i] = arr[i - 1]; // shift right
    }
    arr[pos] = value;
    return n + 1;
}

// Deletion
int delete(int arr[], int n, int pos)
{
    if (pos < 0 || pos >= n)
    {
        printf("Invalid position!\n");
        return n;
    }
    for (int i = pos; i < n - 1; i++)
    {
        arr[i] = arr[i + 1]; // shift left
    }
    return n - 1;
}

// Linear Search
int linearSearch(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// Update
void update(int arr[], int n, int pos, int value)
{
    if (pos < 0 || pos >= n)
    {
        printf("Invalid position!\n");
        return;
    }
    arr[pos] = value;
}

int main()
{
    int arr[MAX], n, choice, pos, value, key, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    while (1)
    {
        printf("\n--- Array Menu ---\n");
        printf("1. Traverse\n2. Insert\n3. Delete\n4. Search\n5. Update\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            traverse(arr, n);
            break;
        case 2:
            printf("Enter position (0-based) and value: ");
            scanf("%d %d", &pos, &value);
            n = insert(arr, n, pos, value);
            break;
        case 3:
            printf("Enter position (0-based): ");
            scanf("%d", &pos);
            n = delete(arr, n, pos);
            break;
        case 4:
            printf("Enter value to search: ");
            scanf("%d", &key);
            result = linearSearch(arr, n, key);
            if (result != -1)
                printf("Element found at index %d\n", result);
            else
                printf("Element not found\n");
            break;
        case 5:
            printf("Enter position (0-based) and new value: ");
            scanf("%d %d", &pos, &value);
            update(arr, n, pos, value);
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
