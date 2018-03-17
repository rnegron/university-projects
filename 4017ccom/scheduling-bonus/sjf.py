#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# sjf.py

from sys import argv

def shortest_job(processes):
    acumulator = 0
    # Initialize total_sum as a float for later division.
    total_sum = 0.0
    # proc_pairs is a list of tuples of the form: (process number, CPU time).
    proc_pairs = [(proc + 1, time) for proc, time in enumerate(processes)]

    # Sort the proc_pairs by their second component (time) and assign
    # the new list to sorted_tuples.
    sorted_tuples = sorted(proc_pairs, key = lambda time: time[1])

    # output_dic is a mapping between the process number (key) and its
    # execution time (value). The execution time is initialized to 0.
    output_dic = {proc + 1 : 0 for proc, time in enumerate(processes)}

    for i in range(len(processes)):
        # Go through every process in the list and acumulate their job time,
        # which is the second component of the ith tuple.
        acumulator += sorted_tuples[i][1]
        total_sum += acumulator

        # Assign the mapping between the process which just ran and the
        # execution time, which is stored in acumulator.
        output_dic[sorted_tuples[i][0]] = acumulator

    # Using the built-in iter function for compatability with python3.
    for proc, time in iter(output_dic.items()):
        print('P{}:{}'.format(proc, time))

    print('Avg:{}'.format(total_sum / len(processes)))

def main():
    input_file = argv[1]
    # Open the file file for reading and automatically close it.
    with open(input_file, 'r') as inp:
        # Use a list comprehension to populate processes with all lines
        # in the input file, which should be ints.
        processes = [int(proc) for proc in inp.readlines()]

    shortest_job(processes)

if __name__ == '__main__' and len(argv) == 2:
    main()
