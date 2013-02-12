
empty:
	nasm -f elf64 -F stabs empty.nasm
	ld empty.o
	rm empty.o

stat:
	../perfrun.py -e cycles:u,branch-misses,cache-misses,r0107:u,r0280,r01a2:u -n 500 -r 100 -i 0 ./a.out
	#../perfrun.py -e cycles:u,r8108,r01a2:u -n 500 -r 1 ./a.out

graph:
	../plot.py -e cycles:u

clean:
	rm -f a.out
