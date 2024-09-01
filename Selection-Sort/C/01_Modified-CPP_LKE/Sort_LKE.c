#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Add n to list with current size size and max size max_size.
 */
int *addn(int *list, size_t *size, size_t *max_size, int n) {
    if(*size == *max_size) {
        *max_size *= 2;
        int *temp = realloc(list, *max_size * sizeof(int));
        if(temp == NULL) {
            printf("Memory allocation failed\n");
            free(list);
            exit(1);
        }
        else {
            list = temp;
        }
    }

    list[(*size)++] = n;
    return list;
}

/**
 * Check if current int overruns current buffer. If it does, keep it in overrun.
 * Otherwise good to add it to list of ints.
 */
int *handle_buffer(int last_int, int end_of_input, char *overrun, char *ptr, int *list, size_t *size, size_t *max_size, int n) {
    // End of buffer but not end of input is the case where the buffer needs to overrun
    if (last_int && !end_of_input) {
        // Store end of current buffer in overrun (overrun = ptr), and don't change list.
        memmove(overrun, ptr, strlen(ptr) + 1);
        return list;
    }
    else {
        // Empty overrun, and add n to list.
        overrun[0] = '\0';
        return addn(list, size, max_size, n);
    }
}

/**
 * Gets user input (integers separated by spaces on one line).
 */
int *get_input(int *list, size_t *size, size_t *max_size) {
    char buffer[100];
    int n;
    // Since user input can overrun buffer size, use a variable to store the overrun
    char overrun[2*sizeof(buffer)] = "";
    printf("Type a list of whole numbers separated by spaces: ");
    while(1) {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // fgets checks for EOF and errors including file not found/opened..
            printf("fgets found EOF or error\n"); 
            exit(1);
        }
        int end_of_input = (buffer[strlen(buffer) - 1] == '\n'); // Whether end of user input is in this buffer

        // Combine overrun with next buffer so can use it.
        char *ptr = strcat(overrun, buffer);
        while(sscanf(ptr, "%d", &n) == 1) {
            char *space = strchr(ptr, ' '); // Return pointer to next space after ptr
            int last_int = (space == NULL); // Whether ptr is pointing at the last int in the buffer
            list = handle_buffer(last_int, end_of_input, overrun, ptr, list, size, max_size, n);

            if (last_int) {
                break;
            }
            else {
                ptr = space + 1; // Move pointer to next int
            }
        }
        if(end_of_input) {
            break;
        }
    }

    return list;
}

/**
 * Simple driver for Sort: initialise a dynamic array, get input, sort it, and print it.
 */
int main() {
    int *list = NULL;
    size_t max_size = 5;
    size_t size = 0;
    list = malloc(max_size * sizeof(int));
    if(list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    list = get_input(list, &size, &max_size);

    list = Sort(list, size);

    for(size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}