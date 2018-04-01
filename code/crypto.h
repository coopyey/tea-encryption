#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include <openssl/des.h>
#include <openssl/rand.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include "inout.h"

typedef struct {
    long tv_sec;
    long tv_usec;
} timeval;

void tea_encrypt(uint32_t *const v,uint32_t *const w,const uint32_t *const k);
void tea_decrypt(uint32_t *const v,uint32_t *const w,const uint32_t *const k);

void tea_cbc_mode(char *in);
void tea_ofb_mode(char *in);
char *rand_stream(size_t num);

void des_cbc(char *in);
void des_ofb(char *in);

#endif