#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "config.h"
#include "gui/bitmap.h"
#include "gui/glyph.h"
#include "log.h"

#define FDEF_SIZE 22 
#define FDEF_FONT CONF_RES_ROOT "fonts/ubuntu.ttf"

class Font
{
public:
    Font();
    ~Font() noexcept;

    void loadFace(const char* path);
    void print();
    void setSize(unsigned int val); // TODO

    Glyph& getGlyph(unsigned char c);

private:
    bool loadGlyphAt(unsigned int index, Glyph& g);
    bool loadBitmap(Glyph& g);
    bool initLib();
    void loadCharmap();

private:
    FT_Library _library;
    FT_Face _face;

    const char* _fontpath;

    // Charcode -> glyph;
    std::map<unsigned int, Glyph> _charmap;

    Log _log{"Font"};
};

