#include "base16.h"

const char codes[16] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
};

void base16_encode(unsigned char* dest, const unsigned char* src, const int len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i * 2 + 0] = codes[src[i] >> 4];
        dest[i * 2 + 1] = codes[src[i] & 15];
    }
}