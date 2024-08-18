#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * This function implements a naive selection sort algorithm,
 * in ascending order. Some simple optimisations, if they can be called that. 
 */
int *Sort(int *list, size_t size) {
    /// The number of elements that are already sorted, and the index of the first unsorted element.
    size_t sorted = 0;

    // Sort. Simple optimisation: The last element to be sorted is the biggest and doesn't need to move.
    while (size > sorted + 1) {
        // Find the minimum unsorted element - by index.
        size_t idx = sorted;
        // Simple optimisation: Start from the next element (ok as a consequence of sorted < size - 1)
        for (size_t i = sorted + 1; i < size; i++) {
            if (list[i] < list[idx]) {
                idx = i;
            }
        }

        // Swap the minimum unsorted element into place. Simple optimisation: Don't swap if already in the right place.
        if (idx > sorted) {
            int temp = list[idx];
            list[idx] = list[sorted];
            list[sorted] = temp;
        }
        sorted++;
    }

    return list;
}

/**
 * Simple driver for Sort: ask for a list, sort it, and print it.
 */
int main() {
    // Get input
    int *list = NULL;
    size_t max_size = 5;
    size_t size = 0;
    list = malloc(max_size * sizeof(int));
    if(list == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int input;
    printf("Type a list of whole numbers separated by spaces (enter a non-numerical character to end input): ");
    while(scanf("%d", &input) > 0) {
        if(size == max_size) {
            max_size *= 2;
            int *temp = realloc(list, max_size * sizeof(int));
            if(temp == NULL) {
                printf("Memory allocation failed\n");
                free(list);
                return 1;
            }
            else {
                list = temp;
            }
        }

        list[size++] = input;
        // at the end of every loop including the last one, size is 1 more than the last array index, which is correct
    }
    clearerr(stdin);
    int c;
    while(c = getchar() != '\n' && c != EOF);

    // (aside: test input is working)
    printf("Test: Enter another number\n");
    scanf("%d", &input);
    printf("%d\n", input);

    // Sort and print list
    list = Sort(list, size);
    for(size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}