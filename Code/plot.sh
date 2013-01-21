#!/bin/bash
# Read ouput files generated from repeated runs and make a plot

# Read all stat.<N>.txt files

DATA='data.txt'

cp /dev/null $DATA

for F in `ls stat.*`
{
    # Append line with cycles
    echo `grep cycles $F | awk '{print $1}'` >> $DATA
}

# plot
gnuplot <<- EOF
    set xlabel "Iteration"
    set ylabel "Cycles"
    set term png
    set output "plot.png"
    plot "$DATA" with lines title "Cycle count"
EOF

