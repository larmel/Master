	.file	"align.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	movl	$0, %r14d
	.cfi_offset 3, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	movl	$1, %r12d
	movl	$1, %ebx
	movl	$42, %r13d
	addl	%ebx, %r13d
	jmp	.L7
.L10:
	nop
.L7:
	addl	$1, %r12d
	addl	$1, %ebx
	cmpl	%ebx, %r12d
	jne	.L8
.L2:
	cmpl	%r13d, %ebx
	je	.L9
.L4:
	cmpl	$-1, %r14d
	je	.L5
	addl	$1, %r14d
	addl	$1, %r12d
	addl	$1, %ebx
	addl	$42, %r13d
.L5:
	cmpl	$305419896, %r14d
	jne	.L10
	jmp	.L3
.L8:
	nop
	jmp	.L3
.L9:
	nop
.L3:
	movl	$0, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
