.globl inputproc
.type inputproc, @function

.section .data
promptformat:
    .ascii "Enter a list of numbers each seperated by a new line\n\0"

scanformat:
    .ascii "%ld\0"

.section .text
    .equ LIST_PTR, -8 # place in stack to pointer to current element in list
    .equ LIST_LEN, -16 # place in stack to pointer to current length of list
    .equ LIST_MAX_LEN, -24 # place in stack to value of max length of list
    
inputproc:
    # allocate space for three local variables, but aligning stack to 16 bytes
    enter $32, $0

    # preserve %rdi (pointer to list space) in LIST_PTR, and %rsi (list max lenght) in LIST
    movq %rdi, LIST_PTR(%rbp)
    movq %rsi, LIST_MAX_LEN(%rbp)

    # initialise counter
    movq $0, LIST_LEN(%rbp)

    # show the prompt to stdout    
    movq stdout, %rdi
    movq $promptformat, %rsi
    movq $0, %rax
    call fprintf

inputloop:
    # request input
    movq stdin, %rdi
    movq $scanformat, %rsi
    movq LIST_PTR(%rbp), %rdx
    movq $0, %rax
    call fscanf

    # exit loop if fscanf returns EOF (-1 as signed) or if fscanf can't intake input (if return val is 0)
    movq $0xffffffff, %r10
    cmpq %r10, %rax
    jz exitinputloop

    movq $0, %r10
    cmpq %r10, %rax
    jz exitinputloop

    # add one to counter
    movq LIST_LEN(%rbp), %rcx
    inc %rcx
    movq %rcx, LIST_LEN(%rbp)

    # exit loop if all list memory taken
    movq LIST_MAX_LEN(%rbp), %rax
    cmpq %rax, LIST_LEN(%rbp)
    jge exitinputloop
    #jl exitinputloop

    # increment pointer in list of numbers to point to next number
    #movq $8, %rax
    addq $8, LIST_PTR(%rbp)
    
    
    # repeat input taking
    jmp inputloop

exitinputloop:
    # return length of list
    movq LIST_LEN(%rbp), %rax

    leave
    ret
