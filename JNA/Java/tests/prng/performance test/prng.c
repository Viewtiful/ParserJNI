#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <ktb.h>
#include <ktb/hash.h>

int example1() {
   int buffer_size = 50;
   uint8_t *buffer = malloc(buffer_size);

	if(ktb_prng_fill_buffer(NULL, buffer, buffer_size) == KTB_ERR_NO_ERROR)
		printf("ktb_prng_fill_buffer() ok\n");

   int i;
   for(i = 0; i < buffer_size; ++i)
      printf("%02X ", buffer[i]);
   printf("\n");

   for(i = 0; i < buffer_size; ++i)
      buffer[i] = 0;
   free(buffer);

	return 1;
}

int main(void) {

	struct timespec tsi, tsf;

	clock_gettime(CLOCK_MONOTONIC, &tsi);
	if(ktb_init() == KTB_ERR_NO_ERROR) 
		printf("ktb_init() ok\n");

	if(!example1()) {
		ktb_clear();
		exit(1);
	}

	ktb_clear();

	clock_gettime(CLOCK_MONOTONIC, &tsf);
	double elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
	long elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
	printf("Elapsed time : %lf ms\n", elaps_s + ((double)elaps_ns) / 1.0e6);
	return 0;
}


