###############################################################################
#
# Filename: meta-data.py
# Author: Jose R. Ortiz and Raul E. Negron
#
# Description:
# 	MySQL support library for the DFS project. Database info for the
#       metadata server.

from mds_db import *
from Packet import *
import sys
import SocketServer


def usage():
    print """Usage: python %s <port, default=8000>""" % sys.argv[0]
    sys.exit(0)


class MetadataTCPHandler(SocketServer.BaseRequestHandler):

    def handle_reg(self, db, p):
		"""Register a new client to the DFS. ACK if successfully REGISTERED,
			NAK if problem, DUP if the IP and port already registered
		"""
		try:
            # try and add the data node to the data base
            # return ACK if successful, DUP is data node is not unique
			if db.AddDataNode(p.getAddr(), p.getPort()):
                            print 'data node registered'
                            self.request.sendall("ACK")
			else:
				self.request.sendall("DUP")
		except:
			self.request.sendall("NAK")

    def handle_list(self, db):
        """Get the file list from the database and send list to client"""

        try:
            # build a respone packet to list all files currently in the db
            pResp = Packet()
            pResp.BuildListResponse(db.GetFiles())
            self.request.sendall(pResp.getEncodedPacket())
        except:
            self.request.sendall("NAK")

    def handle_put(self, db, p):
    	"""Insert new file into the database and send data nodes to save
    	   the file.
    	"""

        # get file name and size from the packet
    	fname, fsize = p.getFileInfo()

        # try and insert the file into the db
    	if db.InsertFile(fname, fsize):
            #! print "file '{}' inserted in db".format(fname)

            # since file entry was successful, send back available data nodes
            pResp = Packet()
            pResp.BuildPutResponse(db.GetDataNodes())
            self.request.sendall(pResp.getEncodedPacket())

    	else:
    		self.request.sendall("DUP")

    def handle_get(self, db, p):
        """Check if file is in database and return list of
                server nodes that contain the file.
        """

        fname = p.getFileName()
        fsize, farr = db.GetFileInode(fname)

        if fsize:
            pResp = Packet()
            pResp.BuildGetResponse(farr, fsize)
            self.request.sendall(pResp.getEncodedPacket())

        else:
            self.request.sendall("NFOUND")

    def handle_blocks(self, db, p):
        """Add the data blocks to the file inode"""

        fname = p.getFileName()
        fblocks = p.getDataBlocks()

        if db.AddBlockToInode(fname, fblocks):
            print "Data blocks for '{}' added to inodes".format(fname)
        else:
            print "Could not add data blocks..."

    def handle(self):

        # Establish a connection with the local database
        db = mds_db("dfs.db")
        db.Connect()

        # Define a packet object to decode packet messages
        p = Packet()

        # Receive a msg from the list, data-node, or copy clients
        msg = self.request.recv(524,288)

        # Decode the packet received
        p.DecodePacket(msg)

        # Extract the command part of the received packet
        cmd = p.getCommand()

        # Invoke the proper action
        if cmd == "reg":
            # Registration client
            self.handle_reg(db, p)

        elif cmd == "list":
            # Client asking for a list of files
            self.handle_list(db)

        elif cmd == "put":
            # Client asking for servers to put data
            self.handle_put(db, p)

        elif cmd == "get":
            # Client asking for servers to get data
            self.handle_get(db, p)

        elif cmd == "dblks":
            # Client sending data blocks for file
            self.handle_blocks(db, p)

        db.Close()

if __name__ == "__main__":
    HOST, PORT = "", 8000

    if len(sys.argv) > 1:
        try:
            PORT = int(sys.argv[1])
        except:
            usage()

    server = SocketServer.TCPServer((HOST, PORT), MetadataTCPHandler)

    server.serve_forever()
