/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>

namespace M7engine
{
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	bool loadImage(const char *filename);
	bool loadImage(const char *filename, int width, int height, int columns, int frames);
	bool reloadBitmap();
	void draw(int x, int y);

	void setSize(int width, int height) { this->width = width; this->height = height; }
	int getWidth() { return this->width; }
	void setWidth(int arg) { this->width = arg; }
	int getHeight() { return this->height; }
	void setHeight(int arg) { this->height = arg; }
	double getScale() { return scale; }
	void setScale(double arg) { scale = arg; }

	void changeFrame(int frame);
	void nextFrame();
	void previousFrame();
		
	ALLEGRO_COLOR getColor() { return color; }
	void setColor(ALLEGRO_COLOR arg) { color = arg; }

private:
	int width, height, frame, maxFrames, frameWidth, frameHeight, columns;
	double rotation, scale;
	ALLEGRO_BITMAP *bitmap;
	ALLEGRO_COLOR color;
	std::vector<ALLEGRO_BITMAP*> frameList;
	const char *bitmapFilename;
};
};

#endif