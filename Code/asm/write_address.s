	# Writes contents of rax in human readable format
	# http://stackoverflow.com/questions/10105871/why-cant-i-sys-write-from-a-register
write_address:
	mov     $0, %rbx		# Count characters on stack
	pushq	$0x20			# Space
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
write_char:
	pushq	%rax
	movq	$1, %rdx		# String length
	leaq	(%rsp), %rsi	# Start address
	movq	$1, %rax
	movq 	$1, %rdi
	syscall
	addq	$8, %rsp
	ret