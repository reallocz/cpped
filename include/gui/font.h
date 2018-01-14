#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "gui/bitmap.h"

#define FDEF_SIZE 28
#define FDEF_FONT "fonts/DejaVuSans.ttf"

class Font
{
public:
    Font();
    ~Font();

    void loadFace(const char* path);
    bool isinit(); 
    void print();
    void setSize(unsigned int val); // TODO

    Bitmap getBitmap(unsigned int code);

private:
    void initLib();
    void setinit(bool val);
    void loadCharmap();

private:
    FT_Library _library;
    FT_Face _face;

    const char* _fontpath;
    bool _isinit;

    std::map<unsigned int, unsigned int> _charmap;
};

