#!/bin/bash
# $ ./run.sh count -e cycles:u,instructions:u -n 100

PROG=$1; STAT="cycles:u"; N=100

while getopts "e:n:" option
do
    case $option in
        e) STAT=${OPTARG};;
        n) N=${OPTARG};;
    esac
done

# Init output file with no content
OUTP='stat.dat'; cp /dev/null $OUTP

ASLR=`cat /proc/sys/kernel/randomize_va_space`
if [ $ASLR != 0 ]
then
    echo "Disabling address space layout randomization ..."
    sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"
fi

echo "Running $N measurements..."
for N in `seq $N`
{
    # Change environment (TODO)

    # Run program and store results
    perf stat -e $STAT -x" " --output $OUTP --append ./$PROG
}

echo "Plotting graph..."
./plot.sh $OUTP $STAT



