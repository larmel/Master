
.PHONY: lperf

lperf:
	./lperf-min Loop/loop -n 10 -r 2 \
		--environment-offset 3200 --environment-increment 1

	./lperf-min Loop/loop -e cycles:u,instructions:u -n 10


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

