/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace M7engine
{
class Primitives
{
public:
	Primitives();
	virtual ~Primitives();

	bool init();

	void drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);

	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color, float thickness);
	void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color);

	void drawRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
	void drawFilledRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);
	void drawRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color, float thickness);
	void drawFilledRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color);

	void drawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color, float thickness);
	void drawFilledEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color);

	void drawCircle(float cx, float cy, float r, ALLEGRO_COLOR color, float thickness);
	void drawFilledCircle(float cx, float cy, float r, ALLEGRO_COLOR color);

	void drawArc(float cx, float cy, float r, float start_theta, float delta_theta, ALLEGRO_COLOR color, float thickness);
};
}
#endif
