#!/usr/bin/env python
#-*- coding: utf8 -*-

"""

scheduler.py

Raúl Negrón Otero
# 801-13-4680
CCOM4017 - Dr. J. Ortiz-Ubarri
September 15, 2015

"""

import Queue
import socket
import threading
import time
from sys import argv

HOST = 'localhost'
MAX_MESSAGES = 10
BUFFER_SIZE = 4096


class Producer(threading.Thread):  # define the Producer thread class

    def __init__(self, shared_queue, shared_semaphore, shared_event, port):
        threading.Thread.__init__(self)
        self.name = 'Producer-Thread'
        self.queue = shared_queue
        self.semaphore = shared_semaphore
        self.event = shared_event
        self.port = int(port)

    def produce(self, first=False):

        # get the data from the client socket
        item, address = self.serverSocket.recvfrom(BUFFER_SIZE)

        # store the data to be consumed later by the other thread
        # protect the critical region with a semaphore
        with self.semaphore:
            self.queue.put(item)
            # DEBUG
            print '{} put an item into the queue - {}'.format(self.name, item)
            self.amount_messages += 1

        if first:  # if it is the first time produce is run, notify the consumer
            self.event.set()
            print self.name + ' set the event'  # DEBUG

    def run(self):
        """
        the run function for the producer listens on a port and stores incoming
        data to the shared queue, then sleeps for a predetermined amount of time
        """

        print self.name + ' is running now'  # DEBUG

        # initalizes to the default address family: AF_INET and uses type: UDP
        self.serverSocket = socket.socket(type=socket.SOCK_DGRAM)

        # configure the socket to allow port recycling
        self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

        # make the socket check the specified server address and port
        self.serverSocket.bind((HOST, self.port))

        # counting variable to stop after MAX_MESSAGES have been received
        self.amount_messages = 0

        # run the produce() function for the first time, notifying the consumer
        self.produce(True)

        # main producer loop which receives data and stores it
        while self.amount_messages < MAX_MESSAGES:
            self.produce()

        # after amount_messages == MAX_MESSAGES, close the socket and return
        self.serverSocket.close()
        print self.name + ' closed the socket'  # DEBUG
        return


class Consumer(threading.Thread):  # define the Consumer thread class

    def __init__(self, shared_queue, shared_semaphore, shared_event, results):
        threading.Thread.__init__(self)
        self.name = 'Consumer-Thread'
        self.queue = shared_queue
        self.semaphore = shared_semaphore
        self.event = shared_event
        self.results = results

    def run(self):
        """
        the run function for the consumer retrieves items from the queue and
        stores the results in a dictionary, then sleeps for the retreived
        amount of time
        """

        self.messages_left = MAX_MESSAGES  # count down the remaining messages

        print self.name + ' is waiting now'  # DEBUG
        self.event.wait()  # wait for the Producer to singal an item in the queue

        while True:  # main consumer loop which gets an item and stores it

             # if we received them all, break and return
            if self.messages_left == 0:
                break

            else:

                # get an item from the queue and decrement the counter
                # protect critical region with a semaphore
                with self.semaphore:
                    item = self.queue.get()

                    print '{} got an item - {}'.format(self.name, item) # DEBUG
                    self.messages_left -= 1

                mobileID, mobileCPU = item.split(
                    ':')  # decode the received item

                # if this is a new Mobile, create a new key and store CPU time
                if mobileID not in self.results:
                    self.results[mobileID] = float(mobileCPU)

                # otherwise add the new CPU time to the overall CPU time
                else:
                    self.results[mobileID] += float(mobileCPU)

                # sleep the extracted amount of seconds
                time.sleep(float(mobileCPU))

        return


def main():

    # check to see if the script was called correctly
    # if not, return and do nothing
    if len(argv) < 2:
        print 'Usage: $ python {} <server port>'.format(argv[0])
        return

    port = argv[1]  # get port number from command line arguments
    results = {}    # initialize the results dicitonary to the empty dict

    queue = Queue.Queue()
    semaphore = threading.Semaphore()
    event = threading.Event()

    # initialize the Producer and Consumer threads
    pThread = Producer(queue, semaphore, event, port)
    cThread = Consumer(queue, semaphore, event, results)

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
