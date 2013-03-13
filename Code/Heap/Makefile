
all: a.out stat.csv graph

prog:
	cc heap.c
	cc heap.c -S

a.out:
	cc -mmmx heap.c

stat.csv:
	../lperf -e cycles:u,r01d1:u,r02d1:u,r0107:u,r01a2:u,cache-references:u,cache-misses:u -n 500 -r 5 -c cycles:u -i 0 -a 16 ./a.out
	#../perfrun.py -n 500 -r 4 -c cycles:u -i 16 -a 16 ./a.out

graph:
	../lplot -e cycles:u,r01d1:u,r02d1:u,r0107:u,r01a2:u,cache-references:u,cache-misses:u,r0120:u

clean:
	rm -f stat.csv
	rm -f a.out

