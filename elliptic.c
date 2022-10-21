#include <openssl/evp.h>
#include <openssl/ec.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>


void handleErrors()
{
  abort();
}


unsigned char *ecdh(size_t *secret_len)
{

    EVP_PKEY_CTX *pctx, *kctx;
    EVP_PKEY_CTX *ctx;
    unsigned char *secret;
    EVP_PKEY *pkey = NULL, *peerkey=NULL, *params = NULL;
    /* NB: assumes pkey, peerkey have been already set up */

    /* Create the context for parameter generation */
    if(NULL == (pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL))) handleErrors();

      /* Initialise the parameter generation */
      if(1 != EVP_PKEY_paramgen_init(pctx)) handleErrors();

      /* We're going to use the ANSI X9.62 Prime 256v1 curve */
      if(1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, NID_X9_62_prime256v1)) handleErrors();

      /* Create the parameter object params */
      if (!EVP_PKEY_paramgen(pctx, &params)) handleErrors();
                  
      /* Create the context for the key generation */
      if(NULL == (kctx = EVP_PKEY_CTX_new(params, NULL))) handleErrors();

      /* Generate the key */
      if(1 != EVP_PKEY_keygen_init(kctx)) handleErrors();
      if (1 != EVP_PKEY_keygen(kctx, &pkey)) handleErrors();
                      
      if (1 != EVP_PKEY_keygen_init(kctx)) handleErrors();
      if (1 != EVP_PKEY_keygen(kctx, &peerkey)) handleErrors();

      /* Get the peer's public key, and provide the peer with our public key */
      
      /* Create the context for the shared secret derivation */
      if(NULL == (ctx = EVP_PKEY_CTX_new(pkey, NULL))) handleErrors();

      /* Initialise */
      if(1 != EVP_PKEY_derive_init(ctx)) handleErrors();

      /* Provide the peer public key */
      if(1 != EVP_PKEY_derive_set_peer(ctx, peerkey)) handleErrors();

      /* Determine buffer length for shared secret */
      if(1 != EVP_PKEY_derive(ctx, NULL, secret_len)) handleErrors();

      /* Create the buffer */
      if(NULL == (secret = OPENSSL_malloc(*secret_len))) handleErrors();

      /* Derive the shared secret */
      if(1 != (EVP_PKEY_derive(ctx, secret, secret_len))) handleErrors();


      EVP_PKEY_CTX_free(ctx);
      EVP_PKEY_free(peerkey);
      EVP_PKEY_free(pkey);
      EVP_PKEY_CTX_free(kctx);
      EVP_PKEY_free(params);
      EVP_PKEY_CTX_free(pctx);

      /* Never use a derived secret directly. Typically it is passed through some hash function to produce a key */
      return secret;
}


int main(int argc, char* argv[])
{

  struct timeval start, end;
  int time = 0;
  int cur_runs = 0;
  int tot_runs = 10;
  FILE* fp = fopen("all_files.out", "a+");
  size_t size;

  while (cur_runs < tot_runs) {
    gettimeofday(&start, NULL);
    ecdh(&size);
    gettimeofday(&end, NULL);

    time += ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
    cur_runs += 1;
  }

  time = time / tot_runs;
  fprintf(fp, "Elliptic Curve execution time: %d microseconds\n", time);
  fclose(fp);
  
  return 0;

}
