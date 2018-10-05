#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
/**
 * file_ptr : the file pointer, ready to be read from.
 * hist: an array to hold 26 long integers.  hist[0] is the
 *       number of 'A', and hist[1] is the number of 'B', etc.
 * block_size: the buf size to be used.
 * milliseconds: time it took to complete the file scan
 * total_bytes_read: the amount data in bytes read
 *
 * returns: -1 if there is an error.
 */
int get_histogram(
    FILE *file_ptr, 
    long hist[], 
    int block_size, 
    long *milliseconds, 
    long *total_bytes_read) {


	struct timeb t;
	ftime(&t);
	long now_in_ms = t.time * 1000 + t.millitm;

	char buf[block_size];

	while (fread(buf, 1, block_size, file_ptr) == block_size) {
		// From handout, bzero(buffer) then fread
		memset(buf, 0, block_size); 
		// Count letters
		for (int i = 0; i < block_size; i++) {
			int letter = (int)buf[i] - 'A';
			hist[letter] += 1;
		}
		// Increment total_bytes_read
		*(total_bytes_read) += (long)block_size;
	}

	// end and time
	ftime(&t);
	long end_time_in_ms = t.time * 1000 + t.millitm;

	*milliseconds = end_time_in_ms - now_in_ms;
	return 0;
}

/** Main function:
 * get_histogram <filename> <block_size>
 */
int main(int argc, const char* argv[]) {
	if (argc != 3) {
		printf("Call the function like this: get_histogram <filename> <blocksize>");
		return 1;
	}

	// from handout:
	long hist[26];
	long milliseconds;
	long filelen;
	int block_size = atoi(argv[2]);

	FILE *file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL) {
		printf("Couldn't open file, file_ptr = NULL");
		return 1;
	}

	int ret = get_histogram( file_ptr,
							 hist,
							 block_size,
							 &milliseconds,
							 &filelen);

	assert(ret >= 0);

	for (int i = 0; i < 26; i++) {
		printf("%c : %ld\n", 'A' + i, hist[i]);
	}
	
	printf("BLOCK SIZE: %ld bytes\n", block_size);
	printf("TOTAL BYTES: %ld bytes\n", filelen);
	printf("TIME: %lu milliseconds\n", milliseconds);


	fclose(file_ptr);
	return 0
}