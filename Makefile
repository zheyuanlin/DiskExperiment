all: get_histogram create_random_file
get_histogram: get_histogram.c
	gcc -std=c99 -g -Wall $^ -o $@
create_random_file: create_random_file.c
	gcc -std=c99 -g -Wall $^ -o $@