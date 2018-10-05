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
			(str)block_size]
	output = subprocess.run(args, stdout=subprocess.PIPE)
	time = output.stdout.split()[-2]
	return int(time)

