;
; This program runs in 32-bit protected mode.
;  build: nasm -f elf -F stabs name.asm
;  link:  ld -o name name.o
;
; In 64-bit protected mode you can use 64-bit registers (e.g. rax instead of eax, rbx instead of ebx, etc..)
; Also change "-f elf " for "-f elf64" in build command.
;
section .data                           ; section for initialized data
str:     db 'Hello world!', 0Ah         ; message string with new-line char at the end (10 decimal)
str_len: equ $ - str                    ; calcs length of string (bytes) by subtracting this' address ($ symbol) 
                                            ; from the str's start address
 
section .text                           ; this is the code section
global _start                           ; _start is the entry point and needs global scope to be 'seen' by the 
                                            ; linker -    equivalent to main() in C/C++
_start:                                 ; procedure start
        mov     eax, 4                   ; specify the sys_write function code (from OS vector table)
        mov     ebx, 1                   ; specify file descriptor stdout -in linux, everything's treated as a file, 
                                             ; even hardware devices
        mov     ecx, str                 ; move start _address_ of string message to ecx register
        mov     edx, str_len             ; move length of message (in bytes)
        int     80h                      ; tell kernel to perform the system call we just set up - 
                                             ; in linux services are requested through the kernel
        mov     eax, 1                   ; specify sys_exit function code (from OS vector table)
        mov     ebx, 0                   ; specify return code for OS (0 = everything's fine)
        int     80h                      ; tell kernel to perform system call
