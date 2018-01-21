#pragma once
#include <iostream>

struct Glyph
{
    // Glyph Index
    unsigned int index = 0;

    // The character itself
    char code = 0;

    // Advance in x dir.
    // slot->advance.x (Shorthand to slot->metrics->horizAdvance)
    long advX = 0;

    // Advance in y dir. Ignored for horizontal text layouts
    // slot->advance.y (Shorthand to slot->metrics->vertAdvance)
    long advY = 0;

    // Glyphs total width. NOT the advance!
    // NOT BITMAP WIDTH!
    long width = 0;

    // Glyphs total width. NOT the ascent!
    // NOT BITMAP HEIGHT!
    long height = 0;

    unsigned int bmap_rows = 0;
    unsigned int bmap_width = 0;
    unsigned int bmap_pitch = 0;
    // Offet of bitmap in the atlasbuffer
    unsigned long bmap_atlasoffset = 0;


    void print(const unsigned char* atlas) const
    {
        for(unsigned int row = 0; row < bmap_rows; ++row)
        {
            for(unsigned int col = 0; col < bmap_width; ++col)
            {
                char c = ((int)atlas[bmap_atlasoffset + (row*bmap_width+col)]) > 0 ? '.': ' ' ;
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
};
