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

    unsigned int bmap_width = 0;
    unsigned int bmap_height = 0;

    // Index in the atlas
    unsigned int atlas_index = 0;


    // Note *atlas must point to the start of the atlasbuffer!
    void print(const unsigned char* atlas, int mwidth, int mheight) const
    {
        long goffset = atlas_index * mwidth * mheight;

        for(unsigned int row = 0; row < bmap_height; ++row)
        {
            for(unsigned int col = 0; col < bmap_width; ++col)
            {
                char c = ((int)atlas[goffset + (row*mwidth+col)]) > 0 ? '.': ' ' ;
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }


    void printInfo()
    {
        std::cout << "Glyph {"
            << "\n width: " << (width>>6)
            << "\n height: " << (height>>6)
            << "\n advX: " << (advX>>6)
            << "\n bmap_width: " << bmap_width
            << "\n bmap_height: " << bmap_height
            << "\n}" << std::endl;
    }

};
