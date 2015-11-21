###############################################################################
#
# Filename: data-node.py
# Author: Jose R. Ortiz and Raul E. Negron
#
# Description:
# 	data node server for the DFS
#

from Packet import *

import sys
import socket
import SocketServer
import uuid
import os.path
from os import mkdir, rmdir


def usage():
    print """Usage: python %s <server> <port> <data path> <metadata port,default=8000>""" % sys.argv[0]
    sys.exit(0)


def register(meta_ip, meta_port, data_ip, data_port):
    """Creates a connection with the metadata server and
       register as data node
    """

    # Establish connection
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # try and connect to the metadata server
    try:
        response = "NAK"
        sp = Packet()
        sock.connect((meta_ip, meta_port))
        while response == "NAK":
            sp.BuildRegPacket(data_ip, data_port)
            sock.sendall(sp.getEncodedPacket())
            response = sock.recv(1024)

            if response == "DUP":
                print "Duplicate Registration"
                rmdir(DATA_PATH)

            if response == "NAK":
                print "Registratation ERROR"
                rmdir(DATA_PATH)

    finally:
        sock.close()


class DataNodeTCPHandler(SocketServer.BaseRequestHandler):

    def handle_put(self, p):
        """Receives a block of data from a copy client, and
           saves it with a unique ID. The ID is then sent back to the
           copy client.
        """
        # Receive the data block info.
        fname, fsize = p.getFileInfo()

        # Acknowledge the received info
        self.request.send("OK")

        # Strng variable which holds the soon to be received binary data
        data = ''

        # Simple progress bar
        loading = {0:'/', 1:'-', 2:'\\', 3:'|'}
        counter = 0

        # Keep receiving data until it is complete
        while len(data) < fsize:
            sys.stdout.write('\rReceiving... {}'.format(loading[counter]))
            data += self.request.recv(4096)
            counter = (counter + 1) % 4
            sys.stdout.flush()

        # Generates an unique block id.
        blockid = str(uuid.uuid1())

        print '\nGot {} bytes'.format(len(data))

        # Write the data to the local chunk using the .dat extension
        with open(os.path.join(DATA_PATH, blockid + '.dat'), 'wb') as f:
            print 'Writing...'
            f.write(data)
            print 'Done writing'

        # Send the block id back
        resp = Packet()
        resp.BuildGetDataBlockPacket(blockid)
        self.request.sendall(resp.getEncodedPacket())

    def handle_get(self, p):

        # Get the block id from the packet
        blockid = p.getBlockID()

        # Read the file with the block id data
        with open(os.path.join(DATA_PATH, blockid + '.dat'), 'rb') as f:
            print 'Reading...'
            fileData = f.read()
            print 'Done reading'

        # Send it back to the copy client.
        self.request.sendall(fileData)

        print 'Sent {} bytes'.format(len(fileData))

    def handle(self):
        """Receive a request from a client and call the corresponding
            handler functions, either put or get
        """

        msg = self.request.recv(524, 288)

        p = Packet()
        p.DecodePacket(msg)
        cmd = p.getCommand()

        if cmd == "put":
            self.handle_put(p)

        elif cmd == "get":
            self.handle_get(p)


if __name__ == "__main__":

    META_PORT = 8000
    if len(sys.argv) < 4:
        usage()

    try:
        HOST = sys.argv[1]
        PORT = int(sys.argv[2])
        DATA_PATH = sys.argv[3]

        if len(sys.argv) > 4:
            META_PORT = int(sys.argv[4])

        if DATA_PATH == "default" or not os.path.isdir(DATA_PATH):
            nodeNum = 1
            while True:
                DATA_PATH = './data{}'.format(nodeNum)
                try:
                    mkdir(DATA_PATH)
                    break
                except OSError:
                    nodeNum += 1
                    continue

    except:
        usage()

    register("localhost", META_PORT, HOST, PORT)
    server = SocketServer.TCPServer((HOST, PORT), DataNodeTCPHandler)

    server.serve_forever()
