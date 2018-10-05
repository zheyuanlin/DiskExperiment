#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>
#include <stdio.h>

/** TAKEN FROM HANDOUT:
 * populate a random array (which is already
 * allocated with enough memory to hold n bytes.
 */
void random_array(char *array, long bytes) {
	for (int i = 0; i < bytes; i++) {
		char c = 'A' + (rand() % 26);
		array[i] = c;
	}
}

/**
 * Main function,
 * create_random_file <filename> <total bytes> <block size>
 */
int main(int argc, const char* argv[]) {
	// incorrect parameters:
	if (argc != 4) {
		printf("Input like following: create_random_file <filename> <total bytes> <block size>");
		return 1;
	}

	const char *filename = argv[1];
	int total_bytes = atoi(argv[2]);
	int block_size = atoi(argv[3]);

	// Your program should allocate a fixed amount of memory char buffer[block_size], 
	// and repeatedly generate random content into buffer, and then write buffer to disk. 
	// A reasonable block_size is 1MB.
	char buf[block_size];

	// Open file
	FILE *fptr;
	fptr = fopen(filename, "w");
	if (fptr == NULL) {
		printf("Couldn't open file, fptr = NULL");
		return 1;
	}

	// Measuring system time in the units of milliseconds
	struct timeb t;
	ftime(&t);
	long now_in_ms = t.time * 1000 + t.millitm;

	// Write file
	for (int i = 0; i < total_bytes; i += block_size) {
		// Fill buffer with random array and write it
		random_array(buf, block_size);
		fwrite(buf, 1, block_size, fptr);
		fflush(fptr);
	}

	if (total_bytes % block_size != 0) {
		int remaining = total_bytes % block_size;
		random_array(buf, remaining);
		fwrite(buf, 1, remaining, fptr);
		fflush(fptr);
	}

	// end and time
	ftime(&t);
	long end_time_in_ms = t.time * 1000 + t.millitm;
	printf("%ld\n", end_time_in_ms - now_in_ms);

	fclose(fptr);
	return 0;

}