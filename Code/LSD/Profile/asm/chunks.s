    .section    .text
    .globl  main
main:
    mov $0x1234567, %eax 
    mov $0, %ebx

    /* Start of block compare and jump occupying 5 byte
       32 - 5 = 26 byte dead code 
       Start loop on 32 byte alignment - 5 bits
       */

    .p2align 5
.l0:
    cmp $0, %ebx
    je .l1
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l1:
    cmp $0, %ebx
    je .l2
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l2:
    cmp $0, %ebx
    je .l3
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l3:
    cmp $0, %ebx
    je .l4
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l4:
    cmp $0, %ebx
    je .l5
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l5:
    cmp $0, %ebx
    je .l6
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l6:
    cmp $0, %ebx
    je .l7
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l7:
    cmp $0, %ebx
    je .l8
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l8:
    cmp $0, %ebx
    je .l9
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l9:
    cmp $0, %ebx
    je .l10
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l10:
    cmp $0, %ebx
    je .l11
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx
.l11:
    /* Final block, sub, cmp and jne takes 3+3+6 = 12 bytes 
       32-12 = 20 bytes dead code max
    */
    lea 0x100(%rsp), %ecx
    lea 0x100(%rsp), %ecx
    add $0x100, %ecx;
    sub $1, %eax
    cmp $0, %eax
    jne .l0

    ret
