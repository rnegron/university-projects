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
        print 'Got: fname: {}, fsize: {}'.format(fname, fsize)

        # Receive the data
        data = self.request.recv(1024)

        # Generates an unique block id.
        blockid = str(uuid.uuid1())

        print 'Writing {} to {}'.format(fname, os.path.join(DATA_PATH, blockid + '.dat'))
        with open(os.path.join(DATA_PATH, blockid + '.dat'), 'wb') as f:
            f.write(data)

        # Send the block id back
        resp = Packet()
        resp.BuildGetDataBlockPacket(blockid)
        self.request.sendall(resp.getEncodedPacket())

    # def handle_get(self, p):
    #
    #     # Get the block id from the packet
    #     blockid = p.getBlockID()
    #
    #     # Read the file with the block id data
    #     # Send it back to the copy client.
    #
    #     # Fill code

    def handle(self):
        msg = self.request.recv(1024)
        #! print msg, type(msg)
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

	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
    server.serve_forever()
