#include <stdio.h>

void binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1, mid;

    printf("\nSearching for %d:\n", key);
    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("low=%d high=%d mid=%d\n", low, high, mid);

        if (arr[mid] == key)
        {
            printf("Element %d found at index %d\n", key, mid);
            return;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    printf("Element %d not found\n", key);
}

int main()
{
    int arr[] = {3, 8, 12, 17, 25, 30, 42, 56};
    int n = sizeof(arr) / sizeof(arr[0]);

    binarySearch(arr, n, 30);
    binarySearch(arr, n, 40);

    return 0;
}
