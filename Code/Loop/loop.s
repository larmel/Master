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

	# http://www.baptiste-wicht.com/2011/11/print-strings-integers-intel-assembly/

	# Print address
	#leaq	-4(%rbp), %rax 	# Address of g
	#xorq	%rsi, %rsi 		# Count characters

	push    $97
	mov     $1, %rsi
	jmp .Lprint

	# Extract new character
.Lextract:
	cmpq    $0, %rax 		# Is address 0?
	jz .Lprint
	movq    %rax, %rbx 		# Copy of address
	andq	$15, %rbx 		# mod 16
	shrq	$4, %rax 		# divide by 16
	incq 	%rsi 			# i++

	# Push character code on stack
	cmpq	$10, %rbx 		# >= 10?. 'a' = 97. Add 87
	jl	.Lint
	addq    $87, %rbx
	pushq   %rbx
	jmp .Lextract
.Lint:
	addq    $48, %rbx 		# '0' = 48
	pushq   %rbx
	cmpq	$0, -16(%rbp)
	jne	.Lextract

	# Pop and print each character
.Lprint:
	#cmpq 	$0, %rsi
	#jz .Lexit
	#decq 	%rsi
	mov 	$4, %eax 		# Syscall sys_write
	mov 	$1, %ebx 		# File descriptor stdout
	#movq 	%rsp, %rcx      # Pointer to first char
	sub     $4, %esp
	mov     %esp, %ecx 
	mov 	$16, %edx 		# Message length
	int  	$0x80 			# OS interrupt
	#addq 	$8, %rsp        # Point to next character (64 bit, 8 byte)
	#jmp .Lprint

.Lexit:

	mov	$1, %eax	#system call number (sys_exit)
	int	$0x80		#call kernel

/*
	movl	$.LC0, %eax
	leaq	-4(%rbp), %rdx
	leaq	-8(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$0, %eax*/
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LOL:
	.string "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
