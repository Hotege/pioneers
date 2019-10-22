#ifndef PIONEERS_GAME_FONT_H
#define PIONEERS_GAME_FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void font_initialize(const char* filename, const int encrypted);
void font_render(unsigned char** dest, int* width, int* height, const wchar_t* wtext, const int font_size);
void font_terminate();

#endif