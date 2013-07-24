#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <ktb.h>
#include <ktb/err.h>
#include <kep/kep.h>
#include <kep/kep_sts.h>

int main() {
	struct timespec tsi, tsf;
	clock_gettime(CLOCK_MONOTONIC, &tsi);

	if(ktb_init() == KTB_ERR_NO_ERROR)
		printf("ktb_init() ok\n");

	int nbCurve = ktb_curves_count();
	printf("nb curve : %d\n", nbCurve);

	int i;
	for(i = 0; i < nbCurve; ++i)
		printf("%s\n", ktb_curves_id(i));

	ktb_kep_sts_t algo_params;
	ktb_kep_ctx_t ctx = NULL;
   ktb_public_key_t public_key;
   ktb_private_key_t private_key;

   size_t shared_key_size = 64;

   if(ktb_keys_generate_keypair(NULL, "nistP521", &public_key, &private_key) == KTB_ERR_NO_ERROR) 
      printf("ktb_keys_generate_keypair() ok\n");

   algo_params.cipher_algo = KTB_CIPHER_ALGO_AES256;
   algo_params.peer_public_key = public_key;
   algo_params.self_private_key = private_key;

   if(ktb_kep_init(&ctx, NULL, KTB_KEP_ALGO_STS, &algo_params, sizeof(algo_params), "nistP521", KTB_HASH_ALGO_SHA512, shared_key_size, 2) == KTB_ERR_NO_ERROR) 
      printf("ktb_kep_init() ok\n");

   int iter_max_left = 10;
   const void *data = NULL;
   size_t data_size;
   bool cont;

   do {
      data = ktb_kep_get_data(ctx, &data_size);

      if(ktb_kep_put_data(ctx, data, data_size, &cont) == KTB_ERR_NO_ERROR)
         printf("ktb_kep_put_data() ok\n");
   } while ( cont && (--iter_max_left >= 0));

   uint8_t *secret_key = malloc(shared_key_size);
   if(ktb_kep_finalise(ctx, secret_key, shared_key_size) == KTB_ERR_NO_ERROR)
      printf("ktb_kep_finalise() ok\n");

   printf("Generated key : \n");
   for( i = 0;i < shared_key_size; ++i)
      printf("%02X ", secret_key[i]);
   printf("\n");

   ktb_keys_public_key_clear(public_key);
   ktb_keys_private_key_clear(private_key);
   ktb_kep_clear(ctx);

   ktb_clear();
	clock_gettime(CLOCK_MONOTONIC, &tsf);
	double elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
	long elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
	printf("Elapsed time : %lf ms\n", elaps_s + ((double)elaps_ns) / 1.0e6);

	return 0;
}
