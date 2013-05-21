	.section	.text
	.globl	main
main:
	mov $0x1234567, %rax 
	mov $0, %rbx
	.p2align 5

.loop:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l1
.l1:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l2
	nop
	nop
.l2:
	xor %rbx, %rbx
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l3

.l3:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l4
.l4:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l5
	nop
	nop
.l5:
	xor %rbx, %rbx
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l6

.l6:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l7
.l7:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l8
	nop
	nop
.l8:
	xor %rbx, %rbx
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l9

.l9:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l10
.l10:
	xor %rbx, %rbx
	cmpq $0, %rbx
	je .l11
	nop
	nop
	
.l11:
	subq $1, %rax
	cmpq $0, %rax
	jne	.loop

	ret
