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
            e = line.strip().split(',')
            if events == 'all' or e[1].lower() in events:
                lines.append({'mnemonic': e[0], 'event': e[1], 'count': map(int, e[2:-1])})
    return lines

def plot_lines(data):
    plt.figure(1, facecolor='white', edgecolor='white')
    plt.subplot(111)
    for line in data:
        plt.plot(line['count'], label=line['mnemonic'])
    plt.grid(True)
    plt.legend()
    plt.show()

def run():
    events, filename = parse_arguments()
    lines = read_file(events, filename)
    plot_lines(lines) 

if __name__ == '__main__':
    run()