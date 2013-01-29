#!/usr/bin/env python 
import subprocess
import argparse
import sys

# $ ./perfrun.py Empty/a.out -e cycles:u,instructions:u -n 100 > Empty/stat.dat

# Number of counters (Sandy Bridge and Ivy Bridge), Section 18.8
# With HT off, 2*4 general purpose counters are visible per core
# Rules seems complicated. Strategy: run 8 counters at a time, hopefully no multiplexing.
# Need to verify that this is done correctly
fixed_counters = 3
general_purpose_counters = 8


def disable_layout_randomization():
    subprocess.call('sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"', shell=True)


def execute():
    disable_layout_randomization()

    parser = argparse.ArgumentParser(description='Automated perf runner')
    parser.add_argument('program', help='program to be run')
    parser.add_argument('-e', '--event_file', default='pc')
    parser.add_argument('-o', '--output', default='stat.dat')
    parser.add_argument('-n', '--num', default=2)
    parser.add_argument('-r', '--repeat', default=5)
    
    args = parser.parse_args()

    # Get list of performance counters from file
    pc = []
    for line in open(args.event_file):
        code, name = line.strip().split('\t')
        pc.append( (code, name) )

    # Clear output file
    subprocess.call('cp /dev/null '+args.output, shell=True)

    for run in range(0, int(args.num)):

        with open(args.output, 'a') as out:
            out.write(' '.join(['# Run', str(run), '\n']))

        for i in range(0, len(pc), general_purpose_counters):
            events = pc[i:i+general_purpose_counters]
            events_string = ','.join(map(lambda (c, n) : 'r'+c+':u', events))
            command = ' '.join(['perf stat -r', str(args.repeat), '-x" "', '-e', events_string, args.program, '0>>', args.output])
            subprocess.call(command, shell=True)

        with open(args.output, 'a') as out:
            out.write('\n')

if __name__ == '__main__':
    execute()

