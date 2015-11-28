#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# optimal.py

from sys import argv
memory = []


def optimize(current_page, future_pages):
    """
    Given the page needed to insert and the future page requests,
    this function will find the best page to evict from memory and
    perform the necessary actions.
    """

    # If there are no more page requests after the current one,
    # it does not matter which page is evicted from memory.
    if len(future_pages) == 0:
        #! print 'Since there are no more future requests, arbirtarily removing the oldest page in memory'
        memory.pop(0)
        memory.append(current_page)

    else:
        #! print 'Need to put {} in {} and checking {}'.format(current_page, memory, future_pages)

        # Dictionary of the form PAGE:BIGGEST_INDEX_IN_FUTUE_PAGES
        memory_dict = {page:None for page in memory}

        # For every page in a copy of memory, we must check
        # if it is a possible candidate for removal
        for page in memory[:]:
            if page not in future_pages:
                #! print 'Since its never used again, removing', page
                memory.remove(page)
                return

            else:
                # If the page is used in the future, mark its index
                # and save it in the dictionary
                idx = future_pages.index(page)
                memory_dict[page] = idx

        # The optimal page to remove from memory is the one whose index
        # in the future page list is the max.
        optimal = max(memory_dict, key=memory_dict.get)

        #! print "Optimally, I should remove", optimal
        memory.remove(optimal)


def main():
    PAGE_AMOUNT = int(argv[1])
    FILE = argv[2]
    page_faults = 0

    # Open file and parse input
    with open(FILE, "r") as INPUT:
        memory_accesses = INPUT.read().split()
        page_requests = [page.split(":")[1] for page in memory_accesses]

    # Loop through every page request and add them to memory or deal with
    # the page fault optimally
    for idx, page in enumerate(page_requests):
        if page not in memory:
            #! print 'Page Fault #{} with page: {}'.format(page_faults + 1, page)
            if len(memory) >= PAGE_AMOUNT:
                optimize(page, page_requests[idx + 1:])

            memory.append(page)
            page_faults += 1

    # Finally, output the number of page faults that occured
    print 'Page Faults:{}'.format(page_faults)

if __name__ == "__main__" and len(argv) == 3:
    main()

else:
    print("Usage: $ python %s <Number of memory page requests> <access file>" % argv[0])
