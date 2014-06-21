/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Font
 *  Font.cpp
 *  Purpose: Font class to be drawn by FontManager.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Font.h"

namespace M7engine {
Font::Font() {
}

Font::~Font() {
    al_destroy_font(font);
}

bool Font::loadFont(const char *filename, int size) {
    font = al_load_ttf_font(filename, size, 0);
    setSize(size);
    this->fontFilename = filename;
    if (!font) {
        Logger::getInstance()->logError(0, "Failed to load font: '%s'", filename);
        return false;
    }

    return true;
}

void Font::setFont(ALLEGRO_FONT *arg) {
    font = arg;
}

bool Font::reloadFont() {
    al_destroy_font(font);
    font = al_load_ttf_font(fontFilename, size, 0);
    if (!font) {
        Logger::getInstance()->logError(0, "Failed to load font: '%s'", fontFilename);
        return false;
    }
    return true;
}

FontManager::FontManager() {
}

FontManager::~FontManager() {
}

bool FontManager::init() {
    al_init_font_addon();

    if (!al_init_ttf_addon()) {
        Logger::getInstance()->logError(0, "al_init_ttf addon failed");
        return false;
    }

    return true;
}

void FontManager::drawText(float x, float y, Font *font, const char *text) {
    al_draw_text(font->getFont(), font->getColor(), x, y, font->getJustification(), text);
}

void FontManager::drawTextF(float x, float y, Font *font, const char *text, ...) {
    char buffer[99];
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    al_draw_text(font->getFont(), font->getColor(), x, y, font->getJustification(), buffer);
    va_end(args);
}
}
