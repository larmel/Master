#!/bin/bash
# ./plot.sh stat.dat cycles:u,instructions:u

# Modifying the data columns (e.g. plot differences):
# plot 'force.dat' using 1:($3-$2)
# plot 'force.dat' using (3*$2):(sin($3+$1))

FILE=$1; LINES=$2
compare=true

# Retrieve list of performance counters to be plotted
counters=$(echo $LINES | tr "," "\n")
for c in $counters
do
    grep " $c" $FILE | awk '{print $1}' > "$c"
done

# Paste files together to form one column for each data line
cp /dev/null "plot.dat"
paste $counters > "plot.dat"
rm $counters

# Build plot command
plot=''; axes=''; i=1; n=$(echo $counters | wc -w)
for c in $counters
do
	if $compare && [ "$i" -eq 2 ]; then
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

# Can be piped to gnuplot
echo "$axes"
echo "plot $plot"

# Generate plot
#echo "$axes; plot $plot" | gnuplot -persist # <<- EOF
	#set y2tics 10 nomirror tc lt 2
	#set y2tic nomirror
	#set logscale y
	#$axes
    #plot $plot
#EOF

