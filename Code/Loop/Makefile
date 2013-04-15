SHELL := /bin/bash

COUNTERS=cycles:u,r02a3:u,r0107:u,r01a2:u
PLOT_AXIS_LABELS=--xlabel 'Bytes added to environment' --ylabel 'Counter value'
PLOT_LEGEND=--legend 'upper right'

# Positions stack close to where alias effects occur
# The precise number of bytes in environment is difficult to get,
# about 130 is added by perf.
ENV_OFFSET=3200

.DEFAULT: loop
.PHONY: clean figure-alias figure-fixed figure-alias-all

loop: loop.c
	cc loop.c -o loop

loop-fixed: loop-fixed.c
	cc loop-fixed.c -o loop-fixed

stat.all.csv: loop
	../lperf ./loop -o stat.all.csv -n 500 -r 10 -c r0107:u --environment-increment 16

stat.csv: loop
	../lperf ./loop -e $(COUNTERS) -o stat.csv -n 200 -r 10 \
		--correlate r0107:u \
		--environment-offset $(ENV_OFFSET) \
		--environment-increment 1

stat.fixed.csv: loop-fixed
	../lperf ./loop-fixed -e $(COUNTERS) -o stat.fixed.csv -n 200 -r 10 \
		--correlate r0107:u \
		--environment-offset $(ENV_OFFSET) \
		--environment-increment 1

figure-alias-cycles: stat.csv
	../lplot stat.csv -e cycles:u \
		--title 'Environment size bias' \
		--xlabel 'Bytes added to environment' --ylabel 'Cycle count'

figure-alias: stat.csv
	../lplot stat.csv -e $(COUNTERS) $(PLOT_AXIS_LABELS) $(PLOT_LEGEND) --title 'Environment size bias'

figure-fixed: stat.fixed.csv
	../lplot stat.csv -e $(COUNTERS) $(PLOT_AXIS_LABELS) $(PLOT_LEGEND) --title 'Runtime detection of address alias'

clean:
	rm -f loop loop-fixed stat.csv
