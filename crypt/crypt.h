#ifndef PIONEERS_CRYPT_CRYPT_H
#define PIONEERS_CRYPT_CRYPT_H

void encrypt_memory(
    unsigned char* dest, const unsigned char* src, const int len,
    const unsigned char* k1, int klen1, const unsigned char* k2, int klen2
);
void decrypt_memory(
    unsigned char* dest, const unsigned char* src, const int len,
    const unsigned char* k1, const int klen1, const unsigned char* k2, int const klen2
);

#endif