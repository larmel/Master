#!/usr/bin/env python
import matplotlib.pyplot as plt


def run():
    plt.figure(1, facecolor='white', edgecolor='white')
    plt.subplot(111)
    plt.plot([30, 60, 100, 200], label='cycles:u')
    plt.plot([1, 2, 3, 4], label='instrucctions:u')
    plt.grid(True)
    plt.legend()

    plt.show()




if __name__ == '__main__':
	run()
