#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "config.h"
#include "gui/glyph.h"
#include "log.h"

#define FDEF_SIZE 24
#define FDEF_RESOLUTION 300
#define FDEF_FONT CONF_RES_ROOT "fonts/DejaVuSans.ttf"

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
    const unsigned long atlascharwidth();
    const unsigned long atlascharheight();
    const unsigned long atlaswidth();
    const unsigned long atlasheight();
    int glyphcount();
    void printarb(unsigned char* buffer);
    float sizepx();

private:
    bool createAtlas();
    bool initLib();
    void loadGlyphInSlot(unsigned int index);

    void printAtlas();
private:
    FT_Library _library;
    FT_Face _face;
    unsigned int _fontsize;
    unsigned int _fontresolution;

    const char* _fontpath;

    // Charcode -> glyph;
    std::map<unsigned int, Glyph> _charmap;

    // Font atlas buffer
    unsigned char* _atlasbuffer;
    unsigned long _atlassize;
    unsigned long _atlascharwidth;
    unsigned long _atlascharheight;

    Log _log{"Font"};
};

