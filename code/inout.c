#include "inout.h"

void input_64(char in[]) {
    FILE *fp;
    fp = fopen("32768_input.txt","r");
    fgets(in,65,fp);
    fclose(fp);
}

void input_512(char *in) {
    FILE *fp;
    fp = fopen("32768_input.txt","r");
    if (fp==NULL) { printf("Null fp\n"); }
    int count = fread(in,sizeof(char),512,fp);
    printf("Read count %d\n", count);
    fclose(fp);
}

/* void input_4096(char in[]) {
    FILE *fp;
    fp = fopen("32768_input.txt","r");
    fgets(in,4097,fp);
    fclose(fp);
}

void input_32768(char in[]) {
    FILE *fp;
    fp = fopen("32768_input.txt","r");
    fgets(in,32769,fp);
    fclose(fp);
} */
