#ifndef _INOUT_H_
#define _INOUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_64(char *in);
void input_512(char *in);
void input_4096(char *in);
//void input_32768(char *in);

void output_64(char *out, char kind, char pass);
void output_512(char *out, char kind, char pass);
void output_4096(char *out, char kind, char pass);
//void output_32768(char *out, char kind, char pass);

#endif