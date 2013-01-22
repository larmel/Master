

mem:
	cc mem.c -Wall -o mem

empty:
	nasm -f elf64 -F stabs empty.nasm
	ld -o empty empty.o

clean:
	rm stat.*
	rm mem
	rm hello
	rm *.o

