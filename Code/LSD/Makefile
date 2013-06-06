
.PHONY: linkorder observer icache


chunks.s: chunks.c
	cc -S $+ -o $@

chunks: chunks.s
	cc $+ -o $@

#
# A single main function covering 13 chunks, fixed by inserting printf
observer: chunks
	perf stat -e cycles:u,r0120:u,r01a8:u,instructions:u ./chunks


# Inspect alignment forced by O3
loop.s: loop.c
	cc -O3 -S loop.c -o $@

main-loop-foo: main.c loop.c foo.c
	cc -O3 main.c loop.c foo.c -o $@

main-foo-loop: main.c loop.c foo.c
	cc -O3 main.c foo.c loop.c -o $@

#
# Show bias from link order
linkorder: main-loop-foo main-foo-loop
	perf stat -e cycles:u,r0120:u,r01a8:u,instructions:u ./main-loop-foo
	perf stat -e cycles:u,r0120:u,r01a8:u,instructions:u ./main-foo-loop


#
# Small example that only uses LSD on certain alignments
icache: icache.s
	cc $+ -o $@ && perf stat -e cycles:u,r0120:u,r01a8:u ./$@


clean:
	rm -f chunks main-foo-loop main-loop-foo icache loop.s chunks.s
