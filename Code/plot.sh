#!/bin/bash

DATA='stat.log'

#cp /dev/null $DATA

#for F in `ls stat.*`
# {
    # Append line with cycles
#    echo `grep cycles $F | awk '{print $1}'` >> $DATA
#}

# Format output data correctly
grep cycles:u $DATA > "plot.tmp"

# plot
gnuplot <<- EOF
    set xlabel "Iteration"
    set ylabel "Cycles"
    set term png
    set output "plot.png"
    plot "plot.tmp" with lines title "Cycle count"
EOF

rm "plot.tmp"
