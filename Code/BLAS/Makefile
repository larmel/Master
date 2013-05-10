
# Test default blas package available from Ubuntu repository, and auto-tuned ATLAS.
# For some reason only serial version works (-lsatlas). 

# Matrix size
CFLAGS=-std=c99 -O3 -march=native

.PHONY: clean

# Link with serial ATLAS in /usr/local/atlas
atlas: atlas.c
	cc $(CFLAGS) $+ -o $@ -I/usr/local/atlas/include -L/usr/local/atlas/lib -lsatlas

# Link with default BLAS
blas: blas.c
	cc $(CFLAGS) $+ -o $@ -L/usr/lib/libblas -Wl,-rpath,/usr/lib/libblas -lblas 

test: atlas blas
	perf stat -e cycles:u,r0107:u,cache-misses:u,cache-references:u ./blas
	perf stat -e cycles:u,r0107:u ./atlas

clean:
	rm -f blas atlas
