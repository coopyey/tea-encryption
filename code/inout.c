#include "inout.h"

void input_64(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp: file couldn't be opened\n"); }
    fgets(in,65,fp);
    fclose(fp);
}

void input_512(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp: file couldn't be opened\n"); }
    fgets(in,513,fp);
    fclose(fp);
}

void input_4096(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp: file couldn't be opened\n"); }
    fgets(in,4097,fp);
    fclose(fp);
}

void input_32768(char *in) {
    FILE *fp;
    fp = fopen("input.txt","r");
    if (fp==NULL) { printf("Null fp: file couldn't be opened\n"); }
    fgets(in,32769,fp);
    fclose(fp);
}

void output_64(char *out, char kind, char pass) {
    FILE *fp;
    
    //0=des cbc, 1=des ofb, 2=cbc, 3=ofb
    if ((kind == 'c') && (pass == '0')) {
        fp = fopen("cbc/des_c_64.txt", "w");
    } else if ((kind == 'p') && (pass == '0')) {
        fp = fopen("cbc/des_p_64.txt", "w");
    }  else if ((kind == 'c') && (pass == '1')) {
        fp = fopen("ofb/des_c_64.txt", "w");
    } else if ((kind == 'p') && (pass == '1')) {
        fp = fopen("ofb/des_p_64.txt", "w");
    } else if ((kind == 'c') && (pass == '2')) {
        fp = fopen("cbc/tea_c_64.txt", "w");
    } else if ((kind == 'p') && (pass == '2')) {
        fp = fopen("cbc/tea_p_64.txt", "w");
    } /*else if ((kind == 'c') && (pass == '3')) {
        fp = fopen("ofb/tea_c_64.txt", "w");
    } else if ((kind == 'p') && (pass == '3')) {
        fp = fopen("ofb/tea_p_64.txt", "w");
    } 
    */

    if (fp==NULL) { printf("Null fp: file couldn't be created\n"); }

    fputs(out,fp);
    fclose(fp);
}

void output_512(char *out, char kind, char pass) {
    FILE *fp;
    
    //0=des cbc, 1=des ofb, 2=cbc, 3=ofb
    if ((kind == 'c') && (pass == '0')) {
        fp = fopen("cbc/des_c_512.txt", "w");
    } else if ((kind == 'p') && (pass == '0')) {
        fp = fopen("cbc/des_p_512.txt", "w");
    }  else if ((kind == 'c') && (pass == '1')) {
        fp = fopen("ofb/des_c_512.txt", "w");
    } else if ((kind == 'p') && (pass == '1')) {
        fp = fopen("ofb/des_p_512.txt", "w");
    } else if ((kind == 'c') && (pass == '2')) {
        fp = fopen("cbc/tea_c_512.txt", "w");
    } else if ((kind == 'p') && (pass == '2')) {
        fp = fopen("cbc/tea_p_512.txt", "w");
    } else if ((kind == 'c') && (pass == '3')) {
        fp = fopen("ofb/tea_c_512.txt", "w");
    } else if ((kind == 'p') && (pass == '3')) {
        fp = fopen("ofb/tea_p_512.txt", "w");
    } 

    if (fp==NULL) { printf("Null fp: file couldn't be created\n"); }

    fputs(out,fp);
    fclose(fp);
}

void output_4096(char *out, char kind, char pass) {
    FILE *fp;
    
    //0=des cbc, 1=des ofb, 2=cbc, 3=ofb
    if ((kind == 'c') && (pass == '0')) {
        fp = fopen("cbc/des_c_4096.txt", "w");
    } else if ((kind == 'p') && (pass == '0')) {
        fp = fopen("cbc/des_p_4096.txt", "w");
    }  else if ((kind == 'c') && (pass == '1')) {
        fp = fopen("ofb/des_c_4096.txt", "w");
    } else if ((kind == 'p') && (pass == '1')) {
        fp = fopen("ofb/des_p_4096.txt", "w");
    } /* else if ((kind == 'c') && (pass == '2')) {
        fp = fopen("cbc_c_4096.txt", "w");
    } else if ((kind == 'p') && (pass == '2')) {
        fp = fopen("cbc_p_4096.txt", "w");
    } else if ((kind == 'c') && (pass == '3')) {
        fp = fopen("ofb_c_4096.txt", "w");
    } else if ((kind == 'p') && (pass == '3')) {
        fp = fopen("ofb_p_4096.txt", "w");
    } 
    */

    if (fp==NULL) { printf("Null fp: file couldn't be created\n"); }

    fputs(out,fp);
    fclose(fp);
}

void output_32768(char *out, char kind, char pass) {
    FILE *fp;
    
    //0=des cbc, 1=des ofb, 2=cbc, 3=ofb
    if ((kind == 'c') && (pass == '0')) {
        fp = fopen("cbc/des_c_32768.txt", "w");
    } else if ((kind == 'p') && (pass == '0')) {
        fp = fopen("cbc/des_p_32768.txt", "w");
    }  else if ((kind == 'c') && (pass == '1')) {
        fp = fopen("ofb/des_c_32768.txt", "w");
    } else if ((kind == 'p') && (pass == '1')) {
        fp = fopen("ofb/des_p_32768.txt", "w");
    } /*else if ((kind == 'c') && (pass == '2')) {
        fp = fopen("cbc_c_32768.txt", "w");
    } else if ((kind == 'p') && (pass == '2')) {
        fp = fopen("cbc_p_32768.txt", "w");
    } else if ((kind == 'c') && (pass == '3')) {
        fp = fopen("ofb_c_32768.txt", "w");
    } else if ((kind == 'p') && (pass == '3')) {
        fp = fopen("ofb_p_32768.txt", "w");
    } */
    

    if (fp==NULL) { printf("Null fp: file couldn't be created\n"); }

    fputs(out,fp);
    fclose(fp);
} 