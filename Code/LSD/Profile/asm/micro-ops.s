    .section    .text
    .globl  main
main:
    mov $0x1234567, %eax

    /* Insert x amount of add isntructions, + 3 for loop logic
       */

    .p2align 5
.loop:
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    add %ebx, %ecx
    sub $1, %eax
    cmp $0, %eax
    jne .loop

    ret
