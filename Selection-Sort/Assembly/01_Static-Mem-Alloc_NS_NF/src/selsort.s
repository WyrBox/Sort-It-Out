.globl selsort
.type selsort, @function

.section .text
    # set positions on stack for particular variables
    .equ LIST_PTR, -8
    .equ LIST_LEN, -16

selsort:
    # %rdi will contain the ptr to the list, and %rsi will contain the list length
    enter $16, $0
    movq %rdi, LIST_PTR(%rbp)
    movq %rsi, LIST_LEN(%rbp)

    # use %r8 as size of sub-list, initially same as the total number of elems
    movq LIST_LEN(%rbp), %r8

    # %rcx to hold the number of elemsin sublist as a counter (starting at the end of the list)
    movq %r8, %rcx

    # %rsi to hold pointer to list
    movq LIST_PTR(%rbp), %rsi

    # use %rdi to hold the current largest value (initially last elem of whole list)
    movq -8(%rsi,%r8,8), %rdi

    # use %r9 to hold the address of the largest value (initially last elem of whole list)
    leaq -8(%rsi,%r8,8), %r9

    ### check preconditions
    # if ther are no numbers , or 1 number in list, stop
    cmpq $1, %r8
    jbe return_to_main

find_largest_elem:
    # start at last sub-list elem and put value in %rax
    movq -8(%rsi,%rcx,8), %rax

    # if this elem is not largest, then jump to find_largest_elem_loop
    cmpq %rdi, %rax
    jbe find_largest_elem_loop

    # otherwise, stor the largest value and remember mem address
    movq %rax, %rdi
    leaq -8(%rsi,%rcx,8), %r9

find_largest_elem_loop:
    # go back until all sub-list is checked (%rcx is zero)
    loopq find_largest_elem

swap_largest_elem:
    # move last elem in sub-list into %rax
    movq -8(%rsi,%r8,8), %rax

    # move largest value found (%rdi) into the last elem position of sub-list
    movq %rdi, -8(%rsi,%r8,8)

    # move last elem of sub-list to where largest elem was
    movq %rax, (%r9)

loop_sub_lists:
    # reduce sub-list size
    decq %r8

    # make counter same size as sub-list
    movq %r8, %rcx

    # check if sub-list size is 1
    cmpq $1, %r8
    jbe return_to_main

    # otherwise set the largest value as the largest elem in new sub-list
    movq -8(%rsi,%r8,8), %rdi

    # %r9 to hold the address of the largest value (init last elem of sub-list)
    leaq -8(%rsi,%r8,8), %r9

    # jump to next sub-list searching step to find further largest value
    jmp find_largest_elem

return_to_main:
    # return pointer to list
    movq %rsi, %rax
    
    leave
    ret
