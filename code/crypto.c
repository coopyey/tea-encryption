#include "crypto.h"

//Function generates a random stream of bytes for use
char *rand_stream(size_t num) {
  char *stream = malloc(num);
  size_t i;

  for (i=0; i<num; i++) {
    stream[i] = rand();
  }
  return stream;
}

//TEA ofc works on 64 bits at a time - modiified to uint32_t from unsigned long for portability
void tea_encrypt(uint32_t *const v,uint32_t *const w,const uint32_t *const k) {
   register uint32_t y=v[0],z=v[1],sum=0,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   while(n-->0)
      {
        sum += delta;
        y += ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
        z += ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
      }
   w[0]=y; w[1]=z;
}

void tea_decrypt(uint32_t *const v,uint32_t *const w,const uint32_t *const k) {
   register uint32_t y=v[0],z=v[1],sum=0xC6EF3720,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   /* sum = delta<<5, in general sum = delta * n */

   while(n-->0)
      {
        z -= ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
        y -= ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
        sum -= delta;
      }
   w[0]=y; w[1]=z;
}

//DES CBC en/decryption using the openssl library
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
  } else if ((length-1)==32768) {
    output_32768((char*)out,'c','0');
    output_32768((char*)back,'p','0');
  }
}

//DES OFB en/decryption using the openssl library
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
  } else if ((length-1)==32768) {
    output_32768((char*)out,'c','1');
    output_32768((char*)back,'p','1');
  }
}

