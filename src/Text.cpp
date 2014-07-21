/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Font
 *  Font.cpp
 *  Purpose: Font class to be drawn by FontManager.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Text.h"

namespace M7engine {
Font::Font()
{
    color = {0, 0, 0, 255};
}

Font::~Font()
{
    TTF_CloseFont(font);
}

bool Font::loadFont(const char *filename, int size)
{
    Logger::getInstance()->logMessage(0, "Font '%s' loading file: '%s'", name.c_str(), filename);
    font = TTF_OpenFont(filename, size);

    setSize(size);

    this->fontFilename = filename;
    if (!font) {
        Logger::getInstance()->logError(0, "Failed to load font: '%s'", filename);
        return false;
    }

    return true;
}

void Font::setFont(TTF_Font *font)
{
    if (font) {
        this->font = font;
    }
}

}
