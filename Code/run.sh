#!/bin/bash

PROG='count'
OUTP='stat.log'
STAT='instructions:u'

LIMIT=1000
ASLR=0
OLD_ASLR=`cat /proc/sys/kernel/randomize_va_space`

# Init output file with no content
cp /dev/null $OUTP

echo "# Address Space Randomization is $OLD_ASLR"

# Disable  address space layout randomization
if [ $OLD_ASLR != $ASLR ]
then
    echo "Changing 'Address space layout randomization' from $OLD_ASLR to $ASLR..."
    sudo bash -c "echo $ASLR > /proc/sys/kernel/randomize_va_space"
fi

echo "# Running $LIMIT measurements"
for N in `seq $LIMIT`
{
    # Change environment (TODO)

    # Run program and store results
    perf stat -e $STAT -x", " --output $OUTP --append ./$PROG
}

echo "# Plotting graph"

# Format output data correctly
grep $STAT $OUTP > "plot.tmp"
gnuplot -persist <<- EOF
    set xlabel "Run #"
    set ylabel "$STAT"
    #set term png
    #set output "plot.png"
    plot "plot.tmp" with lines title "Cycle count"
EOF

#rm "plot.tmp"




