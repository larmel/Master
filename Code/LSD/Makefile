
all:
	cc -std=c99 lsd.c
	cc -std=c99 -S lsd.c

stat:
	../perfrun.py -e cycles:u,r0120:u,r01a8:u -n 100 -r 1 -c cycles:u -i 0 ./a.out

graph:
	../plot.py -e r0120:u,r01a8:u

