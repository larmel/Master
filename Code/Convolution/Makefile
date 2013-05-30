
CLFLAGS=-std=c99 -march=corei7 -O3
CCFLAGS=-std=c99 -march=native -O3

all: perf-compilers

.PHONY: perf-compilers graph graph-all



# Default O3 only
conv-O3-gcc: convolution-simple.c
	gcc -O3 $+ -o $@

# Plotting a few offsets on O3 with GCC
bin/offsets-O3-gcc.csv: conv-O3-gcc
	../lperf ./$+ -e cycles:u,r0107:u,r40d1:u,r01d1:u,r02d1:u,r04d1:u,r20d1:u,r024c:u -o $@ -n 21 -r 10 \
		--environment-increment 0 --argument-increment 1

#
# Output: perf statistics for default and optimal offset, O3 only
perf-offsets-O3: conv-O3-gcc
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./$+
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./$+ 12
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./$+ 16


#
# Figure: Plot over different offsets with GCC and only O3
#         Show L1 hits, all other cache counters are trivially small (a couple of thousands)
bin/offsets-O3-gcc.eps: bin/offsets-O3-gcc.csv
	../lplot $+ -e cycles:u,r0107:u,r01d1:u --export $@ \
		--legend 'upper right' \
		--labels 'Cycles, cycles:u' 'Address alias, r0107:u' 'L1 hit, r01d1:u'








#
# All optimal compiler flags
#
conv-clang: convolution.c
	# Best offset: 0x30
	clang $(CLFLAGS) convolution.c -o $@
	clang $(CLFLAGS) -S convolution.c -o $@.s

conv-cc: convolution.c
	# Best offset: 0x30
	cc $(CCFLAGS) convolution.c -o $@
	cc $(CCFLAGS) -S convolution.c -o $@.s

conv-icc: convolution.c
	# Best offset: 0xa0
	icc $(CCFLAGS) convolution.c-o $@
	icc $(CCFLAGS) -S convolution.c -o $@.s

perf-compilers: conv-cc conv-clang conv-icc
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./conv-cc
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./conv-clang
	perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./conv-icc



stat.csv:
	./run-offsets

stat.all.csv:
	../lperf -i 0 -a 1 --repeat 4 -n 100 -o stat.all.csv ./convolution > /dev/null

graph-all: stat.all.csv
	../lplot stat.all.csv --legend 'upper right' -t 'Array Offset' -e 'cycles:u,r01a2:u,r02a3:u,r025c:u,r013c:u,r003c:u,r04a3:u,r05a3:u,r8108:u' 

graph: stat.csv
	../lplot stat.csv --legend 'upper right' -t 'Array Offset'
