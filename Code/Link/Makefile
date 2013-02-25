
link0:
	cc -c main.c a.c b.c
	cc main.o a.o b.o

link1:
	cc -c main.c a.c b.c
	cc main.o b.o a.o

stat:
	../perfrun.py -e r0120:u,r01a8:u -n 100 -r 1 -c cycles:u -i 0 ./a.out

graph:
	../plot.py #-e r0160:u,r0260:u,r0460:u,r0860:u

