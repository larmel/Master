
all:
	cc heap.c

stat:
	#../perfrun.py -e cycles:u,r01a3:u,r02a3:u,r03a3:u,r04a3:u,r05a3:u,r06a3:u,r07a3:u,r08a3:u,r09a3:u -n 100 -r 1 -c cycles:u -i 0 ./a.out
	../perfrun.py -e cycles:u,page-faults:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u -n 1000 -r 4 -c cycles:u -i 0 -a 16 ./a.out > /dev/null
	

graph:
	../plot.py

