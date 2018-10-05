#!/usr/bin/env python3

import sys
import subprocess
import os
import shutil
import csv
import glob

def run_get_histogram(filename, block_size):
	executable_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), './get_histogram')
	args = [executable_path,
			filename, 
			str(block_size)]
	output = subprocess.run(args, stdout=subprocess.PIPE)
	time = output.stdout.split()[-2]
	return int(time)

def main():
	if len(sys.argv != 2):
		print('wrong number of arguments')
		sys.exit(1)
	else:
		filename = sys.argv[1]
		block_size_list = [128, 512, 1024, 4096, 1024 * 8, 1024 * 16, 1024 * 32, 1024 * 64, 1024 * 128, 1024 * 256]
		total_bytes = 1024 ** 2
		writer = csv.DictWriter(sys.stdout, fieldnames=('block size', 'time (milliseconds)'))
		writer.writeheader()

		for block_size in block_size_list:
			time_taken = run_get_histogram(filename, block_size)
			writer.writerow({'block size': block_size, 'time (milliseconds)': time_taken})

if __name__ == '__main__':
	main()


