#!/bin/bash
# $ ./run.sh count -e cycles:u,instructions:u -n 100
# This command runs a program multiple times, storing output from perf
# in a file stat.dat. plot.sh can extract a set of counters for plotting

prog=$1; stat="cycles:u"; n=100

let OPTIND++; # Ignore first options token in getops
while getopts ":e:n:" option
do
    case $option in
        e) stat=$OPTARG ;;
        n) n=$OPTARG ;;
        \?) echo "Usage: $ ./run <program> [-e <counters>] [-n <runs>]"; ;;
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

echo "Running $n measurements..."
for i in `seq $n`
{
    # Change environment (TODO)

    # Run program and store results
    perf stat -e $stat -x" " --output $output --append ./$prog
}

./plot.sh $output $stat



