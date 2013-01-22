
; program with no overhead whatsoever
section .data 

section .text
global _start
_start:
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     ecx, 5
	mov     edx, 6
	mov     eax, 1 ; specify sys_exit function code (from OS vector table)
	mov     ebx, 0 ; specify return code for OS (0 = everything's fine)
	int     80h    ; tell kernel to perform system call

