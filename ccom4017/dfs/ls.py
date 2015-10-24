###############################################################################
#
# Filename: mds_db.py
# Author: Jose R. Ortiz and ... (hopefully some students contribution)
#
# Description:
# 	List client for the DFS
#


import socket
import sys

from Packet import *


def usage():
    print """Usage: python %s <server>:<port, default=8000>""" % sys.argv[0]
    sys.exit(0)


def client(ip, port):

    # Contacts the metadata server and ask for list of files.
    p = Packet()
    pResp = Packet()
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    p.BuildListPacket()
    msg = p.getEncodedPacket()

    try:
        # Connect to server and send data
        sock.connect((ip, port))
        sock.sendall(msg)

        # Receive data from the server and shut down
        recv = sock.recv(1024)
        pResp.DecodePacket(recv)

        recv = pResp.getFileArray()

    finally:
        sock.close()

    try:
        for fname, fsize in recv:
            print "{} {} bytes".format(fname, fsize)
    except:
        print "Server returned NAK..."

if __name__ == "__main__":

    if len(sys.argv) < 2:
        usage()

    ip = None
    port = None
    server = sys.argv[1].split(":")
    if len(server) == 1:
        ip = server[0]
        port = 8000
    elif len(server) == 2:
        ip = server[0]
        port = int(server[1])

    if not ip:
        usage()

    client(ip, port)
