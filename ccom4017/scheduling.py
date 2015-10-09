#!/usr/bin/env python

def first_come(processes):
    print('\tFirst come, first served\n')
    acumulator = 0
    for i in range(len(processes)):
        acumulator += processes[i]
        print('Process #{} took {} seconds.\n'.format(i + 1, acumulator))

def shortest_job(processes):
    print('\tShortest job first\n')
    process_tuples = [(process + 1, time) for process, time in enumerate(processes)]
    sorted_tuples = sorted(process_tuples, key=lambda time: time[1])
    acumulator = 0
    for i in range(len(processes)):
        acumulator += sorted_tuples[i][1]
        print('Process #{} took {} seconds.\n'.format(sorted_tuples[i][0], acumulator))

def round_robin(processes, quantum):
    print('\tRound Robin\n')
    pass

def main():
    process_list = [5, 1]
    shortest_job(process_list)
    first_come(process_list)

if __name__ == '__main__':
    main()
