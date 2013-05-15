SHELL := /bin/bash

COUNTERS=cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u
PLOT_AXIS_LABELS=--xlabel 'Bytes added to environment' --ylabel 'Counter value'
PLOT_LEGEND=--legend 'upper right'

# Positions stack close to where alias effects occur
# The precise number of bytes in environment is difficult to get,
# about 130 is added by perf.
ENV_OFFSET=3200

.PHONY: clean purge bin/motivation.eps figure-alias figure-fixed figure-alias-all

loop: loop.c
	cc loop.c -o loop

loop-fixed: loop-fixed.c
	cc loop-fixed.c -o loop-fixed

stat.all.csv: loop
	../lperf ./loop -o stat.all.csv -n 200 -r 10 \
		--environment-offset $(ENV_OFFSET) \
		--environment-increment 1

stat.csv: loop
	../lperf ./loop -e $(COUNTERS) -o stat.csv -n 200 -r 10 \
		--environment-offset $(ENV_OFFSET) \
		--environment-increment 1

stat.fixed.csv: loop-fixed
	../lperf ./loop-fixed -e $(COUNTERS) -o stat.fixed.csv -n 200 -r 10 \
		--environment-offset $(ENV_OFFSET) \
		--environment-increment 1

figure-alias-cycles: stat.csv
	../lplot stat.csv -e cycles:u --xlabel 'Bytes added to environment' --ylabel 'Cycle count' --title 'loop-alias-cycles'

figure-alias: stat.csv
	../lplot stat.csv -e $(COUNTERS) $(PLOT_AXIS_LABELS) $(PLOT_LEGEND) --title 'loop-alias'

figure-fixed: stat.fixed.csv
	../lplot stat.fixed.csv -e $(COUNTERS) $(PLOT_AXIS_LABELS) $(PLOT_LEGEND) --title 'loop-alias-fixed'


# Figure: Motivation
# Illustration used in Motivation section of thesis. Small graph with just the spike showing only cycle count. 
bin/motivation.csv: loop
	../lperf ./$+ -e $(COUNTERS) -o $@ -n 100 -r 100 \
		--environment-offset $(ENV_OFFSET) --environment-increment 2

bin/motivation.eps: bin/motivation.csv
	../lplot $+ -e cycles:u --export $@ \
		--xlabel 'Bytes added to environment' --ylabel 'Cycle count' \
		--stride 2 \
		--dimension 3.8 2.3


clean:
	rm -f loop loop-fixed stat.csv

purge:
	rm -f bin/*.csv
