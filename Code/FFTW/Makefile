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

# Creates two dataseries, one for fftw with stackfix implemented, and one default installation
benchmark: bin/default.csv bin/modified.csv
	../lplot bin/default.csv  -e cycles:u,r0107:u --ticks 1024 --stride 16 --title 'default' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--xlabel 'Bytes added to environment'
	mv default.eps bin/default.eps
	../lplot bin/modified.csv -e cycles:u,r0107:u --ticks 1024 --stride 16 --title 'modified' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--ylim 40000000 \
		--xlabel 'Bytes added to environment'
	mv modified.eps bin/modified.eps
	bin/statistics bin/default.csv bin/modified.csv

# Allocate padding heap memory to provoke worst case collision with naive stackfix
worstcase: bin/worstcase.csv
	../lplot $+ -e cycles:u,r0107:u --ticks 1024 --stride 16 --title $@ \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--xlabel 'Bytes added to environment'
	mv $@.eps bin/$@.eps

# Sample 8192/16 = 512 points
bin/default.csv: fftw-default
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16

bin/modified.csv: fftw-modified
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16

# 7500 bytes before calling fftw_malloc hits a peak for alias events: aligns (in, out) to (0x604da0, 0x604f00)
bin/worstcase.csv: fftw-modified
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16 \
		--argument-offset 7500 --argument-increment 0

clean:
	rm -f fftw-default fftw-modified

purge:
	rm -f bin/*.csv
