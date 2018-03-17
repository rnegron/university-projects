#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# fifo.py

from sys import argv

def first_come(processes):
    acumulator = 0
    # Initialize total_sum as a float for precision in later division.
    total_sum = 0.0
    # Go through every process in the list.
    for i in range(len(processes)):
        # Use acumulator to keep track of the job times and simply
        # output them as they come.
        acumulator += processes[i]
        total_sum += acumulator
        print('P{}:{}'.format(i + 1, acumulator))

    print('Avg:{}'.format(total_sum / len(processes)))

def main():
    input_file = argv[1]
    # Open the file file for reading and automatically close it.
    with open(input_file, 'r') as inp:
        # Use a list comprehension to populate processes with all lines
        # in the input file, which should be ints.
        processes = [int(proc) for proc in inp.readlines()]
    
    first_come(processes)

if __name__ == '__main__' and len(argv) == 2:
    main()
