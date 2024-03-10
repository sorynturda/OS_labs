#include <stdio.h>
#include <stdlib.h>

#define BYTECONV(n) (n * 8)
#define BYTE(n, bytes) (n << BYTECONV(1))

int main(int argc, char **argv) {
    unsigned int num;
    if (argc == 1) {
        printf("Enter a number\n");
        exit(-1);
    }
    sscanf(argv[1], "%x", &num);
    // num = 0x12345678;
    unsigned int byte1 = (0x000000ff & num) << BYTECONV(3);
    unsigned int byte2 = (0x0000ff00 & num) << BYTECONV(1);
    unsigned int byte3 = (0x00ff0000 & num) >> BYTECONV(1);
    unsigned int byte4 = (0xff000000 & num) >> BYTECONV(3);
    num = ((byte1 | byte2) | byte3) | byte4;
    printf("%08x\n", num);
    return 0;
}
