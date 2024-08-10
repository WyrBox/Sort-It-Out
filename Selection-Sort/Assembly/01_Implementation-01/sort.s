###########################
# Jaimin L. Symonds Patel #
# 2024-08-03_Sat          #
###########################

# Program to sort a list of numbers
# that are simply stored in memory
# in the program, and then written
# to standard output.

# The sorting algorithm that is
# used is the selection sort
# algorithm.

# define _start symbol
.globl _start

# define data
.section .data
# how many elements we have:
numberOfElems:
    .quad 10

# the list of numbers to sort:
elems:
    .quad 10, 9, 8, 7, 6, 5, 4, 3, 2, 1

.section .text
_start:
    ### INITIALISE REGISTERS
    # use %r8 as size of sub-list
    movq numberOfElems, %r8

    # put number of elems in %rcx
    movq %r8, %rcx

    # use %rdi to hold the current largest value
    # (last elem in sub-list)
    movq elems-8(,%r8,8), %rdi

    # use %r9 to hold address of largest value
    movq $0, %r9

    ### CHECK PRECONDITIONS
    
    # if there are no numbers, or 1 number in list, stop:
    cmp $1, %r8
    jbe exit

find_largest_elem:

    # start at last sub-list elem and put val in rax:
    movq elems-8(,%rcx,8), %rax

    # if it is not bigger, then jump to find_largest_elem_loop
    cmpq %rdi, %rax
    jbe find_largest_elem_loop

    # otherwise store the largest value and remember mem address
    movq %rax, %rdi
    leaq elems-8(,%rcx,8), %r9

find_largest_elem_loop:
    # go back until all the sub-list is checked (rcx is zero):
    loopq find_largest_elem

swap_largest_elem:
    # move last elem in sub-list into %rax
    movq elems-8(,%r8,8), %rax

    # move largest val %rdi into last elem position of sub-list
    movq %rdi, elems-8(,%r8,8)

    # move last elem in sub-list to where largest val was
    movq %rax, (%r9)

loop_sub_lists:
    # reduce sub-list size
    decq %r8
    
    # make counter same size as sub list:
    movq %r8, %rcx

    # check if sub-list size is 1
    cmp $1, %r8
    jbe exit

    # set largest value as last elem in sub-list
    movq elems-8(,%r8,8), %rdi

    # otherwise, jump to next sub-list largest value search
    jmp find_largest_elem

exit:
    movq $0x3c, %rax
    movq $0, %rdi
    syscall
