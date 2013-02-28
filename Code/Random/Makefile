
CSMITH_DIR=~/csmith-2.1.0

all:
	${CSMITH_DIR}/src/csmith > random.c
	gcc -I ${CSMITH_DIR}/runtime/ -O -w random.c

stat:
	../perfrun.py -e cycles:u,branch-misses:u,r0107:u,r01a2:u -n 250 -r 4 -c cycles:u -i 16 ./a.out > /dev/null

graph:
	../plot.py

