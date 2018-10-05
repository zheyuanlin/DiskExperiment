#!/usr/bin/env python3

import sys
import subprocess
import os
import shutil
import csv
import glob

# runs create_random_file c executable and returns the time returned from executable in milliseconds
def run_create_random_file(filename, total_bytes, block_size):
	executable_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), './create_random_file')
	args = [executable_path,
			filename, 
			str(total_bytes), 
			str(block_size)]
	output = subprocess.run(args, stdout=subprocess.PIPE)
	return int(output.stdout)

# creates a bunch of files in a directory
def main():
	if (len(sys.argv) != 2):
		print('Only use 1 argument, which is the path to the directory where you want your files!')
		sys.exit(1)
	else:

		directory = sys.argv[1]
		if os.path.exists(directory) == False:
			# directory doesn't exist, make one
			os.mkdir(directory)
		block_size_list = [128, 512, 1024, 4096, 1024 * 8, 1024 * 64, 1024 * 256, 1024 ** 2, 2 * 1024 ** 2]
		# set total_bytes, just a random pick
		total_bytes = 10 * 1024 ** 2
		writer = csv.DictWriter(sys.stdout, fieldnames=('block size', 'time (milliseconds)'))
		writer.writeheader()

		for block_size in block_size_list:
			created_file = os.path.join(directory, './created_file_{size}'.format(size=block_size))
			# get return from run_create_random_file
			time_taken = run_create_random_file(created_file, total_bytes, block_size)
			writer.writerow({'block size': block_size, 'time (milliseconds)': time_taken})
			# remove file
			os.remove(created_file)

if __name__ == '__main__':
	main()
