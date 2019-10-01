#include <stdio.h>
#include "../crypt/crypt.h"

const int size = 12;

const char k1[] = "This is key1.\0";
const int k1len = 13;
const char k2[] = "Key2 is here.\0";
const int k2len = 13;

int main(int argc, char const *argv[])
{
    printf("crypt test\n");
    const char source[] = "Hello World!\0";
    printf("source: %s\n", source);
    unsigned char result[size];
    encrypt_memory(result, (unsigned char*)source, size, (unsigned char*)k1, k1len, (unsigned char*)k2, k2len);
    printf("result: ");
    for (int i = 0; i < size; i++)
        printf("%d ", result[i]);
    printf("\n");
    char conf[size + 1];
    conf[size] = 0;
    decrypt_memory((unsigned char*)conf, result, size, (unsigned char*)k1, k1len, (unsigned char*)k2, k2len);
    printf("conf: %s\n", conf);
    return 0;
}