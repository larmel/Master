# make && perf stat -e cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u ./fftw-alias 0
# make && perf stat -e cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u env -i FOO=`head -c 2500 </dev/zero | tr '\0' '0'` ./fftw-alias 0
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
		--environment-offset 1700 --environment-increment 16 > /dev/null

graph: stat.csv
	../lplot -e cycles:u,r0107:u,r01a2:u,r05a3:u stat.csv --legend 'upper right'

clean:
	rm -f fftw-alias stat.csv
