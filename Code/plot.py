#!/usr/bin/env python
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
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
    fontP = FontProperties()
    fontP.set_size('small')
    plt.figure(title, figsize=(13,5), facecolor='white', edgecolor='white')
    ax = plt.subplot(111)
    for line in data:
        label = line['event'] if line['mnemonic'] == '' else line['mnemonic']
        plt.plot(line['count'], label=label)
    plt.grid(True)
    # Shink current axis by 20%
    box = ax.get_position()
    legend = plt.legend(loc="upper left", bbox_to_anchor=(1.01,1.0), borderaxespad=0., prop=fontP)
    ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])
    plt.show()

def run():
    events, filename = parse_arguments()
    lines = read_file(events, filename)
    title = filename;
    plot_lines(title, lines) 

if __name__ == '__main__':
    run()