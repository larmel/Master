;
; Program with no overhead whatsoever
;  build: nasm -f elf64 -F stabs name.asm
;  link:  ld -o name name.o
;
section .data 

section .text
global _start
_start:
	mov     rax, 1 ; specify sys_exit function code (from OS vector table)
	mov     rbx, 0 ; specify return code for OS (0 = everything's fine)
	int     80h    ; tell kernel to perform system call

