    .section .text
    .globl main
main:
    mov $0x1234567, %eax 
    mov $0, %ebx
    /* LSD only works when three lea instructions are placed at the start.
       Probably some ICache limitations reached.
    */
    /*
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    */
    .p2align 3
.loop:
    cmp $0, %ebx
    je .l2
.l1:
    cmp $0, %ebx
    je .end
.l2:
    cmp $0, %ebx
    je .l1
.end:
    sub $1, %eax
    cmp $0, %eax
    jne .loop

    ret
