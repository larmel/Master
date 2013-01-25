
empty:
	nasm -f elf64 -F stabs empty.nasm
	ld empty.o
	rm empty.o

graph:
	../plot stat.dat instructions:u,cycles:u,cache-references:u,cache-misses:u,bus-cycles:u,cs | gnuplot -persist

clean:
	rm -f a.out
