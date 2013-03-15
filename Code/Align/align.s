	.file	"align.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	movl	$0, %r13d
	.cfi_offset 3, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	movl	$1, %ebx
	movl	$1, %r12d
	jmp	.L2
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
.L13:
	cmpl	%r12d, %ebx
	je	.L3
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L3:
	cmpl	%r12d, %ebx
	je	.L4
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L4:
	cmpl	%r12d, %ebx
	je	.L5
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L5:
	cmpl	%r12d, %ebx
	je	.L6
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L6:
	cmpl	%r12d, %ebx
	je	.L7
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L7:
	cmpl	%r12d, %ebx
	je	.L8
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L8:
	cmpl	%r12d, %ebx
	je	.L9
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L9:
	cmpl	%r12d, %ebx
	je	.L10
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L10:
	cmpl	%r12d, %ebx
	je	.L11
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L11:
	cmpl	%r12d, %ebx
	je	.L12
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L12:
	cmpl	%r12d, %ebx
	je	.L2
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
	movl	%r12d, %ebx
.L2:
	cmpl	$305419895, %r13d
	setle	%al
	addl	$1, %r13d
	testb	%al, %al
	jne	.L13
	movl	%r13d, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	loop, .-loop
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	loop
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
