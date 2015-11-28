#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# second.py

from sys import argv
memory = []
page_dict = {}


def second_chance(current_page):
    # print 'Trying to insert page {} into {}'.format(current_page, memory)
    for page in memory[:]:
        if page_dict[page] == 1:
            # print 'Clearing R bit from page', page
            page_dict[page] = 0
            memory.remove(page)
            memory.append(page)

        else:
            # print 'Removing page {} to insert page {}'.format(page,
            # current_page)
            memory.remove(page)
            memory.append(current_page)
            page_dict[current_page] = 1
            return True
    return False


def main():
    PAGE_AMOUNT = int(argv[1])
    FILE = argv[2]
    page_faults = 0

    with open(FILE, "r") as INPUT:
        memory_accesses = INPUT.read().split()
        page_requests = [page.split(":")[1] for page in memory_accesses]

    for page in page_requests:
        if page not in memory:
            # print 'Page Fault #{} with page: {}'.format(page_faults + 1,
            # page)
            if len(memory) >= PAGE_AMOUNT:
                page_fault_fixed = False
                while not page_fault_fixed:
                    page_fault_fixed = second_chance(page)

                page_faults += 1

            else:
                page_dict[page] = 1
                memory.append(page)
                page_faults += 1

    print "PF:{}".format(page_faults)

if __name__ == "__main__" and len(argv) == 3:
    main()

else:
    print(
        "Usage: $ python %s <Number of memory page requests> <access file>" % argv[0])
