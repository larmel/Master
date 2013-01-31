#!/usr/bin/env python
import matplotlib.pyplot as plt


def run():
    plt.figure(1, facecolor='white', edgecolor='white')
    plt.subplot(111)

    with open('stat.dat') as f:
        for line in f.readlines():
            w = line.split(',')
            event = w[0]
            data = map(int, w[1:])
            plt.plot(data, label=event)
    plt.grid(True)
    plt.legend()

    plt.show()


if __name__ == '__main__':
	run()
