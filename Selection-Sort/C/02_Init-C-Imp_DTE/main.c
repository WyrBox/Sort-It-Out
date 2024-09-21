#include <stdio.h>

#define MAX_SIZE 100  // Define the maximum size for the array

// Function to perform Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // Outer loop - iterate over each element in the array
    for (i = 0; i < n - 1; i++) {
        // Assume the first unsorted element is the minimum. e.g. if first number entered is 10 then counts 10 as the minimum.
        min_idx = i;

        // Inner loop - find the minimum element in the unsorted portion of the array
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element of the unsorted portion
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;

    // Loop through the array and print each element
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");  // Print a new line at the end
}

int main() {
    int n, i;

    // Prompt the user to enter the number of elements
    printf("Enter the number of elements (max %d): ", MAX_SIZE);
    scanf("%d", &n);

    // Check if the input size exceeds the maximum allowed size
    if (n > MAX_SIZE) {
        printf("Number of elements exceeds the maximum allowed size of %d.\n", MAX_SIZE);
        return 1;  // Exit the program if the input size is too large
    }

    int arr[MAX_SIZE];  // Declare an array of fixed size MAX_SIZE

    // Prompt the user to enter the elements of the array
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);  // Read each element into the array
    }

    // Print the unsorted array
    printf("Unsorted array: \n");
    printArray(arr, n);

    // Call the selectionSort function to sort the array
    selectionSort(arr, n);

    // Print the sorted array
    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;  // End the program
}








