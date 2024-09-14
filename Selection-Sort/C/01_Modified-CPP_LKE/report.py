import mymodule
import numpy
import time

numpy.random.seed() # default seed is system time

# warm up lol
listx = numpy.random.randint(-1000, 1000, 65536, numpy.int32)
sorted_list, sort_time = mymodule.c_sort(listx)

listx = numpy.random.randint(-1000, 1000, 65536, numpy.int32)
sorted_list, sort_time = mymodule.c_sort(listx)
print(f"C selection sort time taken: {sort_time}")
print(f"At least it works:", numpy.array_equal(sorted_list, sorted(listx)))

listx = numpy.random.randint(-1000, 1000, 65536, numpy.int32)
start_time = time.perf_counter()
sorted_list = list(sorted(listx))
end_time = time.perf_counter()

listx = numpy.random.randint(-1000, 1000, 65536, numpy.int32)
start_time = time.perf_counter()
sorted_list = list(sorted(listx))
end_time = time.perf_counter()
print(f"Python built-in sort time taken: {end_time - start_time}")