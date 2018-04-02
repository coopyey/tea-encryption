#include "crypto.h"

int main() {
    srand(time(0));

    char in_64[65];
    char in_512[513];
    char in_4096[4097];
    char in_32768[32769];

    input_64(in_64);
    input_512(in_512);
    input_4096(in_4096);
    input_32768(in_32768);

    des_cbc(in_64);
    des_cbc(in_512);
    des_cbc(in_4096);
    des_cbc(in_32768);
    printf("DES CBC en/decryption done. Find files in cbc folder.\n\n");

    des_ofb(in_64);
    des_ofb(in_512);
    des_ofb(in_4096);
    des_ofb(in_32768);
    printf("DES OFB en/decryption done. Find files in ofb folder.\n\n");

    tea_cbc_mode(in_64);
    tea_cbc_mode(in_512);
    tea_cbc_mode(in_4096);
    tea_cbc_mode(in_32768);
    printf("TEA CBC en/decryption done. Find files in cbc folder.\n\n");

    return 0;
}