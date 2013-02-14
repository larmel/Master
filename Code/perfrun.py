#!/usr/bin/env python 
import subprocess
import argparse
import sys
from scipy import stats

# $ ./perfrun.py Empty/a.out -e cycles:u,instructions:u -n 100 > Empty/stat.dat

# Number of counters (Sandy Bridge and Ivy Bridge), Section 18.8
# With HT off, 2*4 general purpose counters are visible per core
# Rules seems complicated. Strategy: run 8 counters at a time, hopefully no multiplexing.
# Need to verify that this is done correctly
# Note: On > 8, some counters are 0. Seems like they are multiplexed and missed or something
fixed_counters = 3
general_purpose_counters = 8

def disable_layout_randomization():
    subprocess.call('sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"', shell=True)

# Reads a file containing event info, and filters out the events specified
# in eventarg. If eventarg is empty, all events are counted.
def filter_events(filename, eventarg):
    include = eventarg.strip().lower().split(',')
    events = []
    for line in open(filename):
        code, perfmn, name = line.strip().split('\t')
        code = ''.join(['r', code.lower(), ':u']) if perfmn == '' else perfmn+':u'
        if eventarg == '' or code in include:
            events.append({'code': code, 'perfmn': perfmn, 'mnemonic': name})
        if code in include:
            include.remove(code)
    if len(include) > 0:
        print "Adding unknown event(s)", ', '.join(include)
        for e in include:
            events.append({'code': e, 'perfmn': '', 'mnemonic': ''})
    return events

def benchmark(events, runs, repeat, program, increment):
    for e in events:
        e['count'] = [0]*runs
        e['variance'] = [0]*runs

    environment = {'FOO':'0'*3220}

    for run in range(runs):
        subprocess.call('cp /dev/null stat.tmp.dat', shell=True)
        environment['FOO'] += '0'*increment

        # Sample events in batches of 8
        for i in range(0, len(events), general_purpose_counters):
            e = ','.join(map(lambda x: x['code'], events[i:i+general_purpose_counters]))
            c = ' '.join(['perf stat -r', str(repeat), '-x","', '-e', e, program, '0>> stat.tmp.dat'])
            p = subprocess.Popen(c, env=environment, shell=True)
            p.wait()

        # Update results after all events are counted
        with open('stat.tmp.dat', 'r') as f:
            for i in range(len(events)):
                line = f.readline().strip().split(',')
                if (line[0] == "<not counted>"):
                    continue
                events[i]['count'][run] = int(line[0])
                if repeat > 1:
                    events[i]['variance'] = float(line[2][:-1])
    return events

def correlation(events, reference_event):
    reference = events[0]
    for i in range(1, len(events)):
        if events[i]['code'] == reference_event or events[i]['perfmn'] == reference_event:
            reference = events[i]
            break
    for e in events:
        e['pearson'], _ = stats.pearsonr(reference['count'], e['count'])

def export_csv(events, filename):
    with open(filename, 'w') as f:
        for line in events:
            row = [line['mnemonic'], line['code']] + [line['pearson']] + map(str, line['count'])
            f.write(','.join(map(str, row)))
            f.write('\n')

def execute():
    parser = argparse.ArgumentParser(description='Automated perf runner')
    parser.add_argument('program', help='program to be run')
    parser.add_argument('-e', '--events', default='')
    parser.add_argument('-f', '--event_file', default='../counters')
    parser.add_argument('-o', '--output', default='stat.csv')
    parser.add_argument('-n', '--num', default=2)
    parser.add_argument('-r', '--repeat', default=1)
    parser.add_argument('-c', '--correlate', default='cycles:u')
    parser.add_argument('-i', '--increment', default=1)
    args = parser.parse_args()

    # Make memory layout deterministic    
    disable_layout_randomization()

    # List of event properties [[code, perfmnemonic, description]]
    events = filter_events(args.event_file, args.events)

    # Run benchmarks
    events = benchmark(events, int(args.num), int(args.repeat), args.program, int(args.increment))

    # Export result
    correlation(events, args.correlate)
    export_csv(events, args.output)

if __name__ == '__main__':
    execute()
