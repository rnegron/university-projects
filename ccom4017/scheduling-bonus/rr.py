#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# rr.py

from sys import argv

def round_robin(processes, quantum):
    acumulator = 0
    # Initialize total_sum as a float for later division.
    total_sum = 0.0
    # proc_nest is a list of lists of the form: [process number, CPU time].
    proc_nest = [[proc + 1, time] for proc, time in enumerate(processes)]

    # output_dic is a mapping between the process number (key) and its
    # execution time (value). The execution time is initialized to 0.
    output_dic = {proc + 1 : 0 for proc in range(len(processes))}

    # This loop removes
    while len(proc_nest) != 0:
        for i in range(len(proc_nest)):

            # Ignore the edge case where a process takes no time
            if proc_nest[i][1] == 0:
                continue

            # If the time is less than the quantum, use the leftover time
            elif proc_nest[i][1] <= quantum:
                acumulator += proc_nest[i][1]
                total_sum += acumulator
                # The process has now finished executing, save how long
                # it took in the output_dic and signal it for removal.
                output_dic[proc_nest[i][0]] += acumulator
                proc_nest[i][1] = 0

            # The process still has time after this loop, subtract quantum.
            else:
                acumulator += quantum
                proc_nest[i][1] -= quantum

        # Make a new list of lists, this time without the finished processes.
        proc_nest = [[proc, time] for proc, time in proc_nest if time != 0]

    # Using the built-in iter function for compatability with python3.
    for proc, time in iter(output_dic.items()):
        print('P{}:{}'.format(proc, time))

    print('Avg:{}'.format(total_sum / len(processes)))

def main():
    # Store the command-line arguments
    quantum = int(argv[1])
    input_file = argv[2]

    # Open the file file for reading and automatically close it.
    with open(input_file, 'r') as inp:
        # Use a list comprehension to populate processes with all lines
        # in the input file, which should be ints.
        processes = [int(proc) for proc in inp.readlines()]

    round_robin(processes, quantum)

if __name__ == '__main__' and len(argv) == 3:
    main()
