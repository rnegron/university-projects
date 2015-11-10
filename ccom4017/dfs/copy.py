###############################################################################
#
# Filename: mds_db.py
# Author: Jose R. Ortiz and Raul E. Negron
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

	block_List = []
	meta_p = Packet()
	data_p = Packet()

	# Create a connection to the data server
	meta_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	meta_sock.connect(address)

	# Read file and get size
	with open(fname, 'rb') as f:
		fileData = f.read()
		fsize = len(fileData)

	# Create a Put packet with the fname and the length of the data,
	# and send it to the metadata server
	meta_p.BuildPutPacket(fname, fsize)
	meta_sock.sendall(meta_p.getEncodedPacket())

	# Receive the available data nodes
	msg = meta_sock.recv(1024)

	# If no error and if file does not already exist
	try:
		# Get the list of data nodes.
		resp = Packet()
		resp.DecodePacket(msg)

	# The received data is not a packet...
	except:
		print "ERROR: Possible duplicate file."
		return

	# Store the available data nodes
	nodeList = resp.getDataNodes()

	# Define the file split length (block size)
	if len(nodeList) > 0:
		blockSize = fsize / len(nodeList)

		# if the file size is an odd number of bytes, add an extra to be safe
		if blockSize % 2 is not 0:
			blockSize += 1
	else:
		print "ERROR: No available data nodes."
		return

	# Send the blocks to the data servers, one by one
	for node in nodeList:
		# Establish a connection to the data node
		data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		data_sock.connect(tuple(node))

		# Split the blocks by string slices
		block = fileData[:blockSize]

		# Send the block to the current data node
		data_p.BuildPutPacket(fname, len(block))
		data_sock.sendall(data_p.getEncodedPacket())

		# Send the actual data
		data_sock.sendall(block)

		# Move on to the next block by string slice
		fileData = fileData[blockSize:]

		# Receive the data block id
		msg = data_sock.recv(1024)
		resp = Packet()
		resp.DecodePacket(msg)

		# Add the information of the current node to the block list
		addr = node[0]
		port = node[1]
		block_List.append([addr, port, str(resp.getBlockID())])

	print 'Done sending to nodes. Block list...'
	print block_List

	# Notify the metadata server where the blocks are saved.
	meta_p = Packet()
	meta_p.BuildDataBlockPacket(fname, block_List)
	meta_sock.sendall(meta_p.getEncodedPacket())
	print 'Sent!'


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
