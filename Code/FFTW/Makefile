# make && perf stat -e cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u ./fftw-alias 0
# make && perf stat -e cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u env -i FOO=`head -c 2500 </dev/zero | tr '\0' '0'` ./fftw-alias 0
#
# (dft-direct-16 "n1fv_16_avx")
# (120.000000, 120.000000), (-48.218716, 32.218716), (-27.313708, 11.313708), (-19.972846, 3.972846), 
# (-16.000000, 0.000000), (-13.345429, -2.654571), (-11.313708, -4.686292), (-9.591299, -6.408701), 
# (-8.000000, -8.000000), (-6.408701, -9.591299), (-4.686292, -11.313708), (-2.654571, -13.345429), 
# (0.000000, -16.000000), (3.972846, -19.972846), (11.313708, -27.313708), (32.218716, -48.218716),
#
#
# ~/FFT/fftw-mod-3.3.3/dft/simd/avx$ gcc -march=native -std=gnu99 -DHAVE_CONFIG_H -I. -I../../.. -I../../../kernel -I../../../dft -I../../../dft/simd -I../../../simd-support -mavx -O3 -fomit-frame-pointer -mtune=native -malign-double -fstrict-aliasing -fno-schedule-insns -ffast-math -MT n1fv_16.lo -MD -MP -MF .deps/n1fv_16.Tpo -c n1fv_16.c  -fPIC -DPIC -fverbose-asm -S -o .libs/n1fv_16.s
#
COUNTERS=cycles:u,r0107:u,r01a2:u,r05a3:u

CFLAGS=-std=c99 -O3 -ffast-math -fomit-frame-pointer -march=native -Wall

# Custom built FFTW-3.3.3 (see INSTALL) Using evil rpath because LD_LIBRARY_PATH cannot
# be set using the lperf framework (default empty environment). Not needed for static link.
# Built two versions, default in /usr/local, and modified kernels in /usr/local/custom
FFTW_DEFAULT=-I/usr/local/include -L/usr/local/lib/ -Wl,-rpath,/usr/local/lib
FFTW_MODIFIED=-I/usr/local/custom/include -L/usr/local/custom/lib/ -Wl,-rpath,/usr/local/custom/lib

.PHONY: clean purge benchmark

fftw-default: fftw-alias.c
	cc -o $@ $(CFLAGS) $+ $(FFTW_DEFAULT) -lfftw3 -lm

fftw-modified: fftw-alias.c
	cc -o $@ $(CFLAGS) $+ $(FFTW_MODIFIED) -lfftw3 -lm

# Creates two dataseries, one for fftw with stackfix implemented, and one default installation.
# Run a large number of samples with randomized environment (ASLR enabled). 
benchmark: 
	#bin/benchmark-default.csv bin/benchmark-modified.csv
	../lplot bin/benchmark-default.csv  -e cycles:u,r0107:u --ticks 1024 --title 'default' \
		--legend 'upper right' --labels 'Unhalted core cycles' 'Address alias' \
		--dimension 8.5 3.5 \
		--xlabel 'Bytes added to environment'
	mv default.eps bin/default.eps
	../lplot bin/benchmark-modified.csv -e cycles:u,r0107:u --ticks 1024 --title 'modified' \
		--legend 'upper right' --labels 'Unhalted core cycles' 'Address alias' \
		--dimension 8.5 3.5 --ylim 50000000 \
		--xlabel 'Bytes added to environment'
	mv modified.eps bin/modified.eps
	bin/statistics bin/benchmark-default.csv bin/benchmark-modified.csv

bin/benchmark-default.csv: fftw-default
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 8192 -o $@ --environment-offset 1700 --environment-increment 1

bin/benchmark-modified.csv: fftw-modified
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 8192 -o $@ --environment-offset 1700 --environment-increment 1

# Allocate padding heap memory to provoke worst case collision with naive stackfix
worstcase:
	

clean:
	rm -f fftw-default fftw-modified

purge:
	rm -f bin/benchmark*.csv
