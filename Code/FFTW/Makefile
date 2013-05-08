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

.PHONY: clean purge benchmark kernels mainfix


fftw-default: fftw.c
	cc -o $@ $(CFLAGS) $+ $(FFTW_DEFAULT) -lfftw3 -lm

fftw-modified: fftw.c
	cc -o $@ $(CFLAGS) $+ $(FFTW_MODIFIED) -lfftw3 -lm

fftw-mainfix: fftw.c
	cc -o $@ $(CFLAGS) -DMAINFIX $+ $(FFTW_DEFAULT) -lfftw3 -lm


# Creates two dataseries, one for fftw with stackfix implemented, and one default installation
# Sample 8192/16 = 512 points
benchmark: bin/default.csv bin/modified.csv
	../lplot bin/default.csv  -e cycles:u,r0107:u --ticks 1024 --stride 16 --export 'bin/default.eps' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--xlabel 'Bytes added to environment'
	../lplot bin/modified.csv -e cycles:u,r0107:u --ticks 1024 --stride 16 --export 'bin/modified.eps' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--ylim 40000000 \
		--xlabel 'Bytes added to environment'
	bin/statistics bin/default.csv bin/modified.csv

bin/default.csv: fftw-default
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16

bin/modified.csv: fftw-modified
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16


# Allocate padding heap memory to provoke worst case collision with naive stackfix
# 7500 bytes before calling fftw_malloc hits a peak for alias events: aligns (in, out) to (0x604da0, 0x604f00)
worstcase: bin/worstcase.csv
	../lplot $+ -e cycles:u,r0107:u --ticks 1024 --stride 16 --export 'bin/worstcase.eps' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--xlabel 'Bytes added to environment'

bin/worstcase.csv: fftw-modified
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16 \
		--argument-offset 7500 --argument-increment 0


# Plot 4 additional sizes of N having their own kernels. FFTW_ESTIMATE is used because it
# is deterministic. With the default FFTW_MEASURE, different plans messes up the plot.
# avx kernels are chosen for almost all sizes, except "generic" for 17, 19, 23, 29, 32
bin/n1fv_8_avx.csv bin/n1fv_15_avx.csv bin/n1fv_20_avx.csv bin/n1fv_32_avx.csv: fftw.c
	cc $(CFLAGS) -DN=$(subst bin/n1fv_,,$(subst _avx.csv,,$@)) -DPLAN=FFTW_ESTIMATE $+ $(FFTW_DEFAULT) -lfftw3 -lm
	../lperf ./a.out -e $(COUNTERS) -r 1 -n 256 -o $@ --environment-offset 1700 --environment-increment 16
	rm a.out

kernels: bin/n1fv_8_avx.csv bin/n1fv_15_avx.csv bin/n1fv_20_avx.csv bin/n1fv_32_avx.csv
	../lplot $+ -e cycles:u,r0107:u --title $(subst bin/,,$(subst .csv,,$+)) --ticks 1024 --stride 16 \
		--export 'bin/kernels.eps' --dimension 6 5 --ytickformat 'millions'


#
# Illustrate a point by showing all alias gone with fix in main
mainfix: bin/mainfix.csv bin/default.csv
	../lplot bin/default.csv  -e cycles:u,r0107:u --ticks 1024 --stride 16 --export 'bin/default.eps' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--xlabel 'Bytes added to environment'
	../lplot bin/mainfix.csv -e cycles:u,r0107:u --ticks 1024 --stride 16 --export 'bin/mainfix.eps' \
		--legend 'center right' --labels 'Cycle count, cycles:u' 'Address alias, r0107:u' \
		--ylim 40000000 \
		--xlabel 'Bytes added to environment'
	bin/statistics bin/default.csv bin/mainfix.csv

bin/mainfix.csv: fftw-mainfix
	../lperf ./$+ -e $(COUNTERS) -r 1 -n 512 -o $@ --environment-offset 1700 --environment-increment 16


clean:
	rm -f fftw-default fftw-modified

purge:
	rm -f bin/*.csv
