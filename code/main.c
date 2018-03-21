#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char c;

    fp = fopen("64_input.txt","r");

    while(c!=EOF) {
        c=fgetc(fp);
        printf("%c",c);
    }

    printf("\n\n");
    fclose(fp);
    return 0;
}
 /*
void input_64(char *in[]) {

}

void input_512() {

}

void input_4096() {

}

void input_32768() {
 
}*/