#!/bin/bash
# ./plot.sh stat.log cycles:u,instructions:u

# Modifying the data columns (e.g. plot differences):
# plot 'force.dat' using 1:($3-$2)
# plot 'force.dat' using (3*$2):(sin($3+$1))

FILE=$1
LINES=$2

echo "Plotting data from $FILE with data $LINES"

# Retrieve list of performance counters to be plotted
counters=$(echo $LINES | tr "," "\n")
for c in $counters
do
    grep $c $FILE | awk '{print $1}' > "$c"
done

# Paste files together to form one column for each data line
paste $counters > "plot.dat"
rm $counters

# Build plot command
plot=''; axes=''; i=1; n=$(echo $counters | wc -w)
for c in $counters
do
	echo $i $c
	if [ "$i" -eq 2 ]; then
		echo "wat"
		axes+="set y${i}tic nomirror tc lt $i"
		plot+="'plot.dat' using $i linetype $i axes x1y2 title '$c' with lines"
	else
		plot+="'plot.dat' using $i linetype $i title '$c' with lines"
	fi
	if [ $i != $n ]
	then
		plot+=", "
	fi
	let i++
done

# Generate plot
gnuplot -persist <<- EOF
	#set y2tics 10 nomirror tc lt 2
	#set y2tic nomirror
	$axes
    plot $plot
EOF

