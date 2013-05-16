SHELL := /bin/bash

# Counters with more than 30% correlation to cycle count
# LD_BLOCKS_PARTIAL.ADDRESS_ALIAS
# RESOURCE_STALLS.ANY
# CYCLE_ACTIVITY.CYCLES_LDM_PENDING
# CPL_CYCLES.RING123
# CPU_CLK_THREAD_UNHALTED.REF_XCLK
# CPU_CLK_UNHALTED.THREAD_P
# CYCLE_ACTIVITY.CYCLES_NO_EXECUTE
# CYCLE_ACTIVITY.STALLS_L2_PENDING (Disregard, not in 19-5)
# UOPS_DISPATCHED_PORT.PORT_4
# UOPS_DISPATCHED_PORT.PORT_5
# UOPS_DISPATCHED_PORT.PORT_1
# UOPS_DISPATCHED_PORT.PORT_0
# RESOURCE_STALLS.RS
COUNTERS=cycles:u,r0107:u,r01a2:u,r02a3:u,r025c:u,r05a3:u,r40a1:u,r80a1:u,r02a1:u,r01a1:u,r04a2:u

# Positions stack close to where alias effects occur
# The precise number of bytes in environment is difficult to get,
# about 130 is added by perf.
ENV_OFFSET=3200

.PHONY: clean purge bin/cycles.eps bin/correlation.eps bin/uopsdispatch.eps bin/fixed.eps bin/motivation.eps

loop: loop.c
	cc loop.c -o loop

loop-fixed: loop-fixed.c
	cc loop-fixed.c -o loop-fixed


# Counter statistics
bin/loop.all.csv: loop
	../lperf ./$+ -o $@ -n 256 -r 2 \
		--environment-offset $(ENV_OFFSET) --environment-increment 1

bin/loop.csv: loop
	../lperf ./$+ -e $(COUNTERS) -o $@ -n 256 -r 2 \
		--environment-offset $(ENV_OFFSET) --environment-increment 1

bin/fixed.csv: loop-fixed
	../lperf ./$+ -e $(COUNTERS) -o $@ -n 256 -r 2 \
		--environment-offset $(ENV_OFFSET) --environment-increment 1

bin/motivation.csv: loop
	../lperf ./$+ -e $(COUNTERS) -o $@ -n 100 -r 100 \
		--environment-offset $(ENV_OFFSET) --environment-increment 2


# Figure: Only cycle count
bin/cycles.eps: bin/loop.csv
	../lplot $+ -e cycles:u --export $@ \
		--xlabel 'Bytes added to environment' --ticks 64

# Figure: Counters with the most correlation to cycle count
bin/correlation.eps: bin/loop.csv
	../lplot $+ -e cycles:u,r0107:u,r01a2:u,r02a3:u --export $@ \
		--xlabel 'Bytes added to environment' --ticks 64 \
		--legend 'upper right' --legendcols 2 \
		--labels 'Cycles, cycles:u' 'Alias, r0107:u' 'Resource stalls, r01a2:u' 'Pending loads, r02a3:u'

# Figure: Uops dispatch ports correlation with cycles
bin/uopsdispatch.eps: bin/loop.csv
	../lplot $+ -e cycles:u,r01a1:u,r02a1:u,r40a1:u,r80a1:u --export $@ \
		--xlabel 'Bytes added to environment' --ticks 64 \
		--legend 'upper right' --legendcols 2 \
		--labels 'Cycles, cycles:u' 'Port 0' 'Port 1' 'Port 4' 'Port 5'

# Figure: All alias gone with alternate code path on detected conflict
bin/fixed.eps: bin/fixed.csv
	../lplot $+ -e cycles:u,r0107:u,r01a2:u,r02a3:u --export $@ \
		--xlabel 'Bytes added to environment' --ticks 64 \
		--legend 'upper right' --legendcols 2 \
		--labels 'Cycles, cycles:u' 'Alias, r0107:u' 'Resource stalls, r01a2:u' 'Pending loads, r02a3:u'

# Figure: Motivation, small graph with just the spike showing only cycle count. 
bin/motivation.eps: bin/motivation.csv
	../lplot $+ -e cycles:u --export $@ \
		--xlabel 'Bytes added to environment' --ylabel 'Cycle count' \
		--stride 2 \
		--dimension 3.8 2.3


clean:
	rm -f loop loop-fixed stat.csv

purge:
	rm -f bin/loop.csv bin/fixed.csv bin/motivation.csv
