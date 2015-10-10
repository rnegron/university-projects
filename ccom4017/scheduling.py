#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# scheduling.py


"""
TODO
- General cleanup
- FCFS sorted output
- Check and add comments
"""

# Global, boilerplate output string
OUTPUT = 'Process #{} took {} seconds.\n'
PROC_LIST = [5, 9, 2, 0, 5]
QUANTUM = 4

def first_come(processes):
    print('--- First come, first served ---\n')
    acumulator = 0
    # Go through every process in the list.
    for i in range(len(processes)):
        # Use acumulator to keep track of the job times and simply
        # output them as they come.
        acumulator += processes[i]
        print(OUTPUT.format(i + 1, acumulator))

def shortest_job(processes):
    print('--- Shortest job first ---\n')
    acumulator = 0
    # proc_pairs is a list of tuples of the form: (process number, CPU time).
    proc_pairs = [(proc + 1, time) for proc, time in enumerate(processes)]

    # Sort the proc_pairs by their second component (time) and assign
    # the new list to sorted_tuples.
    sorted_tuples = sorted(proc_pairs, key = lambda time: time[1])

    for i in range(len(processes)):
        # Go through every process in the list and acumulate their job time,
        # which is the second component of the ith tuple. Then output.
        acumulator += sorted_tuples[i][1]
        print(OUTPUT.format(sorted_tuples[i][0], acumulator))

def round_robin(processes, quantum):
    print('--- Round robin ---\n')
    acumulator = 0
    proc_nest = [[proc + 1, time] for proc, time in enumerate(processes)]
    proc_table = {proc + 1 : 0 for proc in range(len(processes))}

    # A list in a boolean context is true only if it has at least one
    # element. This loop runs until proc_pairs is empty.
    while True:
        proc_changed = False
        for i in range(len(processes)):
            if proc_nest[i][1] == 0:
                continue

            elif proc_nest[i][1] <= quantum:
                acumulator += proc_nest[i][1]
                proc_table[i + 1] += acumulator
                proc_nest[i][1] = 0
                proc_changed = True

            else:
                acumulator += quantum
                proc_table[i + 1] += acumulator
                proc_nest[i][1] -= quantum
                proc_changed = True

        if not proc_changed:
            break

    for proc, time in proc_table.iteritems():
        print(OUTPUT.format(proc, time))

def main():
    shortest_job(PROC_LIST)
    first_come(PROC_LIST)
    round_robin(PROC_LIST, QUANTUM)

if __name__ == '__main__':
    main()
