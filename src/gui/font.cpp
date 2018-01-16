#include "gui/font.h"
#include <iostream>

static bool ISFTINIT = false;

Font::Font()
{
    if(!ISFTINIT) {
        ISFTINIT = initLib();
    }
    loadFace(FDEF_FONT);
    // TODO https://www.freetype.org/freetype2/docs/tutorial/step1.html
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
        std::cerr << "Failed to initialize freetype library"
            << std::endl;
        return false;
    }
    else
    {
        std::cout << "Freetype initialized successfully!"
            << std::endl;
        return true;
    }
}


void Font::loadFace(const char* path)
{
    _fontpath = path;

    int error = FT_New_Face(_library, _fontpath, 0, &_face);

    if ( error == FT_Err_Unknown_File_Format )
    {
        std::cerr << "FONT: Unknown file format: " << _fontpath
            << std::endl;
    }
    else if ( error || _face == NULL )
    {
        std::cerr << "FONT: Failed to load font: " <<  _fontpath
            << std::endl;
    }
    else
    {
        std::cout << "Font face loaded successfully: " << _fontpath
            << std::endl;
        
        setSize(24);        
        loadCharmap();
    }
}


void Font::setSize(unsigned int val)
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
        std::cerr << "Failed to set font size: " << val << std::endl;
    }
}



void Font::print() const
{
    std::cout << "Font {\n"
        << " path: " << _fontpath << ",\n"
        << " family: " << _face->family_name << ",\n"
        << " style: " << _face->style_name << ",\n"
        << " size: " << _face->size << ",\n"
        << " faces: " << _face->num_faces << ",\n"
        << " glyphs: " << _face->num_glyphs << ",\n"
        << "}" << std::endl;
}


void Font::loadCharmap()
{
    std::cout << "Loading charmap...";
    int num_glyphs = _face->num_glyphs;

    for(wchar_t c = 0; c < 129; ++c)
    {
        unsigned int index = FT_Get_Char_Index(_face, c); 
        if(index != 0)
        {
            Glyph g;
            g.code = c;
            loadGlyphAt(index, g);
            loadBitmap(g);
            _charmap[c] = g;
        }
    }

    std::cout << "done.\n"
        << "Loaded " << _charmap.size() << "/" << _face->num_glyphs
        << std::endl;
}



Glyph& Font::getGlyph(unsigned char c)
{
    return _charmap[c];
}


bool Font::loadGlyphAt(unsigned int index, Glyph& g)
{
    int error = 1;
    error = FT_Load_Glyph(_face, index, FT_LOAD_DEFAULT);
    if(error)
    {
        std::cerr << "Error: Cannot loadGlyphAt(index=" << index << ")" << std::endl;
        return false;
    }
    else
    {
        FT_GlyphSlot slot = _face->glyph;

        g.index = index;
        g.advX = slot->advance.x;
        g.advY = slot->advance.y;
        g.width = slot->metrics.width;
        g.height = slot->metrics.height;
        return true;
    }
}


// Load bitmap from glyph index
bool Font::loadBitmap(Glyph& g)
{
    int error = 1;
    error = FT_Load_Glyph(_face, g.index, FT_LOAD_DEFAULT);
    if (error)
    {
        std::cout << "Error: cannot loadBitmap::Cannot getGlyph: Failed to load glyph!" << std::endl;
        return false;
    }

    error = 1;
    error = FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
    if (error)
    {
        std::cout << "Error FT_Render_Glyph" << std::endl;
        return false;
    }


    FT_Bitmap bitmap = _face->glyph->bitmap;

    //std::cout << "Loaded glyph {"
    //<< " char: " << (char)code
    //<< " rows: " << bitmap.rows
    //<< " width: " << bitmap.width
    //<< " pitch: " << bitmap.pitch
    //<< " }" << std::endl;
    g.bitmap = Bitmap(bitmap.rows, bitmap.width, bitmap.pitch, bitmap.buffer);
    return true;
}


