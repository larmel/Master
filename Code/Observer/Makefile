
SEVEN=cycles:u,page-faults:u,r0107:u,r003c:u,r025c:u,r01a2:u,r02a3:u
EIGHT=cycles:u,page-faults:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u


all: a.out stat graph

a.out:
	cc heap.c

stat:
	../perfrun.py -o stat.7.csv -e $(SEVEN) -n 500 -r 4 -c cycles:u -i 0 -a 0 ./a.out > /dev/null
	# Effect disappears whn removing one or more counters
	../perfrun.py -o stat.8.csv -e $(EIGHT) -n 500 -r 4 -c cycles:u -i 0 -a 0 ./a.out > /dev/null
	../perfrun.py -o stat.all.csv -n 500 -r 4 -c cycles:u -i 0 -a 0 ./a.out > /dev/null

graph:
	../plot.py -f stat.7.csv -e $(SEVEN) &
	../plot.py -f stat.8.csv -e $(SEVEN) &
	../plot.py -f stat.all.csv -e $(SEVEN) &


wat:
	cc heap.c
	#../perfrun.py -o stat.test.csv -e r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,cycles:u -n 500 -r 4 -i 0 -a 0 ./a.out > /dev/null
	../perfrun.py -o stat.test.csv -e cycles:u,cycles:u,cycles:u,cycles:u,cycles:u,cycles:u,cycles:u,cycles:u,cycles:u -n 500 -r 1 -i 0 -a 0 ./a.out > /dev/null
	../plot.py -f stat.test.csv
