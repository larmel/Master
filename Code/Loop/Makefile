
loop:
	cc loop.c

stat:
	../perfrun.py -e ../counters -n 40 -r 5 -c r0107:u ./a.out
	#../stat ./a.out -n 1000 > stat.dat

graph:
	#../plot.py -e cycles:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u,branch-misses:u
	../plot.py -e cycles:u,r0107:u,r40a1:u,r04a2:u,r01a1:u,r80a1:u
	#../plot stat.dat branch-misses:u,cycles:u,cache-references:u,cache-misses:u,r203 | gnuplot -persist

clean:
	rm -f a.out
	rm -f
