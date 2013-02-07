
loop:
	cc loop.c -O3

stat:
	../perfrun.py -e ../counters -n 1000 -r 2 ./a.out
	#../stat ./a.out -n 1000 > stat.dat

graph:
	../plot.py -e cycles:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u
	#../plot stat.dat branch-misses:u,cycles:u,cache-references:u,cache-misses:u,r203 | gnuplot -persist

clean:
	rm -f a.out
	rm -f
