#include "gui/font.h"
#include <iostream>

Font::Font()
{
    setinit(false);
    initLib();
    loadFace(FDEF_FONT);
    // TODO https://www.freetype.org/freetype2/docs/tutorial/step1.html
}


Font::~Font()
{
    FT_Done_FreeType(_library);
}


void Font::initLib()
{
    int error = FT_Init_FreeType(&_library);
    if(error)
        std::cerr << "Failed to initialize freetype library"
            << std::endl;
    else
        std::cout << "Freetype initialized successfully!"
            << std::endl;
}


void Font::loadFace(const char* path)
{
    _fontpath = path;

    int error = FT_New_Face(_library, _fontpath, 0, &_face);

    if ( error == FT_Err_Unknown_File_Format )
    {
        std::cerr << "FONT: Unknown file format: " << _fontpath
            << std::endl;
        setinit(false);
    }
    else if ( error || _face == NULL )
    {
        std::cerr << "FONT: Failed to load font: " <<  _fontpath
            << std::endl;
        setinit(false);
    }
    else
    {
        std::cout << "Font face loaded successfully: " << _fontpath
            << std::endl;
        
        setSize(24);        
        loadCharmap();
        setinit(true);
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
        setinit(false);
    }
}

void Font::setinit(bool val)
{
    _isinit = val;
}


bool Font::isinit()
{
    return _isinit;
}


void Font::print()
{
    std::cout << "Font {\n"
        << " path: " << _fontpath << ",\n"
        << " family: " << _face->family_name << ",\n"
        << " style: " << _face->style_name << ",\n"
        << " size: " << _face->size << ",\n"
        << " faces: " << _face->num_faces << ",\n"
        << "}" << std::endl;
}


void Font::loadCharmap()
{
    unsigned int index;
    //std::cout << "Charmap: " << std::endl;

    for(unsigned int i = 0; i < 127; ++i)
    {
        index = FT_Get_Char_Index(_face, i); 
        //std::cout << (char) i << " -> " << index << std::endl;
        _charmap[i] = index;
    }
    std::cout << "Loaded charmap." << std::endl;
}


Bitmap Font::getBitmap(unsigned int code)
{
    if(_charmap[code] != 0)
    {
        int error = FT_Load_Glyph(_face, code, FT_LOAD_DEFAULT);

        if (error) 
        {
            std::cout << "Cannot getGlyph: Failed to load glyph!" << std::endl;
        }

        error = FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
        if (error)
        {
            std::cout << "Error FT_Render_Glyph" << std::endl;
        }

        FT_Bitmap bitmap = _face->glyph->bitmap;

        return Bitmap(bitmap.rows, bitmap.width, bitmap.pitch, bitmap.buffer);
    }
    else
    {
        std::cout << "Cannot getGlyph: Invalid code: " << code << std::endl;
        return Bitmap();
    }
}


