#include "gui/font.h"
#include <iostream>

static bool ISFTINIT = false;

Font::Font()
{
    if(!ISFTINIT) {
        ISFTINIT = initLib();
    }
    if(!loadFace(FDEF_FONT))
    {
        _log << Log::E << __func__ << ":Failed to create font!"
            << std::endl;
        throw;
    }
    if(!setSize(24))
    {
        _log << Log::E << __func__ << ":Failed to set font size!"
            << std::endl;
        throw;
    }
    createAtlas();
}


Font::~Font()
{
    FT_Done_FreeType(_library);
}


bool Font::initLib()
{
    int error = FT_Init_FreeType(&_library);
    if(error)
    {
        _log << Log::E << "Failed to initialize freetype library"
            << std::endl;
        return false;
    }
    else
    {
        _log << Log::L << "Freetype initialized successfully!"
            << std::endl;
        return true;
    }
}


bool Font::loadFace(const char* path)
{
    _fontpath = path;

    int error = FT_New_Face(_library, _fontpath, 0, &_face);

    if ( error == FT_Err_Unknown_File_Format )
    {
        _log << Log::E << "FONT: Unknown file format: " << _fontpath
            << std::endl;
        return false;
    }
    else if ( error || _face == NULL )
    {
        _log << Log::E << "FONT: Failed to load font: " <<  _fontpath
            << std::endl;
        return false;
    }
    else
    {
        _log << Log::L << "Font face loaded successfully: " << _fontpath
            << std::endl;
        return true;
    }
}


bool Font::setSize(unsigned int val)
{
    int error = FT_Set_Char_Size(
            _face, 
            0,              // Width 0 means same as height
            val*64,         // Height
            200,            // Horizontal resolution
            200             // Vertical resolution
            );

    if(error)
    {
        _log << Log::E << "Failed to set font size: " << val << std::endl;
        return false;
    }
    else
        return true;
}



void Font::print()
{
    _log << Log::L << "Font {\n"
        << " path: " << _fontpath << ",\n"
        << " family: " << _face->family_name << ",\n"
        << " style: " << _face->style_name << ",\n"
        << " size: " << _face->size << ",\n"
        << " faces: " << _face->num_faces << ",\n"
        << " glyphs: " << _face->num_glyphs << ",\n"
        << "}" << std::endl;
}


const Glyph& Font::getGlyph(unsigned char c)
{
    return _charmap[c];
}


const unsigned char* Font::atlasbuffer()
{
    return _atlasbuffer;
}

const unsigned long Font::atlassize()
{
    return _atlassize;
}


// load glyph into slot and RENDER it too
void Font::loadGlyphInSlot(unsigned int index)
{
    int error = 1;
    error = FT_Load_Glyph(_face, index, FT_LOAD_DEFAULT);

    if(error)
    {
        _log << Log::E << __func__ <<
            ":FT_Load_Glyph(index=" << index << ")" << std::endl;
        throw;
    }

    error = FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        _log << Log::E << __func__<<
            ":FT_Render_Glyph(index=" << index << std::endl;
        throw;
    }
}


// Load glyph into slot and init Glyph
void Font::initGlyph(unsigned int index, Glyph& g)
{
    loadGlyphInSlot(index);

    FT_GlyphSlot slot = _face->glyph;

    // GlyphSlotRec
    g.index = index;
    g.advX = slot->advance.x;
    g.advY = slot->advance.y;
    g.width = slot->metrics.width;
    g.height = slot->metrics.height;


    // Bitmap
    FT_Bitmap bitmap = _face->glyph->bitmap;
    g.bmap_rows = bitmap.rows;
    g.bmap_width = bitmap.width;
    g.bmap_pitch = bitmap.pitch;
}


// Load up an atlas in a buffer!
bool Font::createAtlas()
{

    // load charmap and calc the size of buffer required
    _atlassize = 0;

    _log << Log::L << "Loading charmap...";
    for(char c = FDEF_ASCIIBEGIN; c < FDEF_ASCIIEND; ++c)
    {
        unsigned int index = FT_Get_Char_Index(_face, c);
        if(index != 0)
        {
            Glyph glyph;
            glyph.code = c;
            initGlyph(index, glyph);
            glyph.bmap_atlasoffset = _atlassize;

            _charmap[c] = glyph;

            std::cout << glyph.code << " -> " << glyph.bmap_atlasoffset << std::endl;

            _atlassize += glyph.bmap_width * glyph.bmap_rows;
        }
        else
            std::cout << "TODO ERROR!:: " << c << std::endl;
    }

    _log << Log::L << "done.\n" << "Loaded " << _charmap.size()
        << "/" << _face->num_glyphs << std::endl;

    _log << Log::L << __func__ << ":Atlas size = "
        << _atlassize << " bytes" << std::endl;

    // Alloc atlasbuffer and copy bitmaps to it
    _atlasbuffer = new unsigned char[_atlassize];
    long writtensize = 0;

    // Write bitmaps to buffer
    for(char c = FDEF_ASCIIBEGIN; c < FDEF_ASCIIEND; ++c)
    {
        const Glyph& glyph = _charmap[c];
        loadGlyphInSlot(glyph.index);
        unsigned int gwidth = glyph.bmap_width;
        unsigned int grows = glyph.bmap_rows;
        unsigned char* gbuffer = _face->glyph->bitmap.buffer;
        long goffset = glyph.bmap_atlasoffset;

        for(unsigned int row = 0; row < grows; ++row)
        {
            for(unsigned int col = 0; col < gwidth; ++col)
            {
                _atlasbuffer[goffset + (row*gwidth) + col] =
                    gbuffer[(row*gwidth) + col];
                writtensize += 1;
            }
        }
    }

    std::cout << "Atlas ready: " << writtensize << " / "
        << _atlassize << " written!" << std::endl;

    return true;
}


// Print to console
void Font::printAtlas()
{
    for(char c = FDEF_ASCIIBEGIN; c < FDEF_ASCIIEND; ++c)
    {
        const Glyph& glyph = _charmap[c];
        loadGlyphInSlot(glyph.index);
        unsigned int gwidth = glyph.bmap_width;
        unsigned int grows = glyph.bmap_rows;
        long goffset = glyph.bmap_atlasoffset;

        for(unsigned int row = 0; row < grows; ++row)
        {
            for(unsigned int col = 0; col < gwidth; ++col)
            {

                char cx = ((int)_atlasbuffer[goffset + (row*gwidth)+col]) > 0 ? '.': ' ' ;
                std::cout << cx;
            }
            std::cout << std::endl;
        }
    }

}
