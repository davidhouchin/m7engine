/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "Sprite.h"

namespace M7engine
{
Sprite::Sprite()
{
	Logger::getInstance()->logMessage(0, "Sprite created");

	this->bitmap = NULL;
	this->width = 1;
	this->height = 1;
	this->rotation = 0;
	this->scale = 1;
	this->color = al_map_rgb(255, 255, 255);
}

Sprite::~Sprite()
{
	if (bitmap != NULL)
	{
		Logger::getInstance()->logError(0, "Sprite destroying self: %s", bitmapFilename);
		al_destroy_bitmap(bitmap);
	}
}

bool Sprite::loadImage(const char *filename)
{
	Logger::getInstance()->logMessage(0, "Sprite loading image: '%s'", filename);
	if (bitmap != NULL)
	{
		al_destroy_bitmap(bitmap);
	}

	bitmap = al_load_bitmap(filename);
	if (!bitmap)
	{
		Logger::getInstance()->logError(0, "Sprite failed to load bitmap: '%s'", filename);
		return false;
	}
	else
	{
		frameList.push_back(bitmap);
		this->bitmapFilename = filename;
		this->frame = 0;
		this->maxFrames = 1;
		this->setSize(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));
		return true;
	}
}

bool Sprite::loadImage(const char *filename, int width, int height, int columns, int frames)
{
	if (bitmap != NULL)
	{
		al_destroy_bitmap(bitmap);
	}

	bitmap = al_load_bitmap(filename);
	if (!bitmap)
	{
		Logger::getInstance()->logError(0, "Failed to load bitmap: '%s'", filename);
		return false;
	}
	else
	{
		this->bitmapFilename = filename;

		this->setSize(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));

		ALLEGRO_BITMAP *tempBitmap = NULL;
		int tempX = 0;
		int tempY = 0;
		this->frame = 0;
		this->maxFrames = frames;
		this->frameWidth = width;
		this->frameHeight = height;
		this->columns = columns;

		for (int i = 0; i < frames; i++)
		{
			tempBitmap = al_create_bitmap(width, height);
			tempX = 0 + (i % columns) * width;
			tempY = 0 + (i / columns) * height;
			Logger::getInstance()->logMessage(0, "Sprite creating frame %i at %i %i", i, tempX, tempY);
			al_set_target_bitmap(tempBitmap);
			al_draw_bitmap_region(bitmap, tempX, tempY, width, height, 0, 0, 0);
			frameList.push_back(tempBitmap);
		}

		return true;
	}
}

bool Sprite::reloadBitmap()
{
	if (bitmap != NULL)
	{
		this->frameList.clear();

		if (maxFrames > 1) { this->loadImage(this->bitmapFilename, this->frameWidth, this->frameHeight, this->columns, this->maxFrames); }
		else { this->loadImage(this->bitmapFilename); }

		if (!bitmap)
		{
			Logger::getInstance()->logError(0, "Sprite failed to reload bitmap: '%s'", bitmapFilename);
			return false;
		}
		else
		{
			Logger::getInstance()->logMessage(0, "Sprite reloaded successfully");
			return true;
		}
	}
	return false;
}

void Sprite::changeFrame(int changeTo)
{
	this->frame = changeTo;

	if (this->frame > this->maxFrames){ this->frame = 0; }
	if (this->frame < 0){ this->frame = this->maxFrames; }
}

void Sprite::nextFrame()
{
	this->frame++;
	if (frame > maxFrames-1){ frame = 0; }
}

void Sprite::previousFrame()
{
	this->frame--;
	if (frame < 0){ frame = maxFrames-1; }
}

void Sprite::draw(int x, int y)
{
	if (bitmap)
	{
		if (this->maxFrames > 0)
		{
			if (this->maxFrames > 1) { Logger::getInstance()->logMessage(99, "Frame: %i", frame); }
			bitmap = frameList[this->frame];
			al_draw_tinted_scaled_rotated_bitmap(bitmap, color, 0, 0, x, y, scale, scale, rotation, 0);

			step++;
			if (step == delay)
			{
				step = 0;
				this->nextFrame();
			}
		}
	}
}
}