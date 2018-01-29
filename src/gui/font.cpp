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

    _fontresolution = FDEF_RESOLUTION;
    if(!setSize(FDEF_SIZE))
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
    _fontsize = val;
    int error = FT_Set_Char_Size(
            _face, 
            0,              // Width. 0 = same as height
            _fontsize*64,   // Height
            0,              // Horizontal resolution 0 = same as V
            _fontresolution             // Vertical resolution
            );

    if(error)
    {
        _log << Log::E << "Failed to set font size: " << _fontsize << std::endl;
        return false;
    }
    else
        return true;
}


// Font size in px
float Font::sizepx()
{
    return (1. * _fontsize * _fontresolution / 72);
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

void Font::printarb(unsigned char* buffer)
{
    for(unsigned int row = 0; row < _atlascharheight; ++row)
    {
        for(unsigned int col = 0; col < _atlascharwidth; ++col)
        {
            char c = ((int)buffer[(row*_atlascharwidth) + col]) > 0 ? '.': ' ' ;
            std::cout << c;
        }
        std::cout << std::endl;
    }
}


int Font::glyphcount()
{
    return _charmap.size();
}


const Glyph& Font::getGlyph(unsigned char c)
{
    return _charmap.at(c);
}


const unsigned char* Font::atlasbuffer()
{
    return _atlasbuffer;
}


const unsigned long Font::atlassize()
{
    return _atlassize;
}


const unsigned long Font::atlascharwidth()
{
    return _atlascharwidth;
}


const unsigned long Font::atlascharheight()
{
    return _atlascharheight;
}

const unsigned long Font::atlaswidth()
{
    return _atlascharwidth * _charmap.size();
}

const unsigned long Font::atlasheight()
{
    return _atlascharheight;
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


// Load up an atlas in a buffer!
bool Font::createAtlas()
{
    _log << Log::L << "Loading charmap..." << std::endl;

    // load charmap and calc the size of buffer required
    _atlassize = 0;
    _atlascharwidth = 0;
    _atlascharheight = 0;

    unsigned int max_width = 0;
    unsigned int max_height = 0;

    // First pass to map available glyphs into _charmap
    for(char c = FDEF_ASCIIBEGIN; c < FDEF_ASCIIEND; ++c)
    {
        unsigned int index = FT_Get_Char_Index(_face, c);
        if(index != 0)
        {
            Glyph glyph;

            loadGlyphInSlot(index);
            // Aliases
            FT_GlyphSlot slot = _face->glyph;
            FT_Bitmap bitmap = slot->bitmap;

            /// Init glyph
            // GlyphSlotRec
            glyph.index = index;
            glyph.code = c;
            glyph.advX = slot->advance.x;
            glyph.advY = slot->advance.y;
            glyph.width = slot->metrics.width;
            glyph.height = slot->metrics.height;
            // Bitmap
            glyph.bmap_width = bitmap.width;
            glyph.bmap_height = bitmap.rows;
            glyph.atlas_index = _charmap.size();
            //std::cout << "PITCH!!!!: " << (bitmap.pitch>0 ? "+ve!" : "-ve!" )<< std::endl;

            // Insert into charmap
            _charmap[c] = glyph;


            // Update maxheight
            max_width = std::max(glyph.bmap_width, max_width);
            max_height = std::max(glyph.bmap_height, max_height);
        }
        else
            std::cout << "TODO ERROR!:: " << c << std::endl;
    }

    _atlascharwidth = max_width;
    _atlascharheight = max_height;
    _atlassize = _charmap.size() * _atlascharheight * _atlascharwidth;

    _log << Log::L << "done.\n" << "Loaded " << _charmap.size()
        << "/" << _face->num_glyphs << std::endl;
    _log << Log::L << __func__ << ":Atlas maxw, maxh = "
        << _atlascharheight << ", " << _atlascharwidth << std::endl;
    _log << Log::L << __func__ << ":Atlas size = "
        << _atlassize << " bytes" << std::endl;

    // Alloc atlasbuffer and copy bitmaps to it
    _atlasbuffer = new unsigned char[_atlassize];
    long writtensize = 0;

    // Write bitmaps to buffer
    for(auto c = _charmap.begin(); c != _charmap.end(); ++c)
    {
        const Glyph& glyph = c->second;

        loadGlyphInSlot(glyph.index);
        unsigned int gwidth = glyph.bmap_width;
        unsigned int gheight = glyph.bmap_height;
        unsigned char* gbuffer = _face->glyph->bitmap.buffer;

        long goffset = glyph.atlas_index * _atlascharwidth * _atlascharheight;

        for(unsigned int row = 0; row < gheight; ++row)
        {
            for(unsigned int col = 0; col < gwidth; ++col)
            {
                _atlasbuffer[goffset + (row*_atlascharwidth) + col] 
                    = gbuffer[(row*gwidth) + col];
                writtensize += 1;
            }
        }

        //glyph.print(_atlasbuffer, _atlascharwidth, _atlascharheight);
        //printarb(&_atlasbuffer[goffset]);
        //std::cout <<  "______________" << std::endl;
    }

    std::cout << "Atlas ready: " << writtensize << " / "
        << _atlassize << " written!" << std::endl;

    return true;
}


// Print to console
void Font::printAtlas()
{
    for(auto c = _charmap.begin(); c != _charmap.end(); ++c)
    {
        const Glyph& glyph = c->second;
        loadGlyphInSlot(glyph.index);
        unsigned int gwidth = glyph.bmap_width;
        unsigned int grows = glyph.bmap_height;
        long goffset = glyph.atlas_index * _atlascharwidth * _atlascharheight;

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
