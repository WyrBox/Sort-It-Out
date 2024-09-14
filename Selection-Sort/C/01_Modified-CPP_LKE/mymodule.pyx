from libc.stdlib cimport malloc, free
from libc.stdint cimport int32_t
from libc.string cimport memcpy

import numpy

cdef extern from "./Sort_LKE.h":
    int *Sort(int *list, size_t size)

def c_sort(int32_t[:] list): 
    cdef size_t size = list.shape[0]
    cdef int *c_list = <int *>malloc((size+1) * sizeof(int))

    # Convert Python list to C array
    for i in range(size):
        c_list[i] = list[i]
    c_list[size] = 0

    Sort(c_list, size)  # Call the C Sort function

    # Convert C array back to Python list
    sorted_list = numpy.empty(size, dtype=numpy.int32)
    for i in range(size):
        sorted_list[i] = c_list[i]
    time_taken = c_list[size]/1000000 # ... and grab the time taken
    
    free(c_list)  # Free the allocated memory
    return (sorted_list, time_taken)
