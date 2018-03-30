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

void output_64(char *out, char kind) {
    FILE *fp;
    
    if (kind == 'c') {
        fp = fopen("cipher_64.txt", "w+");
    } else if (kind == 'p') {
        fp = fopen("plain_64.txt", "w+");
    }

    if (fp==NULL) { printf("Null fp\n"); }


}