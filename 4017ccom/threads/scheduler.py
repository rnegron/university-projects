#!/usr/bin/env python
#-*- coding: utf8 -*-

"""

scheduler.py

Raúl Negrón Otero
# 801-13-4680
CCOM4017 - Dr. J. Ortiz-Ubarri
September 15, 2015

"""

import socket
import threading
import time
from collections import deque
from sys import argv

HOST = 'localhost'
MAX_MESSAGES = 15
BUFFER_SIZE = 4096


class Producer(threading.Thread):  # define the Producer thread class

    def __init__(self, shared_buffer, empty_semaphore, full_semaphore,
                 binary_semaphore, port):

        threading.Thread.__init__(self)
        self.name = 'Producer-Thread'
        self.buffer = shared_buffer
        self.empty_semaphore = empty_semaphore
        self.full_semaphore = full_semaphore
        self.binary_semaphore = binary_semaphore
        self.port = int(port)
        self.debug = '{} put an item - Mobile {} sent {}s'

    def run(self):
        """
        the run function for the producer listens on a port and stores incoming
        data to the shared buffer, then sleeps for a predetermined amount of time
        """

        print self.name + ' is running now'

        # initalizes to the default address family: AF_INET and uses type: UDP
        self.serverSocket = socket.socket(type=socket.SOCK_DGRAM)

        # configure the socket to allow port recycling
        self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

        # make the socket check the specified server address and port
        self.serverSocket.bind((HOST, self.port))

        # counting variable to stop after MAX_MESSAGES have been received
        self.amount_messages = 0

        # main producer loop which receives data and stores it
        while self.amount_messages < MAX_MESSAGES:

            # get the data from the client socket
            item, address = self.serverSocket.recvfrom(BUFFER_SIZE)

            # store the data to be consumed later by the other thread
            # protect the critical region with semaphores
            self.empty_semaphore.acquire()
            self.binary_semaphore.acquire()
            self.buffer.append(item)
            self.binary_semaphore.release()
            self.full_semaphore.release()

            mobileID, mobileCPU = item.split(':')  # decode the message

            # print a confirmation message
            print self.debug.format(self.name, mobileID, mobileCPU)

            self.amount_messages += 1

        # after amount_messages == MAX_MESSAGES, close the socket and return
        self.serverSocket.close()
        print self.name + ' closed the socket'  # DEBUG
        return


class Consumer(threading.Thread):  # define the Consumer thread class

    def __init__(self, shared_buffer, empty_semaphore, full_semaphore,
                 binary_semaphore, results):
        threading.Thread.__init__(self)
        self.name = 'Consumer-Thread'
        self.buffer = shared_buffer
        self.empty_semaphore = empty_semaphore
        self.full_semaphore = full_semaphore
        self.binary_semaphore = binary_semaphore
        self.results = results
        self.debug = '{} got an item - Mobile {} sent {}s'

    def run(self):
        """
        the run function for the consumer retrieves items from the buffer and
        stores the results in a dictionary, then sleeps for the retreived
        amount of time
        """

        print self.name + ' is running now'

        while True:  # main consumer loop which gets an item and stores it

            # if this is not the only thread (other than the main thread),
            # the producer is still working. This thread must keep working too
            if threading.active_count() != 2:

                # get an item from the buffer and decrement the counter
                # protect critical region with semaphores
                self.full_semaphore.acquire()
                self.binary_semaphore.acquire()
                item = self.buffer.popleft()
                self.binary_semaphore.release()
                self.empty_semaphore.release()

                mobileID, mobileCPU = item.split(':')  # decode the message

                # print a confirmation message
                print self.debug.format(self.name, mobileID, mobileCPU)

                # if this is a new Mobile, create a new key and store CPU time
                if mobileID not in self.results:
                    self.results[mobileID] = float(mobileCPU)

                # otherwise add the new CPU time to the overall CPU time
                else:
                    self.results[mobileID] += float(mobileCPU)

                # sleep the extracted amount of seconds
                time.sleep(float(mobileCPU))

            # if this is the only thread, dont worry about semaphores
            # finish working on the buffer, then break and return
            else:
                while len(self.buffer) > 0:

                    item = self.buffer.popleft()  # get an item from the buffer

                    mobileID, mobileCPU = item.split(':')  # decode the message

                    # print a confirmation message
                    print self.debug.format(self.name, mobileID, mobileCPU)

                    # if this is a new Mobile, create key and store CPU time
                    if mobileID not in self.results:
                        self.results[mobileID] = float(mobileCPU)

                    # otherwise add the new CPU time to the overall CPU time
                    else:
                        self.results[mobileID] += float(mobileCPU)

                    # sleep the extracted amount of seconds
                    time.sleep(float(mobileCPU))

                # break once the consumer is the only thread and is finished
                break
        return


def main():

    # check to see if the script was called correctly
    # if not, return and do nothing
    if len(argv) < 2:
        print 'Usage: $ python {} <server port>'.format(argv[0])
        return

    port = argv[1]  # get port number from command line arguments
    results = {}    # initialize the results dicitonary to the empty dict

    # initialize the objects to send to both threads
    buffer = deque(maxlen=MAX_MESSAGES)
    empty_semaphore = threading.BoundedSemaphore(MAX_MESSAGES)
    full_semaphore = threading.Semaphore(0)
    binary_semaphore = threading.Semaphore()
    shared_event = threading.Event()

    # initialize the Producer and Consumer threads
    pThread = Producer(buffer, empty_semaphore,
                       full_semaphore, binary_semaphore, port)

    cThread = Consumer(buffer, empty_semaphore,
                       full_semaphore, binary_semaphore, results)

    # start both threads
    cThread.start()
    pThread.start()

    # synchronize the threads, each waits for the other
    pThread.join()
    cThread.join()

    for id in results:  # for every Mobile ID received, print results
        print 'Mobile {} consumed {} seconds of CPU time'.format(id, results[id])

    return

if __name__ == '__main__':
    main()
