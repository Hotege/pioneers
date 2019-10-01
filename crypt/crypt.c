#include "crypt.h"
#include <stdio.h>
#include <stdlib.h>
#include "base16.h"
#include "table.h"

void encrypt_memory(
    unsigned char* dest, const unsigned char* src, const int len,
    const unsigned char* k1, const int klen1, const unsigned char* k2, const int klen2
)
{
    unsigned char* k1base16 = (unsigned char*)malloc(klen1 * 2);
    base16_encode(k1base16, k1, klen1);
    unsigned char* k2base16 = (unsigned char*)malloc(klen2 * 2);
    base16_encode(k2base16, k2, klen2);
    for (int i = 0; i < len; i++)
        dest[i] = get_enc_code((k2base16[i % (klen2 * 2)]) * 16 + k1base16[i % (klen1 * 2)], src[i]);
    free(k2base16); k2base16 = NULL;
    free(k1base16); k1base16 = NULL;
}

void decrypt_memory(
    unsigned char* dest, const unsigned char* src, const int len,
    const unsigned char* k1, const int klen1, const unsigned char* k2, const int klen2
)
{
    unsigned char* k1base16 = (unsigned char*)malloc(klen1 * 2);
    base16_encode(k1base16, k1, klen1);
    unsigned char* k2base16 = (unsigned char*)malloc(klen2 * 2);
    base16_encode(k2base16, k2, klen2);
    for (int i = 0; i < len; i++)
        dest[i] = get_dec_code((k2base16[i % (klen2 * 2)]) * 16 + k1base16[i % (klen1 * 2)], src[i]);
    free(k2base16); k2base16 = NULL;
    free(k1base16); k1base16 = NULL;
}