#include "crypto.h"

void tea_encrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k) {
   register unsigned long y=v[0],z=v[1],sum=0,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   while(n-->0)
      {
        sum += delta;
        y += ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
        z += ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
      }

   w[0]=y; w[1]=z;
}

void tea_decrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k)
{
   register unsigned long y=v[0],z=v[1],sum=0xC6EF3720,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   /* sum = delta<<5, in general sum = delta * n */

   while(n-->0)
      {
        z -= ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
        y -= ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
        sum -= delta;
      }
   
   w[0]=y; w[1]=z;
}

void des_cbc(char *in) {
  int length = strlen(in)+1;
  unsigned char out[length], back[length];
  struct timeval start;
  struct timeval end;

  DES_cblock key;
  DES_cblock seed = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
  DES_cblock ivsetup = {0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8};
  DES_key_schedule keysched;
  DES_cblock ivec;

  memset(out, 0, sizeof(out));
  memset(back, 0, sizeof(back));

  RAND_seed(seed,sizeof(DES_cblock));

  DES_random_key(&key);
  DES_set_odd_parity(&key);
  if (DES_set_key_checked((C_Block *)key, &keysched)) { printf("Cannot set key schedule\n"); }

  memcpy(ivec, ivsetup, sizeof(ivsetup));
  gettimeofday(&start,NULL);
  DES_ncbc_encrypt((unsigned char *)in, out, length, &keysched, &ivec, DES_ENCRYPT);
  gettimeofday(&end,NULL);
  printf("%d CBC DES encrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));


  memcpy(ivec, ivsetup, sizeof(ivsetup));
  gettimeofday(&start,NULL);
  DES_ncbc_encrypt(out, back, length, &keysched, &ivec, DES_DECRYPT);
  gettimeofday(&end,NULL);
  printf("%d CBC DES decrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  if((length-1)==64) {
    output_64((char*)out,'c','0');
    output_64((char*)back,'p','0');
  } else if ((length-1)==512) {
    output_512((char*)out,'c','0');
    output_512((char*)back,'p','0');
  } else if ((length-1)==4096) {
    output_4096((char*)out,'c','0');
    output_4096((char*)back,'p','0');
  } /*else if ((length/3)==32768) {
    output_32768(out,'c','0');
    output_32768(back,'p','0');
    printf("32768 DES CBC files in output folder.\n");
  }*/
}

void des_ofb(char *in) {
  int length = strlen(in)+1;
  unsigned char out[length], back[length];
  struct timeval start;
  struct timeval end;

  DES_cblock key;
  DES_cblock seed = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
  DES_cblock ivsetup = {0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8};
  DES_key_schedule keysched;
  DES_cblock ivec;

  memset(out, 0, sizeof(out));
  memset(back, 0 ,sizeof(back));

  RAND_seed(seed,sizeof(DES_cblock));

  DES_random_key(&key);
  DES_set_odd_parity(&key);
  if (DES_set_key_checked((C_Block *)key, &keysched)) { printf("Cannot set key schedule\n"); }

  memcpy(ivec, ivsetup, sizeof(ivsetup));
  gettimeofday(&start,NULL);
  DES_ofb_encrypt((unsigned char*)in, out, 8, length, &keysched, &ivec);
  gettimeofday(&end,NULL);
  printf("%d OFB DES encrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  memcpy(ivec, ivsetup, sizeof(ivsetup));
  gettimeofday(&start,NULL);
  DES_ofb_encrypt(out, back, 8, length, &keysched, &ivec);
  gettimeofday(&end,NULL);
  printf("%d OFB DES decrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  if((length-1)==64) {
    output_64((char*)out,'c','1');
    output_64((char*)back,'p','1');
  } else if ((length-1)==512) {
    output_512((char*)out,'c','1');
    output_512((char*)back,'p','1');
  } else if ((length-1)==4096) {
    output_4096((char*)out,'c','1');
    output_4096((char*)back,'p','1');
  } /*else if ((length/3)==32768) {
    output_32768(out,'c','0');
    output_32768(back,'p','0');
    printf("32768 DES CBC files in output folder.\n");
  }*/
}
