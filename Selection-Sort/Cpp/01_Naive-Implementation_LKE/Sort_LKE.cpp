#include <vector>

#include <iostream>
#include <iterator>
#include <algorithm>

/**
 * This function implements a naive selection sort algorithm,
 * in ascending order. Some simple optimisations, if they can be called that. 
 */
std::vector<int> Sort(std::vector<int> list) {
    /// The number of elements that are already sorted, and the index of the first unsorted element.
    std::size_t sorted{ 0 };

    // Sort. Simple optimisation: The last element to be sorted is the biggest and doesn't need to move.
    while (list.size() > sorted + 1) {
        // Find the minimum unsorted element - by index.
        std::size_t idx = sorted;
        // Simple optimisation: Start from the next element (ok as a consequence of sorted < list.size() - 1)
        for (std::size_t i{ sorted + 1 }; i < list.size(); i++) {
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
    // Ask for it
    std::cout << "Type a list of whole numbers separated by spaces: ";
    std::istream_iterator<int> begin(std::cin), end;
    std::vector<int> list(begin, end);

    // Sort it
    list = Sort(list);

    // Print it
    std::copy(list.begin(), list.end(), std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}