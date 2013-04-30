SHELL := /bin/bash

COUNTERS=cycles:u,r02a3:u,r0107:u,r01a2:u,r05a3:u
PLOT_AXIS_LABELS=--xlabel 'Bytes added to environment' --ylabel 'Counter value'
PLOT_LEGEND=--legend 'upper right'

# Positions stack close to where alias effects occur
# The precise number of bytes in environment is difficult to get,
# about 130 is added by perf.
ENV_OFFSET=3200

.PHONY: clean figure-alias figure-fixed figure-alias-all

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

# Illustration used in Motivation section of thesis. Small graph with just the spike showing only cycle count. 
bin/motivation.eps: loop
	../lperf ./loop -e $(COUNTERS) -o stat.motivation.csv -n 100 -r 10 \
		--environment-offset $(ENV_OFFSET) --environment-increment 16
	../lplot stat.motivation.csv -e cycles:u --title 'motivation' \
		--xlabel '$(ENV_OFFSET) + n * 16 bytes added to environment' \
		--ylabel 'Cycle count' \
		--dimension 5 3
	rm stat.motivation.csv
	mv motivation.eps bin/motivation.eps

clean:
	rm -f loop loop-fixed stat.csv
