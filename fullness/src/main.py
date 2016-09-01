
import os
import hashlib
import sys

if len(sys.argv) < 3:
	print("missing argument")
	sys.exit(-1)

f_digests = open(sys.argv[2], "w")

for dirname, dirnames, filenames in os.walk(sys.argv[1]):
	for filename in filenames:
		current = open(os.path.join(dirname, filename), "r")
		_digest = hashlib.md5(current.read().encode('utf-8')).hexdigest()
		current.close()
		f_digests.write(_digest + "\n")

f_digests.close()
