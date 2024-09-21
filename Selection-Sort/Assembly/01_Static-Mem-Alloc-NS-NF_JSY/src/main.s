.globl main

.section .bss
list:
    # reserve enough space for 10 quadwords containing the list of numbers to sort
    .zero LIST_MAX_MEM
listLength:
    .zero 8

.section .text
.equ LIST_MAX_LEN, 5
.equ LIST_MAX_MEM, LIST_MAX_LEN*8

main:
    # align the stack
    enter $16, $0

    # call the inputproc function to retrieve the list of numbers to sort
    leaq list, %rdi
    movq $LIST_MAX_LEN, %rsi
    call inputproc

    # store output of inputproc
    movq %rax, listLength

    # check if output is zero, and exit if so
    cmpq $0, %rax
    je exit

    #call selsort with inputs
    leaq list, %rdi
    movq listLength, %rsi
    call selsort

    # store ouput of selsort (return value of success or failure)
    # (not needed for now since we assume success, if input is valid)

    #call outputproc with inputs
    leaq list, %rdi
    movq listLength, %rsi
    call outputproc

    # outputproc returns success or failure
    # (not needed for now since we assume success)

    # return exit code of zero
    movq $0, %rax

exit:
    leave
    ret