//TEA CBC implementation
void tea_cbc_mode(char *in) {
  int length = strlen(in)+1; //total length of input +1
  int rounds = length/8; //number of blocks to process based on input
  int i;
  char key[16], ivsetup[8], ivec[8], cur_block[8], returned[8];
  char ctext[length], ptext[length], temp[length];
  struct timeval start;
  struct timeval end;

  memset(ctext, 0, sizeof(ctext));
  memset(ptext, 0 ,sizeof(ptext));
  memset(cur_block, 0 ,sizeof(cur_block));
  memset(returned, 0 ,sizeof(returned));
  memset(key, 0, sizeof(key));
  memset(ivsetup, 0, sizeof(ivsetup));
  memset(temp, 0, sizeof(temp));
  memset(ivec, 0, sizeof(ivec));

  //initialization
  memcpy(key,rand_stream(16),16);
  memcpy(ivsetup,rand_stream(8),8);
  strcpy(temp,in);
  memcpy(ivec, ivsetup, 8);

  //encrypt
  gettimeofday(&start,NULL);
  for (i=0; i<rounds; i++) {
    if(i==0) {
      memcpy(cur_block,temp,8); //set current working block

      //XOR working block with iv
      int j;
      for (j=0; j<=8; j++) {
        cur_block[j] ^= ivec[j];
      }
     
      //encrypt current block + update ctext and iv
      tea_encrypt((uint32_t*)cur_block,(uint32_t*)returned,(uint32_t*)key);

      memcpy(ivec,returned,8);
      memcpy(ctext,returned,8);
    } else {
        int pos=(i*8)+1; //set to start pos
        int itr = 0;
        //Set current working block based on round number
        while (itr<=8) {
          cur_block[itr] = temp[pos];
          pos++;
          itr++;
        }

        //XOR current block with iv
        int j;
        for (j=0; j<=8; j++) {
          cur_block[j] ^= ivec[j];
         }

      //encrypt current block + update iv and append ctext
      tea_encrypt((uint32_t*)cur_block,(uint32_t*)returned,(uint32_t*)key);

      memcpy(ivec,returned,8);
      memcpy(ctext+(i*8),returned,8);
    } //end if/else
  }//end for i
  gettimeofday(&end,NULL);
  printf("%d TEA CBC encrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  //output bc i was too lazy to realloc and the like
  if((length-1)==64) {
    output_64(ctext,'c','2');
  } else if ((length-1)==512) {
    output_512(ctext,'c','2');
  } else if ((length-1)==4096) {
    output_4096(ctext,'c','2');
  } else if ((length-1)==32768) {
    output_32768(ctext,'c','2');
  }

  //reinitialize values
  memset(cur_block, 0, 8);
  memset(returned, 0, 8);
  memcpy(ivec, ivsetup, 8);

  //decrypt
  gettimeofday(&start,NULL);
  for (i=0; i<rounds; i++) {
    if(i==0) {
      memcpy(temp,ctext,length); //set working string to ciphertext
      memcpy(cur_block,temp,8); //set working block

      //"decrypt" ctext
      tea_decrypt((uint32_t*)cur_block,(uint32_t*)returned,(uint32_t*)key);

      //XOR "decrypted" text with iv + update iv and set ptext
      int h;
      for (h=0; h<=8; h++) {
        returned[h] ^= ivec[h];
      }

      memcpy(ivec,returned,8);
      memcpy(ptext,returned,8);
    } else {
        int pos=(i*8)+1; //set to start pos
        int itr = 0;
        //set work block based on round number
        while (itr<=8) {
          cur_block[itr] = temp[pos];
          pos++;
          itr++;
        }

        //"decrypt" ptext
        tea_decrypt((uint32_t*)cur_block,(uint32_t*)returned,(uint32_t*)key);

        //XOR "decrypted" text with iv + update iv and append ptext
        int h;
        for(h=0; h<=8; h++) {
          returned[h] ^= ivec[h];
        }

        memcpy(ivec,returned,8);
        memcpy(ptext+(i*8),returned,8);
    } //end if/else
  }//end for i
  gettimeofday(&end,NULL);
  printf("%d TEA CBC decrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  //output bc i was too lazy to realloc and the like
  if((length-1)==64) {
    output_64(ptext,'p','2');
  } else if ((length-1)==512) {
    output_512(ptext,'p','2');
  } else if ((length-1)==4096) {
    output_4096(ptext, 'p', '2');
  } else if ((length-1)==32768) {
    output_32768(ptext, 'p', '2');
  }
}

//TEA OFB implementation
void tea_ofb_mode(char *in) {
  int length = strlen(in)+1; //total length of input +1
  int rounds = length/8; //number of blocks to process based on input
  int i;
  char key[16], nonceset[8], nonceec[8], cur_block[8], returned[8];
  char ctext[length], ptext[length], temp[length];
  struct timeval start;
  struct timeval end;

  memset(ctext, 0, sizeof(ctext));
  memset(ptext, 0 ,sizeof(ptext));
  memset(cur_block, 0 ,sizeof(cur_block));
  memset(returned, 0 ,sizeof(returned));
  memset(key, 0, sizeof(key));
  memset(nonceset, 0, sizeof(nonceset));
  memset(temp, 0, sizeof(temp));
  memset(nonceec, 0, sizeof(nonceec));

  memcpy(key,rand_stream(16),16);
  memcpy(nonceset,rand_stream(8),8);
  strcpy(temp,in);
  memcpy(nonceec, nonceset, 8);

  //encrypt
  gettimeofday(&start,NULL);
  for (i=0; i<rounds; i++) {
    if(i==0) {
      memcpy(cur_block,temp,8);
     
      //sets new iv value based on encrypted nonce
      tea_encrypt((uint32_t*)nonceec,(uint32_t*)returned,(uint32_t*)key);
      memcpy(nonceec,returned,8);

      //XOR working block with updated nonce
      int j;
      for (j=0; j<=8; j++) {
        cur_block[j] ^= returned[j];
      }

      //sets first 64 bits of ciphertext to encrypted value
      memcpy(ctext,cur_block,8);
    } else {
      int pos=(i*8)+1; //set to start pos
      int itr = 0;
      //sets working block according to round
      while (itr<8) {
        cur_block[itr] = temp[pos];
        pos++;
        itr++;
      }

      //sets new iv balue based on encrypted value
      tea_encrypt((uint32_t*)nonceec,(uint32_t*)returned,(uint32_t*)key);
      memcpy(nonceec,returned,8);

      //XOR working block with updated nonce
      int j;
      for (j=0; j<=8; j++) {
        cur_block[j] ^= returned[j];
       }

      //appends encrypted block to ciphertext
      memcpy(ctext+(i*8),cur_block,8);
    } //end if/else
  }//end for i
  gettimeofday(&end,NULL);
  printf("%d TEA OFB encrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  //output bc i was too lazy to realloc and the like
  if((length-1)==64) {
    output_64(ctext,'c','3');
  } else if ((length-1)==512) {
    output_512(ctext,'c','3');
  } else if ((length-1)==4096) {
    output_4096(ctext,'c','3');
  } else if ((length-1)==32768) {
    output_32768(ctext,'c','3');
  }

  //clear/reset values
  memset(cur_block, 0, 8);
  memset(returned, 0, 8);
  memcpy(nonceec, nonceset, 8);

  //decrypt
  gettimeofday(&start,NULL);
  for (i=0; i<rounds; i++) {
    if(i==0) {
      //take in ciphertext as new working string & set first working block
      memcpy(temp,ctext,length);
      memcpy(cur_block,temp,8);

      //update new iv with encrypted nonce
      tea_encrypt((uint32_t*)nonceec,(uint32_t*)returned,(uint32_t*)key);
      memcpy(nonceec,returned,8);

      //XOR working block with nonce + set plaintext start
      int h;
      for (h=0; h<=8; h++) {
        cur_block[h] ^= returned[h];
      }

      memcpy(ptext,cur_block,8);
    } else {
      int pos=(i*8)+1; //set to start pos
      int itr = 0;
      //set current working block based on round #
      while (itr<8) {
        cur_block[itr] = temp[pos];
        pos++;
        itr++;
      }

      //encrypte iv and update
      tea_encrypt((uint32_t*)cur_block,(uint32_t*)returned,(uint32_t*)key);
      memcpy(nonceec,returned,8);

      //XOR current working block with updated nonce + append ptext
      int h;
      for(h=0; h<=8; h++) {
        cur_block[h] ^= returned[h];
      }

      memcpy(ptext+(i*8),cur_block,8);
    } //end if/else
  }//end for i
  gettimeofday(&end,NULL);
  printf("%d TEA OFB decrypt took %li useconds.\n",length-1,(end.tv_usec-start.tv_usec));

  //output block bc i was too lazy to realloc and the like
  if((length-1)==64) {
    output_64(ptext,'p','3');
  } else if ((length-1)==512) {
    output_512(ptext,'p','3');
  } else if ((length-1)==4096) {
    output_4096(ptext, 'p', '3');
  } else if ((length-1)==32768) {
    output_32768(ptext, 'p', '3');
  }
}
