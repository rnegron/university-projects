#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# second.py

from sys import argv
memory = []
page_dict = {}  # Dictionary of the form PAGE:R_BIT


def second_chance(current_page):
    """
    Given the page needede to insert into memory, this function will
    search for a page to remove and make room by checking the R bits
    of the pages in memory and re-arranging them as necessary.

    The function will return a bool value since it used many times inside
    a conditional loop.
    """
    #! print 'Trying to insert page {} into {}'.format(current_page, memory)

    # For every page in a copy of memory, we must check
    # if it is a possible candidate for removal
    for i in xrange(len(memory)):

        # Always check the page at the beginning of the list
        page = memory[0]

        # If the page has R == 1, then we must clear the bit and put the page
        # at the tail of the list
        if page_dict[page] == 1:
            #! print 'Clearing R bit from page', page
            page_dict[page] = 0
            memory.append(memory.pop(0))

        # If the page has R == 0, then that page should be removed to make
        # space for current_page.
        else:
            #! print 'Removing page {} to insert page {}'.format(page, current_page)
            memory.pop(0)
            memory.append(current_page)
            page_dict[current_page] = 1
            return True

    return False


def main():
    MEMORY_SIZE = int(argv[1])
    FILE = argv[2]
    page_faults = 0

    # Open file and parse input
    with open(FILE, "r") as INPUT:
        memory_accesses = INPUT.read().split()
        page_requests = [page.split(":")[1] for page in memory_accesses]

    # Loop through every incoming page request
    for page in page_requests:
        # If the page is not in memory, it will trigger a page fault
        if page not in memory:
            page_faults += 1
            #! print 'Page Fault #{} with page: {}'.format(page_faults, page)

            # If there is no room in memory, run the second chance algorithm
            if len(memory) >= MEMORY_SIZE:
                page_fault_fixed = False

                # The algorithm will run until page_fault_fixed is True
                while not page_fault_fixed:
                    page_fault_fixed = second_chance(page)

            # If there is sufficient room in memory, just place the page in
            else:
                page_dict[page] = 1  # Set R bit of incoming page
                memory.append(page)

    # Finally, output the number of page faults that occured
    print page_faults

if __name__ == "__main__" and len(argv) == 3:
    main()

else:
    print("Usage: $ python %s <Number of memory page requests> <access file>" % argv[0])
