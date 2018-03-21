#ifndef _TEA_H_
#define _TEA_H_

//#include <openssl/des.h>

void encrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k);
void decrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k);

#endif