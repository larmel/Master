	.file	"loop.c"
	.local	i
	.comm	i,4,4
	.local	j
	.comm	j,4,4
	.local	k
	.comm	k,4,4
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
	movl	$0, -8(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L2
.L3:
	movl	i(%rip), %eax
	addl	-4(%rbp), %eax
	movl	%eax, i(%rip)
	movl	j(%rip), %eax
	addl	-4(%rbp), %eax
	movl	%eax, j(%rip)
	movl	k(%rip), %eax
	addl	-4(%rbp), %eax
	movl	%eax, k(%rip)
	addl	$1, -8(%rbp)
.L2:
	cmpl	$65535, -8(%rbp)
	jle	.L3

	leaq	-4(%rbp), %rax 	# Address of g
	call write_address

	leaq	-8(%rbp), %rax 	# Address of inc
	call write_address

	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

	# Writes address in rax in human readable format
	# http://stackoverflow.com/questions/10105871/why-cant-i-sys-write-from-a-register
write_address:
	mov     $0, %rbx		# Count characters on stack
	pushq	$0x0a			# Line feed
.push:
	cmpq    $0, %rax
	jz .print
	movq    %rax, %rcx 		# Copy of address
	andq	$15, %rcx 		# Char
	shrq	$4, %rax 		# Shift
	incq 	%rbx 			# i++
	cmpq	$10, %rcx 		# Compare to 10
	jl	.int
	addq    $87, %rcx 		# a-f
	pushq   %rcx
	jmp .push
.int:
	addq    $48, %rcx 		# 0-9
	pushq   %rcx
	jmp	.push
.print:
	cmpq 	$0, %rbx
	jl .exit
	decq 	%rbx
	movq	$1, %rdx		# String length
	leaq	(%rsp), %rsi	# Start address
	movq	$1, %rax
	movq 	$1, %rdi
	syscall
	addq	$8, %rsp
	jmp .print
.exit:
	ret

.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
