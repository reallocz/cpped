#pragma once
#include "gui/bitmap.h"

struct Glyph
{
    unsigned int index = 0;
    char code = 0;
    long advX = 0;
    long advY = 0;
    long width = 0;
    long height = 0;
    Bitmap bitmap;
};
