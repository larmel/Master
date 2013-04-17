# make fftw-alias && perf stat -e cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u ./fftw-alias 0
COUNTERS=cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u

CFLAGS=-O3 -ffast-math -fomit-frame-pointer -march=native -Wall

# Custom built FFTW 3.3.3
#   ./configure; make; make install
# Remove to use prebuilt package instead
FFTWLIBDIR=-L/usr/local/lib/

# float | double | int32_t | int16_t | simd
DATATYPE=double

ifeq "$(DATATYPE)" "float"
	FFTWLIB=-lfftw3f
else
	FFTWLIB=-lfftw3
endif


.DEFAULT: fftw-alias
.PHONY: clean

fftw-alias: fftw-alias.c
	cc -o $@ $(CFLAGS) -DDATATYPE$(DATATYPE) $+ $(FFTWLIB) $(FFTWLIBDIR) -lm

stat.csv: fftw-alias
	../lperf ./fftw-alias -e $(COUNTERS) -r 1 -n 60 \
		--argument-offset 0 \
		--argument-increment 2 \
		--environment-offset 0 \
		--environment-increment 0 > /dev/null

graph: stat.csv
	../lplot stat.csv --legend 'upper right'

clean:
	rm -f fftw-alias stat.csv
