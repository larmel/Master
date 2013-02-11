
empty:
	nasm -f elf64 -F stabs empty.nasm
	ld empty.o
	rm empty.o

stat:
	../perfrun.py -e cycles:u -n 40 -r 1 ./a.out

graph:
	../plot.py -e cycles:u,r02a3:u,r0107:u,r40a1:u,r04a2:u,r01a1:u,r01a2:u,r80a1:u,r0203:u

clean:
	rm -f a.out
