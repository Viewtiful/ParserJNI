#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <ktb.h>
#include <ktb/hash.h>

int hashString() {
	char *hello = "Hello1";
	size_t hash_len = ktb_hash_get_len_from_algo(KTB_HASH_ALGO_SHA512);
   printf("hash_len : %ld\n", hash_len);
	uint8_t *hash = malloc(hash_len);

	if(ktb_hash_block(KTB_HASH_ALGO_SHA512, hello, strlen(hello), hash, hash_len) == KTB_ERR_NO_ERROR)
		printf("ktb_hash_block() ok\n");

   int i;
   for(i = 0; i < hash_len; ++i)
      printf("%02X ", hash[i]);
   printf("\n");
   hello = NULL;
   for(i = 0; i < hash_len; ++i)
      hash[i] = 0;
   free(hash);

	return 1;
}

int main(void) {

	struct timespec tsi, tsf;

	clock_gettime(CLOCK_MONOTONIC, &tsi);
	if(ktb_init() == KTB_ERR_NO_ERROR) 
		printf("ktb_init() ok\n");

	if(!hashString()) {
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


