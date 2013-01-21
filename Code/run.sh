#!/bin/bash
# Run a program and store performance counter information

PROG='hello'
LIMIT=100
ASLR=0 # 0 => No randomization, 1 => Stack random, 2 => Stack and heap random
OLD_ASLR=`cat /proc/sys/kernel/randomize_va_space`
STAT='cycles'

echo "Old is $OLD_ASLR"

# Disable  address space layout randomization
if [ $OLD_ASLR != $ASLR ]
then
    echo "Changing 'Address space layout randomization' from $OLD_ASLR to $ASLR..."
    sudo bash -c "echo $ASLR > /proc/sys/kernel/randomize_va_space"
fi

for N in `seq $LIMIT`
{
    # Add environment (TODO)

    # Run program and store results
    echo `perf stat -e $STAT -x" " --output "stat.$N.txt" ./$PROG` #> /dev/null
}

echo 'Done!'





