#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Raúl E. Negrón
# 801-13-4680
# CCOM4017
# wsclock.py

from sys import argv
memory = []
clock = 0


class wsclock_structure:
    """
    Implementation of the circular list idea, where a clock hand (index)
    points to the scheduled page to check. This class also allows for
    modification of page_record objects since they are stored in a local
    list (c_list).
    """

    def __init__(self):
        self.c_list = []
        self.index = 0  # Initially, point to the soon-to-be first element

    # Resets every R bit at each clock tick
    def reset_rbit(self):
        for page in self.c_list:
            page.clear_rbit()

    # Adds a page record to the end of the list
    def append(self, page_record):
        self.c_list.append(page_record)

    # Receives an incoming page and replaces the current indexed page by it
    def overwrite(self, new_page_record):
        # The current working page is index - 1 since we already moved the hand
        self.c_list[self.index - 1] = new_page_record

    # Given a page which was referenced and is in memory, updates the page info
    def referenced(self, page_to_update, should_write):
        for idx, current_page_record in enumerate(self.c_list):
            if current_page_record.get_page() == page_to_update:
                # Set the R bit and update the time to the current clock
                self.c_list[idx].change_time()
                self.c_list[idx].set_rbit()
                if should_write:
                    # If it came in a 'W' command, set the M bit, too
                    self.c_list[idx].set_mbit()
                return

    def get_size(self):
        return len(self.c_list)

    # Returns the page record pointed to by the clock hand and moves the hand
    def get_next(self):
        next_page_record = self.c_list[self.index]
        self.index = (self.index + 1) % len(self.c_list)
        return next_page_record


class page_record:
    """
    Simple container structure for pages which allows access and modification
    of the important attributes.
    """

    def __init__(self, page,):
        self.page = page
        self.time = clock
        self.r_bit = 0
        self.m_bit = 0

    def get_page(self):
        return self.page

    def get_time(self):
        return self.time

    def change_time(self):
        self.time = clock

    def get_rbit(self):
        return self.r_bit

    def get_mbit(self):
        return self.m_bit

    def set_rbit(self):
        self.r_bit = 1

    def set_mbit(self):
        self.m_bit = 1

    def clear_rbit(self):
        self.r_bit = 0

    def clear_mbit(self):
        self.m_bit = 0


def wsclock(new_page_record, tau, clock_list, second_run=False):
    """
    Function which uses a circularly linked list to simulate the wsclock
    page replacement algorithm. There is a second_run parameter which, if
    not specified, is initiliazed to False.  If it is true, this function
    will fix the page fault by claiming the first free page in the list. Else,
    it will try to find a clean page to evict which is not in the working set
    by comparing each page's age with the tau parameter. If it finds pages with
    R or M bits on, it clears them and advanced the clock hand. It returns a
    boolean value, which specifies if the page fault was fixed or not.
    By returning False, the function can be run again by the callee, thus
    claiming the first clean page.
    """

    # Loop which runs as many times as there are page_records
    for i in xrange(clock_list.get_size()):
        # Inspect the current page_record and move the clock hand for next time
        clock_page_record = clock_list.get_next()

        if clock_page_record.get_rbit() == 1:
            # Simply clear the R bit and move on to the next page_record
            #! print 'Clearing the R bit of page', clock_page_record.get_page()
            clock_page_record.clear_rbit()

        else:
            if second_run:
                # If this is the second time the algorithm runs, simply claim
                # the current page, which is the first clean one.
                memory.remove(clock_page_record.get_page())
                memory.append(new_page_record.get_page())
                #! print 'Claiming the first clean page:', clock_page_record.get_page()

                # Put the new page_record where the old one was and return True
                clock_list.overwrite(new_page_record)
                return True

            # Since the R bit is 0, we must compare the page age to Tau
            page_age = clock - clock_page_record.get_time()

            if page_age > tau:
                # If the page is older than Tau, it is candidate for removal
                if clock_page_record.get_mbit() == 0:
                    # Since the page is clean and old, it should be removed
                    #! print 'Found an "old, clean" page. {} has age: {}'.format(clock_page_record.get_page(), page_age)

                    # Remove this page from memory and add the incoming page
                    memory.remove(clock_page_record.get_page())
                    memory.append(new_page_record.get_page())

                    # Put the new page_record where the old one was and return
                    clock_list.overwrite(new_page_record)
                    return True

                else:
                    # Page is old but dirty, it must be written first
                    write_to_disk()
                    clock_page_record.clear_mbit()

    # In case no good page was found during the search, return False
    # This way, the algorithm can be run anew, and there is now at least one
    # old, clean page in memory. By running wsclock again, we may claim it.
    return False

# Dummy function to simulate I/O
def write_to_disk():
    pass


def main():
    # Read in command line arguments
    MEMORY_SIZE = int(argv[1])
    TAU = int(argv[2])
    FILE = argv[3]

    # Using the global clock, initialize other data
    global clock
    page_faults = 0
    clock_list = wsclock_structure()

    # Open file and parse input
    with open(FILE, "r") as INPUT:
        memory_accesses = INPUT.read().split()

    # For every incoming page request...
    for request in memory_accesses:
        # Clock ticks forward
        clock += 1
        # We must reset the R bits of in-memory pages at each clock tick
        clock_list.reset_rbit()

        #! print '\nThe current time is:', clock
        command, page = request.split(':')

        if page not in memory:
            # The definition of a page fault has occured
            page_faults += 1
            #! print 'Page fault #{} with page: {}'.format(page_faults, page)
            #! print 'Memory before page fault is fixed:', memory

            if len(memory) < MEMORY_SIZE:
                # If there is enough space, simply place page in memory
                memory.append(page)
                clock_list.append(page_record(page))

            else:
                # If there is not enough space, page-replacement is due
                page_fault_fixed = wsclock(page_record(page), TAU, clock_list)

                # If the first run of wsclock did not find a good page, run
                # it again and always claim the first free page.
                if not page_fault_fixed:
                    wsclock(page_record(page), TAU, clock_list, second_run=True)

            #! print 'Memory after page fault is fixed:', memory


        else:
            # Page is in memory and we just referenced it
            # So turn on the R bit and maybe the M bit
            if command == 'W':
                clock_list.referenced(page, should_write=True)
            else:
                clock_list.referenced(page, should_write=False)

    # Finally, output the number of page faults that occured
    print "Page Faults:{}".format(page_faults)

if __name__ == "__main__" and len(argv) == 4:
    main()

else:
    print("Usage: $ python %s <Number of memory page requests> <tau> <access file>" % argv[0])
