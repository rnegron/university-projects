###############################################################################
#
# Filename: mds_db.py
# Author: Jose R. Ortiz and ... (hopefully some students contribution)
#
# Description:
# 	Copy client for the DFS
#
#

import socket
import sys
import os.path
from math import ceil as ceiling

from Packet import *

def usage():
	print """Usage:\n\tFrom DFS: python %s <server>:<port>:<dfs file path> <destination file>\n\tTo DFS: python %s <source file> <server>:<port>:<dfs file path>""" % (sys.argv[0], sys.argv[0])
	sys.exit(0)

def copyToDFS(address, fname, path):
	""" Contact the metadata server to ask to copy file fname,
	    get a list of data nodes. Open the file in path to read,
	    divide in blocks and send to the data nodes.
	"""

	# Create a connection to the data server
	meta_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	meta_sock.connect(address)

	# Read file
	with open(fname, 'rb') as f:
		fileData = f.read()

	fsize = len(fileData)

	# Create a Put packet with the fname and the length of the data,
	# and send it to the metadata server
	meta_p = Packet()
	meta_p.BuildPutPacket(fname, fsize)
	meta_sock.sendall(meta_p.getEncodedPacket())

	msg = meta_sock.recv(1024)
	resp = Packet()

	# If no error or if file already exists
	try:
		# Get the list of data nodes.
		resp.DecodePacket(msg)

	# The received data is not a packet...
	except:
		print "ERROR: Possible duplicate file."
		return

	nodeList = resp.getDataNodes()

	# Divide the file in blocks
	# possibly: divide normally then add 1 if not divisible
	if len(nodeList) > 0:
		blockSize = ceiling(float(fsize) / len(nodeList))
	else:
		print "NodeList:", nodeList
		return

	blockList = []
	for i in range(len(nodeList)):
		blockList.append('block{}'.format(i + 1))

	# Send the blocks to the data servers
	data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	data_p = Packet()

	for node in nodeList:
		data_sock.connect(tuple(node))
		data_p.BuildPutPacket(blockList.pop(), blockSize)
		data_sock.sendall(data_p.getEncodedPacket())

		# Receive the data block id
		msg = data_sock.recv(1024)
		resp = Packet()
		resp.DecodePacket(msg)

		print "GOT ID BACK! ITS {}".format(resp.getBlockID())

	# Notify the metadata server where the blocks are saved.
	# meta_p.BuildDataBlockPacket()


# def copyFromDFS(address, fname, path):
# 	""" Contact the metadata server to ask for the file blocks of
# 	    the file fname.  Get the data blocks from the data nodes.
# 	    Saves the data in path.
# 	"""
#
#    	# Contact the metadata server to ask for information of fname
#
# 	# Fill code
#
# 	# If there is no error response Retreive the data blocks
#
# 	# Fill code
#
#     	# Save the file
#
# 	# Fill code

if __name__ == "__main__":
#	client("localhost", 8000)
	if len(sys.argv) < 3:
		usage()

	file_from = sys.argv[1].split(":")
	file_to = sys.argv[2].split(":")

	if len(file_from) > 1:
		ip = file_from[0]
		port = int(file_from[1])
		from_path = file_from[2]
		to_path = sys.argv[2]

		if os.path.isdir(to_path):
			print "Error: path %s is a directory.  Please name the file." % to_path
			usage()

		copyFromDFS((ip, port), from_path, to_path)

	elif len(file_to) > 2:
		ip = file_to[0]
		port = int(file_to[1])
		from_path = sys.argv[1]
		to_path = file_to[2]

		if os.path.isdir(from_path):
			print "Error: path %s is a directory.  Please name the file." % from_path
			usage()

		copyToDFS((ip, port), from_path, to_path)
