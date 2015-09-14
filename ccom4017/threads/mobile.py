#!/usr/bin/env python
#-*- coding: utf8 -*-

"""

mobile.py

Raúl Negrón Otero
# 801-13-4680
CCOM4017 - Dr. J. Ortiz-Ubarri
September 15, 2015

"""

from random import uniform as random_interval
from sys import argv
import socket
import time

PRECISION = 2
MIN_CPU_TIME = 1.0
MAX_CPU_TIME = 5.0
MIN_SLEEP_TIME = 1.0
MAX_SLEEP_TIME = 3.0


def main():

    # check to see if the script was called correctly
    # if not, return and do nothing
    if len(argv) < 4:
        print 'Usage: $ python {} <mobileID> <server address> <server port>'.format(argv[0])
        return

    script, mobileID, address, port = argv  # unpack command line arguments

    # initalizes to the default address family: AF_INET and uses type: UDP
    clientSocket = socket.socket(type=socket.SOCK_DGRAM)

    # configure the socket to allow port recycling
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

    # main loop which sends data through the server socket
    while True:

        # randomize a floating point number to symbolize CPU time
        mobileCPU = round(random_interval(
            MIN_CPU_TIME, MAX_CPU_TIME), PRECISION)

        # send data through as a string
        sent = clientSocket.sendto("{}:{}".format(
            mobileID, mobileCPU), (address, int(port)))

        print 'Mobile {} sending CPU time = {}s'.format(mobileID, mobileCPU)

        # wait a random amount of time interval between sends
        time.sleep(random_interval(MIN_SLEEP_TIME, MAX_SLEEP_TIME))

    return

if __name__ == "__main__":
    main()
