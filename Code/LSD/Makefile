
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

clean:
	rm -f static
	rm -f dynamic
	rm -f a.out
	rm -f b.out
