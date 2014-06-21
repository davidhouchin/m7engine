/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Font
 *  Font.h
 *  Purpose: Font class to be drawn by FontManager.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef FONT_H
#define	FONT_H

#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Logger.h"

namespace M7engine {
class Font {
public:
    Font();
    virtual ~Font();

    /**
     *  Load font from file, specifying size.
     *  @param *filename File to load font from.
     *  @param size The font size to use.
     */
    bool loadFont(const char *filename, int size);
    /**
     *  Set font directly using ALLEGRO_FONT.
     *  @param *font ALLEGRO_FONT to use.
     */
    void setFont(ALLEGRO_FONT *font);
    /**
     *  Reload current font into memory.
     */
    bool reloadFont();
    /**
     *  Return pointer to current font.
     *  @return Pointer to current ALLEGRO_FONT.
     */
    ALLEGRO_FONT* getFont(){ return font; }

    /**
     *  Sets the current color using an ALLEGRO_COLOR.
     *  @param color ALLEGRO_COLOR to set.
     */
    void setColor(ALLEGRO_COLOR color){ this->color = color; }
    /**
     *  Returns the current color as an ALLEGRO_COLOR.
     *  @return The current ALLEGRO_COLOR.
     */
    ALLEGRO_COLOR getColor(){ return color; }

    /**
     *  Set the justification of the font.
     *  @param just Int to set justification to.
     */
    void setJustification(int just){ justification = just; }
    /**
     *  Returns the current justification.
     *  @return Int defining current justification.
     */
    int getJustification(){ return justification; }
    /**
     *  Set font size.
     *  @param size Int to set size to.
     */
    void setSize(int size){ this->size = size; }
    /**
     *  Returns current font size.
     *  @return The current font size.
     */
    int getSize(){ return size; }

    /**
     *  Returns the resource name of the font.
     *  @return Char array containing name.
     */
    const char* getName(){ return this->name; }
    /**
     *  Set the resource name of the font.
     *  @param *name Char array containing name to set.
     */
    void setName(const char *name) { this->name = name; }

private:
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR color;
    int justification, size;
    const char *fontFilename, *name;
};

class FontManager {
public:
    FontManager();
    virtual ~FontManager();

    bool init();

    void drawText(float x, float y, Font *font, char const *text);
    void drawTextF(float x, float y, Font *font, char const *text, ...);
};
}
#endif
