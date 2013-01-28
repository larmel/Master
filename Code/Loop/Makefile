
loop:
	cc loop.c -O3

stat:
	../stat ./a.out -n 1000 > stat.dat

graph:
	../plot stat.dat branch-misses:u,cycles:u,cache-references:u,cache-misses:u,r203 | gnuplot -persist

clean:
	rm -f a.out
