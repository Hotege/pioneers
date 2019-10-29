#include "font.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../file/file.h"
#include "../../crypt/crypt.h"
#include "../../image/image.h"

unsigned char* font_data = NULL;
FT_Library library = NULL;
FT_Face face = NULL;

void font_initialize(const char* filename, const int encrypted)
{
    struct file_loader font_file;
    char* path = (char*)malloc(strlen(filename) + 6);
    memset(path, 0, strlen(filename) + 6);
    strcat(path, filename);
    if (encrypted)
        strcat(path, ".hbc");
    load_file(&font_file, path);
    if (encrypted)
    {
        font_data = (unsigned char*)malloc(font_file.size);
        memset(font_data, 0, font_file.size);
        decrypt_memory(
            font_data, ((unsigned char*)(font_file.data)), font_file.size,
            filename, strlen(filename), path, strlen(path)
        );
    }
    else
    {
        font_data = font_file.data;
        font_file.data = NULL;
    }
    FT_Init_FreeType(&library);
    FT_New_Memory_Face(library, font_data, (FT_Long)font_file.size, 0, &face);
    close_file(&font_file);
    free(path);
    path = NULL;
}

void font_render(unsigned char** dest, int* width, int* height, const wchar_t* wtext, const int font_size)
{
    FT_Set_Pixel_Sizes(face, font_size, font_size);
    size_t size = wcslen(wtext);
    unsigned char** chararacters = malloc(sizeof(unsigned char*) * size);
    int* widths = malloc(sizeof(int) * size);
    int* heights = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++)
    {
        chararacters[i] = NULL;
        FT_Load_Char(face, (FT_ULong)wtext[i], FT_LOAD_RENDER);
        widths[i] = face->glyph->metrics.horiAdvance / 64;
        heights[i] = face->glyph->metrics.vertAdvance / 64;
        int dx = face->glyph->metrics.horiBearingX / 64;
        int base = face->size->metrics.ascender / 64;
        int sy = face->glyph->metrics.horiBearingY / 64;
        unsigned char* data = malloc(face->glyph->bitmap.width * face->glyph->bitmap.rows);
        memcpy(data, face->glyph->bitmap.buffer, face->glyph->bitmap.width * face->glyph->bitmap.rows);
        chararacters[i] = malloc(widths[i] * heights[i]);
        memset(chararacters[i], 0, widths[i] * heights[i]);

        for (int y = 0; y < face->glyph->bitmap.rows; y++)
            for (int x = 0; x < face->glyph->bitmap.width; x++)
                chararacters[i][(heights[i] - 1 - (y + (base - sy))) * widths[i] + (x + dx)] = data[y * face->glyph->bitmap.width + x];
        free(data);
        data = NULL;
    }
    int total_width = 0;
    for (size_t i = 0; i < size; i++)
        total_width += widths[i];
    *dest = malloc(total_width * font_size);
    memset(*dest, 0, total_width * font_size);
    int x_offset = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (int y = 0; y < heights[i]; y++)
            for (int x = 0; x < widths[i]; x++)
                (*dest)[y * total_width + (x + x_offset)] = chararacters[i][y * widths[i] + x];
        x_offset += widths[i];
    }
    free(heights);
    heights = NULL;
    free(widths);
    widths = NULL;
    for (size_t i = 0; i < size; i++)
    {
        free(chararacters[i]);
        chararacters[i] = NULL;
    }
    free(chararacters);
    chararacters = NULL;
    *width = total_width;
    *height = font_size;
}

void font_terminate()
{
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    free(font_data);
    font_data = NULL;
}