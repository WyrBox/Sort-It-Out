.globl outputproc
.type outputproc, @function

.section .data
formatstring:
    .ascii "%ld\n\0"

prologue:
    .ascii "These are the numbers in order from lowest to highest:\n\0"
    
.section .text
    .equ LIST_PTR, -8 # place in stack to pointer to current element in list
    .equ LIST_LEN_UNPRINT, -16 # place in stack for length of list left unprinted
    
outputproc:
    # allocate space for three local variables, but aligning stack to 16 bytes
    enter $16, $0

    # preserve list pointer and list length (unprinted) on stack
    movq %rdi, LIST_PTR(%rbp)
    movq %rsi, LIST_LEN_UNPRINT(%rbp)

    # print prologue
    movq stdout, %rdi
    movq $prologue, %rsi
    movq $0, %rax
    call fprintf

    # check if list is of size 1 or less
    movq LIST_LEN_UNPRINT(%rbp), %rcx
    cmpq $1, %rcx
    jbe return_to_main

    # put pointer to current list elem in %r10
    movq LIST_PTR(%rbp), %r10

outputproc_loop:
    # print numbers
    movq stdout, %rdi
    movq $formatstring, %rsi
    movq (%r10), %rdx
    movq $0, %rax
    call fprintf

    # decrement LIST_LEN_UNPRINT
    movq LIST_LEN_UNPRINT(%rbp), %rcx
    decq %rcx

    # check if number of unprinted numbers is zero, and jump to exit if so
    cmpq $0, %rcx
    je return_to_main

    # otherwise, put new number of unprinted numbers back in stack
    movq %rcx, LIST_LEN_UNPRINT(%rbp)

    # increment LIST_PTR to point to next number, and continue by using %r10 again for next loop (keeping the value in %r10)
    movq LIST_PTR(%rbp), %r10
    add $8, %r10
    movq %r10, LIST_PTR(%rbp)

    # jump to beginning of loop
    jmp outputproc_loop

return_to_main:
    # return success/failure value (assume success for now)
    movq $0, %rax

    leave
    ret
