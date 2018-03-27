#include "inout.h"

void input_64(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp\n"); }
    fgets(in,65,fp);
    fclose(fp);
}

void input_512(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp\n"); }
    fgets(in,513,fp);
    fclose(fp);
}

void input_4096(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp\n"); }
    fgets(in,4097,fp);
    fclose(fp);
}

void input_32768(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp\n"); }
    fgets(in,32769,fp);
    fclose(fp);
}
