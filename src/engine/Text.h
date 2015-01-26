/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Logger.h"

namespace M7engine {
class Font {
public:
    Font();
    virtual ~Font();

    /**
     *  @brief Load font from file, specifying size.
     *  @param *filename File to load font from.
     *  @param size The font size to use.
     */
    bool loadFont(const char *filename, int size);

    /**
     *  @brief Set font directly using TTF_Font.
     *  @param *font TTF_Font to use.
     */
    void setFont(TTF_Font *font);

    /**
     *  @brief Return pointer to current font.
     *  @return Pointer to current TTF_Font.
     */
    TTF_Font* getFont(){ return font; }

    /**
     *  @brief Sets the current color using an SDL_Color.
     *  @param color SDL_Color to set.
     */
    void setSDLColor(SDL_Color color){ this->color = color; }

    /**
     *  @brief Returns the current color as an SDL_Color.
     *  @return The current SDL_Color.
     */
    SDL_Color getSDLColor(){ return color; }

    /**
     *  @brief Set the justification of the font.
     *  @param just Int to set justification to.
     */
    void setJustification(int just){ justification = just; }

    /**
     *  @brief Returns the current justification.
     *  @return Int defining current justification.
     */
    int getJustification(){ return justification; }

    /**
     *  @brief Set font size.
     *  @param size Int to set size to.
     */
    void setSize(int size){ this->size = size; }

    /**
     *  @brief Returns current font size.
     *  @return The current font size.
     */
    int getSize(){ return size; }

    int getTextWidth(const char* text);

    int getTextHeight(const char* text);

    /**
     *  @brief Returns the resource name of the font.
     *  @return Char array containing name.
     */
    std::string getName(){ return this->name; }

    /**
     *  @brief Set the resource name of the font.
     *  @param *name Char array containing name to set.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  @brief Set color using RGB values. Accepts values from 0 - 255.
     *  @param r The red value.
     *  @param g The green value.
     *  @param b The blue value.
     */
    void setColor(Uint8 r, Uint8 g, Uint8 b) { color.r = r; color.g = g; color.b = b; }

    /**
     *  @brief Set the alpha. Accepts values from 0 - 255.
     *  @param a The alpha value.
     */
    void setAlpha(Uint8 a) { color.a = a; }

private:
    TTF_Font* font;
    SDL_Color color;
    int justification, size;
    const char *fontFilename;
    std::string name;
};
}

#endif
