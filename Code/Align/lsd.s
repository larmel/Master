	.file	"align.c"
	.text
	.globl	main
	.type	main, @function
# 916,523,820 cycles:u                  #    0.000 GHz                    
#                 0 r0120:u                                                     
#     3,054,197,919 r01a8:u                
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6

	mov $0, %r10d

.l0:
	cmp %rax, %rbx
	jne .l1
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
.l1:
	add $0x7, %r9d
	mov %rax, %rbx
	cmp %rbx, %rcx
	jne .l2

.l2:
	add $0x1, %r10d
	add $0x9, %r8d
	add $0x1, %esi
	add $0x1, %rcx
	cmp $0x12345678, %r10d
	jl .l0

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
