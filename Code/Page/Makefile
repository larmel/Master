
all:
	gcc -std=c99 -O3 -march=native page.c
	gcc -std=c99 -O3 -march=native -S page.c

stat:
	../perfrun.py -e cycles:u,page-faults:u -n 100 -r 1 -c cycles:u -i 16 ./a.out

graph:
	../plot.py -e cycles:u &
	../plot.py -e page-faults:u &

