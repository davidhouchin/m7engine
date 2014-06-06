/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "Font.h"

namespace M7engine
{
	Font::Font()
	{
	}

	Font::~Font()
	{
		al_destroy_font(font);
	}

	bool Font::loadFont(const char *filename, int size)
	{
		font = al_load_ttf_font(filename, size, 0);
		if (!font)
		{
			fprintf(stderr, "Failed to load font: '%s'\n", filename);
			return false;
		}

		return true;
	}

	void Font::setFont(ALLEGRO_FONT *arg)
	{
		font = arg;
	}

	FontManager::FontManager()
	{
	}

	FontManager::~FontManager()
	{
	}

	bool FontManager::init()
	{
		al_init_font_addon();

		if (!al_init_ttf_addon())
		{
			fprintf(stderr, "al_init_ttf_addon failed\n");
			return false;
		}

		return true;
	}

	void FontManager::drawText(float x, float y, Font *font, const char *text)
	{
		al_draw_text(font->getFont(), font->getColor(), x, y, font->getJustification(), text);
	}

	void FontManager::drawTextF(float x, float y, Font *font, const char *text, ...)
	{
		//char buffer[strlen(text)];
		va_list args;
		va_start(args, text);
		//vsprintf(buffer, text, args);
		//al_draw_text(font->getFont(), font->getColor(), x, y, font->getJustification(), buffer);
		va_end(args);

	}

}
