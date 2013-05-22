
dynamic:
	cc -c -fPIC loop.c -o loop.o
	cc -shared -Wl,-soname,libloop.so -o libloop.so loop.o
	cc lsd.c -Wl,-rpath . -L. -lloop -o dynamic

static:
	cc -c loop.c -o loop.o
	ar rcs libloop.a loop.o
	cc lsd.c -L. -static -lloop -o static

a.out:
	cc lsd.c fact.c loop.c -o a.out

b.out:
	cc lsd.c loop.c fact.c -o b.out

test: a.out b.out
	perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./a.out
	perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./b.out


# A single main function covering 13 chunks. Fixed by inserting nops
loop-single.s: loop-single.c
	cc -S loop-single.c -o loop-single.s
loop-single: loop-single.s
	cc loop-single.s -o loop-single
test-single: loop-single
	perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./loop-single


# Based on link order and O3
c.out:
	cc -O3 lsd.c loop-optimized.c fact-optimized.c -o c.out
d.out:
	cc -O3 lsd.c fact-optimized.c loop-optimized.c -o d.out
test-optimized: c.out d.out
	perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./c.out
	perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./d.out

clean:
	rm -f static dynamic a.out b.out c.out d.out
