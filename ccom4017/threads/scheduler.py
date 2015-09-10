#!/usr/bin/env python

import Queue
import socket
import threading
from sys import argv


HOST = 'localhost'
MAX_CONNECTIONS = 5
MAX_MESSAGES = 5
BUFFER_SIZE = 4096


def produce(shared_queue):

    # initalizes to the defaults; address family AF_INET and type SOCK_STREAM
    serverSocket = socket.socket()

    port = argv[1]
    amount_messages = 0

    serverSocket.bind((HOST, int(port)))
    serverSocket.listen(MAX_CONNECTIONS)

    (clientSocket, address) = serverSocket.accept()

    while amount_messages < 5:
        msg = clientSocket.recv(BUFFER_SIZE)
        split = msg.find(':')
        print 'Mobile {} sent CPU time = {}s'.format(msg[:split], msg[split + 1:])
        amount_messages += 1

    clientSocket.shutdown(socket.SHUT_RDWR)
    clientSocket.close()


def consume(shared_queue):
    pass


def main():
    if len(argv) < 2:
        print 'Usage: $ python {} <server port>'.format(argv[0])
        return

    queue = Queue.Queue()
    pThread = threading.Thread(target=produce, name='producer', args=(queue,))
    cThread = threading.Thread(target=consume, name='consumer', args=(queue,))

    pThread.start()
    cThread.start()

if __name__ == '__main__':
    main()

"""
TODO

Better variable names
Implement safe IPC

"""
