def first_come(processes):
    print('\tFirst come, first served\n')
    process_table = {process + 1:time for process, time in enumerate(processes)}
    acumulator = 0
    for i in range(len(processes)):
        idx = i + 1
        acumulator += process_table[idx]
        process_table[idx] = acumulator
        print('Process #{} took {} seconds.\n'.format(idx, process_table[idx]))

def shortest_job(processes):
    print('\tShortest job first\n')
    process_table = {process + 1:time for process, time in enumerate(processes)}
    shortest_list = sorted(processes)
    acumulator = 0
    for i in range(len(shortest_list)):
        acumulator += shortest_list[i]
        print('... took {} seconds.\n'.format(acumulator))
        
def round_robin(processes, quantum):
    pass

def main():
    shortest_job([5, 8, 10, 3, 10])
    first_come([5, 8, 10, 3, 10])

if __name__ == '__main__':
    main()
