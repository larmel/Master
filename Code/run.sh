#!/bin/bash
# $ ./run.sh count -e cycles:u,instructions:u -n 100
# This command runs a program multiple times, storing output from perf
# in a file stat.dat. plot.sh can extract a set of counters for plotting

<<COMMENT
# Hardware events
cycles:u,instructions:u,cache-references:u,cache-misses:u,branches:u,branch-misses:u,bus-cycles:u

# Software events
cpu-clock:u,task-clock:u,faults:u,minor-faults:u,major-faults:u,cs,migrations,alignment-faults:u

# Cache hardware events
L1-dcache-loads:u
L1-dcache-load-misses:u
L1-dcache-stores:u
L1-dcache-store-misses:u
L1-dcache-prefetches:u
L1-dcache-prefetch-misses:u
L1-icache-loads:u
L1-icache-load-misses:u
L1-icache-prefetches:u
L1-icache-prefetch-misses:u
LLC-loads:u
LLC-load-misses:u
LLC-stores:u
LLC-store-misses:u
LLC-prefetches:u
LLC-prefetch-misses:u
dTLB-loads:u
dTLB-load-misses:u
dTLB-stores:u
dTLB-store-misses:u
dTLB-prefetches:u
dTLB-prefetch-misses:u
iTLB-loads:u
iTLB-load-misses:u
branch-loads:u
branch-load-misses:u
node-loads:u
node-load-misses:u
node-stores:u
node-store-misses:u
node-prefetches:u
node-prefetch-misses:u
COMMENT

stat="instructions:u,cycles:u,cache-references:u,cache-misses:u,branches:u,branch-misses:u,bus-cycles:u,\
faults:u,minor-faults:u,major-faults:u,cs,migrations,alignment-faults:u";

prog=$1; n=100

let OPTIND++; # Ignore first options token in getops
while getopts ":e:n:" option
do
    case $option in
        e) stat=$OPTARG ;;
        n) n=$OPTARG ;;
        \?) echo "Usage: $ ./run <program> [-e <counters>] [-n <runs>]"; exit ;;
    esac
done

# Init output file with no content
output='stat.dat'; cp /dev/null $output

ASLR=`cat /proc/sys/kernel/randomize_va_space`
if [ $ASLR != 0 ]
then
    echo "Disabling address space layout randomization ..."
    sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"
fi

for i in `seq $n`
{
    # Change environment (TODO)

    # Run program and store results
    echo "" >> $output
    echo "# Run $i" >> $output
    perf stat -e $stat -x" " --output $output --append ./$prog
}

./plot.sh $output $stat



