#include <stdio.h>

int main()
{
    int A[10] = {5, 10, 15, 20, 25, 30};
    int n = 6;

    // Insert 12 at index 2
    for (int i = n; i > 2; i--)
    {
        A[i] = A[i - 1];
    }
    A[2] = 12;
    n++;

    printf("After insertion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    // Delete element at index 4
    for (int i = 4; i < n - 1; i++)
    {
        A[i] = A[i + 1];
    }
    n--;

    printf("\nAfter deletion: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}
