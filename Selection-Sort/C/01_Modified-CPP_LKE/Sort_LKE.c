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
 * Simple driver for Sort: ask for a list, sort it, and print it.
 */
int main() {
    int *list = NULL;
    size_t max_size = 5;
    size_t size = 0;
    list = malloc(max_size * sizeof(int));
    if(list == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    char buffer[100];
    int n;
    // space for the overrun, initially an empty string
    char overrun[2*sizeof(buffer)] = "";
    printf("Type a list of whole numbers separated by spaces: ");
    while(1) {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // fgets checks for EOF and errors including file not found/opened..
            printf("fgets found EOF or error\n"); 
            return 1; 
        }
        int end_of_input = (buffer[strlen(buffer) - 1] == '\n');

        // concatenate buffer onto overrun - fixes issue of int being split
        char *ptr = strcat(overrun, buffer);
        while(sscanf(ptr, "%d", &n) == 1) {
            char *space = strchr(ptr, ' ');
            int last_int = (space == NULL);
            // if at end of incomplete buffer, set overrun = ptr
            if (last_int && !end_of_input) {
                memmove(overrun, ptr, strlen(ptr) + 1);
            }
            // otherwise can add this int to list, and reset overrun
            else {
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

                list[size++] = n;

                overrun[0] = '\0';
            }
            // if not at end of buffer, move pointer to next int
            if (!last_int) {
                ptr = space + 1;
            }
            // otherwise done
            else {
                break;
            }
        }
        if(end_of_input) {
            break;
        }
    }

    list = Sort(list, size);
    for(size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}