#include "tea.h"

void encrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k)
{
   register unsigned long y=v[0],z=v[1],sum=0,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   while(n-->0)
      {
        sum += delta;
        y += (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        z += (y << 4)+c ^ y+sum ^ (y >> 5)+d;
      }

   w[0]=y; w[1]=z;
}

void decrypt(unsigned long *const v,unsigned long *const w,const unsigned long *const k)
{
   register unsigned long y=v[0],z=v[1],sum=0xC6EF3720,delta=0x9E3779B9,a=k[0],b=k[1],c=k[2],d=k[3],n=32;

   /* sum = delta<<5, in general sum = delta * n */

   while(n-->0)
      {
        z -= (y << 4)+c ^ y+sum ^ (y >> 5)+d;
        y -= (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        sum -= delta;
      }
   
   w[0]=y; w[1]=z;
}