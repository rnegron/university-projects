#!/usr/bin/env python

from random import uniform as random_interval
from sys import argv
import socket
import time

# global variable definitions
PRECISION = 2
MIN_CPU_TIME = 1.0
MAX_CPU_TIME = 4.0
MIN_SLEEP_TIME = 1.0
MAX_SLEEP_TIME = 3.0


def main():
    if len(argv) < 4:
        print 'Usage: $ python {} <mobileID> <server address> <server port>'.format(argv[0])
        return

    # unpack command line arguments
    script, mobileID, address, port = argv

    # initalizes to the defaults; address family AF_INET and type SOCK_STREAM
    clientSocket = socket.socket()
    clientSocket.connect((address, int(port)))

    while True:
        mobileCPU = round(random_interval(
            MIN_CPU_TIME, MAX_CPU_TIME), PRECISION)

        try:
            clientSocket.send("{}:{}".format(mobileID, mobileCPU))
            print 'Mobile {} sending CPU time = {}s'.format(mobileID, mobileCPU)
        except socket.error:
            print 'Connection closed'
            break

        time.sleep(random_interval(MIN_SLEEP_TIME, MAX_SLEEP_TIME))


if __name__ == "__main__":
    main()
