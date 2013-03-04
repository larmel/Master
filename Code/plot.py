#!/usr/bin/env python
import matplotlib.pyplot as plt
import argparse
from string import lower

def parse_arguments():
    parser = argparse.ArgumentParser(description='Plot perf data')
    parser.add_argument('-e', '--event_list', default='all')
    parser.add_argument('-f', '--file', default='stat.csv', help='csv data to plot from')
    args = parser.parse_args()
    e = map(lower, args.event_list.strip().split(','))
    f = args.file
    return e, f

def read_file(events, filename):
    lines = []
    with open(filename) as f:
        for line in f:
            e = map(lambda s : s.strip(), line.split(','))
            if events == ['all'] or e[1].lower() in events:
                lines.append({'mnemonic': e[0], 'event': e[1], 'count': map(float, e[3:])})
    return lines

def plot_lines(title, data):
    plt.figure(title, facecolor='white', edgecolor='white')
    plt.subplot(111)
    for line in data:
        label = line['event'] if line['mnemonic'] == '' else line['mnemonic']
        plt.plot(line['count'], label=label)
    plt.grid(True)
    plt.legend()
    plt.show()

def run():
    events, filename = parse_arguments()
    lines = read_file(events, filename)
    title = filename;
    plot_lines(title, lines) 

if __name__ == '__main__':
    run()