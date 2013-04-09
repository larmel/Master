
CLFLAGS=-std=c99 -march=corei7 -O3
CCFLAGS=-std=c99 -march=native -O3

all: clang cc icc

.PHONY: all clang cc

clang:
	# Best offset: 0x30
	clang $(CLFLAGS) convolution.c 
	clang $(CLFLAGS) -S convolution.c -o convolution.clang.s
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out

cc:
	# Best offset: 0x30
	cc $(CCFLAGS) convolution.c
	cc $(CCFLAGS) -S convolution.c -o convolution.cc.s
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out

icc:
	# Best offset: 0xa0
	icc $(CCFLAGS) convolution.c
	icc $(CCFLAGS) -S convolution.c -o convolution.icc.s
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out
