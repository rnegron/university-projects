###############################################################################
#
# Filename: mds_db.py
# Author: Jose R. Ortiz and Raul E. Negron
#
# Description:
# 	Copy client for the DFS
#

import socket
import sys
import os.path

from Packet import *

def usage():
	print """Usage:\n\tFrom DFS: python %s <server>:<port>:<dfs file path> <destination file>\n\tTo DFS: python %s <source file> <server>:<port>:<dfs file path>""" % (sys.argv[0], sys.argv[0])
	sys.exit(0)

def copyToDFS(address, fname, path):
	""" Contact the metadata server to ask to copy file fname,
	    get a list of data nodes. Open the file in path to read,
	    divide in blocks and send to the data nodes.
	"""

	# List which will hold the information of the data blocks
	blockList = []

	# Create a connection to the data server
	meta_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	meta_sock.connect(address)

	# Read source file and get size
	with open(fname, 'rb') as f:
		fileData = f.read()
		fsize = len(fileData)

	# Change fname to that of the target directory
	fname = os.path.join(path, os.path.basename(fname))

	# Create a Put packet with the fname and the length of the data,
	# and send it to the metadata server
	meta_p = Packet()
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
		if fsize % 2 is not 0:
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

		print 'Sending {} bytes to port {}'.format(len(block), node[1])

		# Send the block to the current data node
		data_p = Packet()
		data_p.BuildPutPacket(fname, len(block))
		data_sock.sendall(data_p.getEncodedPacket())

		# Wait for acknowledgement from client
		msg = data_sock.recv(1024)

		# Check if data nodes acknowledged; if not, return
		if msg != "OK":
			print "ERROR! Could not send file information to data node", node
			return

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
		blockList.append([addr, port, str(resp.getBlockID())])

	# Connect to the metadata server
	meta_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	meta_sock.connect(address)

	# Build a packet with the data block info
	meta_p = Packet()
	meta_p.BuildDataBlockPacket(fname, blockList)

	# Notify the metadata server where the blocks are saved
	meta_sock.sendall(meta_p.getEncodedPacket())


def copyFromDFS(address, fname, path):
	""" Contact the metadata server to ask for the file blocks of
	    the file fname.  Get the data blocks from the data nodes.
	    Saves the data in path.
	"""

   	# Contact the metadata server
	meta_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	try:
		meta_sock.connect(address)
	except:
		print 'ERROR! Could not connect to', address

	# Ask for information of fname
	meta_p = Packet()
	meta_p.BuildGetPacket(fname)
	meta_sock.sendall(meta_p.getEncodedPacket())

	# Receive information of fname
	msg = meta_sock.recv(1024)

	# If there is no error, retreive the data blocks
	try:
		resp = Packet()
		resp.DecodePacket(msg)

	except:
		print 'ERROR! Could not retrieve the data blocks for', fname
		print 'Remember to specify the absolute DFS path!'
		return

	# No error, get the available data nodes and fsize
	nodeList = resp.getDataNodes()
	fsize = resp.getFileSize()

	# Define the maximum blockSize based on how many data nodes there are
	blockSize = fsize / len(nodeList)
	if fsize % 2 is not 0:
		blockSize += 1

	# String which will hold all the binary data for fname
	data = ''

	# Get the data from each of the data nodes
	for node in nodeList:
		addr = node[0]
		port = node[1]
		blockid = node[2]

		# Connect to the data node
		data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		data_sock.connect((addr, port))

		# Build a GetDataBlock packet
		data_p = Packet()
		data_p.BuildGetDataBlockPacket(blockid)

		# Send the request to the current data node
		data_sock.sendall(data_p.getEncodedPacket())

		# Create a temporary string to buffer incoming data
		buff = ''

		# While there is still data to receive..
		while True:
			# If the buffer completes the data, break
			if len(data) + len(buff) >= fsize:
				break

			# If the buffer is becoming larger than the blockSize, break
			if len(buff) >= blockSize:
				break

			# Receive the data from the current data node
			buff += data_sock.recv(4096)

		print 'Got {} bytes from port {}'.format(len(buff), port)

		# Append the received data to the data string
		data += buff

    # Save the file once all the data is received
	with open(path, 'ab') as f:
		f.write(data)

if __name__ == "__main__":

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
