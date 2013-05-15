SHELL:=/bin/bash
# Test default blas package available from Ubuntu repository, and auto-tuned ATLAS.
# For some reason only serial version works (-lsatlas). 

COUNTERS=cycles:u,r0107:u,r01a2:u
LABELS='Cycle count, cycles:u' 'Address alias, r0107:u' 'Resource stalls, r01a2:u'

CFLAGS=-std=c99 -O3 -march=native

.PHONY: clean purge disable-aslr


# Link with serial ATLAS in /usr/local/atlas
gemv-atlas: gemv.c
	cc $(CFLAGS) $+ -o $@ -I/usr/local/atlas/include -L/usr/local/atlas/lib -lsatlas

# Link with default BLAS
# Fails for some reason, almost no instructions executed.
gemv-blas: gemv.c
	cc $(CFLAGS) $+ -o $@ -L/usr/lib/libblas -Wl,-rpath,/usr/lib/libblas -lblas 


# Try allocating increasing amount on heap initially, pushing addresses of x and y vectors, 256x16 = 4K
bin/gemv-atlas-offset.csv: gemv-atlas
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 256 -o $@ --environment-increment 0 --argument-increment 16

bin/gemv-atlas-offset-all.csv: gemv-atlas
	../lperf ./$+ -r 1 -n 32 -o $@ --environment-increment 0 --argument-increment 16

bin/gemv-atlas-offset.eps: bin/gemv-atlas-offset.csv
	../lplot $+ --export $@ -e $(COUNTERS) --labels $(LABELS) \
		--legend 'center right' --ytickformat 'millions' \
		--xlabel 'Additional heap-allocated bytes' --ylabel 'Event count (millions)' \
		--stride 16 --ticks 1024


# Show single run statistics for best (64) and worst (1024) case, ++
# Use argument to specify iteration count (third argument)
# Lots of counters of interest, hard to rule out cache as underlying cause
# But, there is a period on 4K, meaning it must reflect in L1 size (it does) or L2 size (not).
disable-aslr:
	sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"

# Run directly (64, 0, _), with script (48, 0, _)
bin/worstcase.csv: gemv-atlas disable-aslr
	bin/benchmark gemv-atlas 48 0 ${n} $@

# Run directly (64, 128, _), with script (48, 128, _)
bin/averagecase.csv: gemv-atlas disable-aslr
	bin/benchmark gemv-atlas 48 128 ${n} $@

# Run directly (1024, 0 _), with script (1016, 0, _)
bin/bestcase.csv: gemv-atlas disable-aslr
	bin/benchmark gemv-atlas 1016 0 ${n} $@

bin/statistics.csv: bin/worstcase.csv bin/averagecase.csv bin/bestcase.csv
	bin/merge $@ $+


clean:
	rm -f gemv-atlas gemv-blas

purge:
	rm -f bin/worstcase.csv bin/averagecase.csv bin/bestcase.csv
