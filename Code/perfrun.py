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

def export_csv(result, filename):
    with open(filename, 'w') as f:
        for line in result:
            f.write(','.join([line['event']] + map(str, line['count'])))
            f.write('\n')

def execute():
    disable_layout_randomization()

    parser = argparse.ArgumentParser(description='Automated perf runner')
    parser.add_argument('program', help='program to be run')
    parser.add_argument('-e', '--event_file', default='pc')
    parser.add_argument('-o', '--output', default='stat.dat')
    parser.add_argument('-n', '--num', default=2)
    parser.add_argument('-r', '--repeat', default=5)
    
    args = parser.parse_args()

    n = int(args.num)

    # Store result, total events for each performance counter
    events, res = [], []
    for line in open(args.event_file):
        code, name = line.strip().split('\t')
        code = ''.join(['r', code, ':u'])
        events.append(code)
        res.append({'event': code, 'mnemonic': name, 'count': [0]*n, 'diff': [0]*n})

    for run in range(n):

        # Clear temporary storage for perf output
        fn = ''.join(['stat.', str(run), '.dat'])
        subprocess.call('cp /dev/null '+fn, shell=True)

        # Sample events in batches of 8
        for i in range(0, len(events), general_purpose_counters):
            events_string = ','.join(events[i:i+general_purpose_counters])
            command = ' '.join(['perf stat -r', str(args.repeat), '-x","', '-e', events_string, args.program, '0>>', fn])
            subprocess.call(command, shell=True)

        # Update results
        with open(fn, 'r') as f:
            for i in range(len(res)):
                line = f.readline()
                if (line.find("<not counted>") == -1):
                    count, _, diff = line.strip().split(',')
                    res[i]['count'][run] = int(count)
                    res[i]['diff'][run] = float(diff[:-1])

    export_csv(res, args.output)

if __name__ == '__main__':
    execute()

