
all:
	cc -std=c99 page.c

stat:
	../perfrun.py -e cycles:u,page-faults:u -n 100 -r 1 -c cycles:u -i 0 ./a.out

graph:
	../plot.py

