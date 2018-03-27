//#include <openssl/des.h>
#include "inout.h"
/*#include "mode1.h"
#include "mode2.h"
#include "tea.h"*/

int main() {
    char in_64[65];
    char in_512[513];
    //char in_4096[4097];
    //char in_32768[32769];

    input_64(in_64);
    printf("%s\n\n", in_64);

    input_512(in_512);
    printf("%s\n\n", in_512);

    /*input_4096(in_4096);
    //printf("%s\n\n", in_4096);

    input_32768(in_32768);
    //printf("%s\n", in_32768); */

    return 0;
}