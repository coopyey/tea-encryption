#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include <openssl/des.h>
#include <openssl/rand.h>
#include <time.h>
#include <sys/time.h>
#include "inout.h"

typedef struct {
    long tv_sec;
    long tv_usec;
} timeval;

//Encryptions
void tea_encrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k);
//cbc_encrypt();
//ofb_encrypt();

//Decryptions
void tea_decrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k);
//cbc_decrypt();
//ofb_decrypt();


//DES library stuff
void des_cbc(char *in);
void des_ofb(char *in);

#endif