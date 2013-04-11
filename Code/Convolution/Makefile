
CLFLAGS=-std=c99 -march=corei7 -O3
CCFLAGS=-std=c99 -march=native -O3

all: clang cc icc

.PHONY: all clang cc graph graph-all

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

stat.csv:
	./run-offsets

stat.all.csv:
	../lperf -i 0 -a 1 --repeat 4 -n 100 -o stat.all.csv ./convolution > /dev/null

graph-all: stat.all.csv
	../lplot -l 'upper right' -t 'Array Offset' -e 'cycles:u,r01a2:u,r02a3:u,r025c:u,r013c:u,r003c:u,r04a3:u,r05a3:u,r8108:u' stat.all.csv

graph: stat.csv
	../lplot -l 'upper right' -t 'Array Offset' stat.csv
