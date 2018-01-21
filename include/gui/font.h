#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "config.h"
#include "gui/glyph.h"
#include "log.h"

#define FDEF_SIZE 22 
#define FDEF_FONT CONF_RES_ROOT "fonts/ubuntu.ttf"

#define FDEF_ASCIIBEGIN 32
#define FDEF_ASCIIEND  127

class Font
{
public:
    Font();
    ~Font() noexcept;

    bool loadFace(const char* path);
    void print();
    bool setSize(unsigned int val); // TODO

    const Glyph& getGlyph(unsigned char c);
    const unsigned char* atlasbuffer();
    const unsigned long atlassize();

private:
    void initGlyph(unsigned int index, Glyph& g);
    bool createAtlas();
    bool initLib();
    void loadGlyphInSlot(unsigned int index);

    void printAtlas();
private:
    FT_Library _library;
    FT_Face _face;

    const char* _fontpath;

    // Charcode -> glyph;
    std::map<unsigned int, Glyph> _charmap;

    // Font atlas buffer
    unsigned char* _atlasbuffer;
    unsigned long _atlassize;

    Log _log{"Font"};
};

