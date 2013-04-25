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
COUNTERS=cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u

CFLAGS=-O3 -ffast-math -fomit-frame-pointer -march=native -Wall

# Custom built FFTW-3.3.3 (see INSTALL)
# Remove to use prebuilt package instead. Using evil rpath because LD_LIBRARY_PATH cannot
# be set using the lperf framework (default empty environment). Not needed for static link.
# Built two versions, default in /usr/local, and modified kernels in /usr/local/custom
FFTW_PATH=/usr/local/custom
FFTW_INCLUDES=-I$(FFTW_PATH)/include -L$(FFTW_PATH)/lib/ -Wl,-rpath,$(FFTW_PATH)/lib

DATATYPE=double
ifeq "$(DATATYPE)" "float"
	FFTWLIB=-lfftw3f
else
	FFTWLIB=-lfftw3
endif

.DEFAULT: fftw-alias
.PHONY: clean graph

fftw-alias: fftw-alias.c
	cc -o $@ $(CFLAGS) -DDATATYPE$(DATATYPE) $+ $(FFTW_INCLUDES) $(FFTWLIB) -lm

stat.csv: fftw-alias
	../lperf ./fftw-alias -e $(COUNTERS) -r 1 -n 300 \
		--argument-offset 0 --argument-increment 0 \
		--environment-offset 1700 --environment-increment 16 > output

graph: stat.csv
	../lplot -e cycles:u,r0107:u,r01a2:u,r05a3:u stat.csv --title '${title}' --legend 'upper right'

clean:
	rm -f fftw-alias stat.csv
