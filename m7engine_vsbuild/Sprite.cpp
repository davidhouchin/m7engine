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
		fprintf(stdout, "Sprite created.\n");
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
			fprintf(stderr, "Sprite destroying self: %s\n", bitmapFilename);
			al_destroy_bitmap(bitmap);
		}
	}

	bool Sprite::loadImage(const char *filename)
	{
		fprintf(stdout, "Sprite loading image: '%s'\n", filename);
		if (bitmap != NULL)
		{
			al_destroy_bitmap(bitmap);
		}

		bitmap = al_load_bitmap(filename);
		if (!bitmap)
		{
			fprintf(stderr, "Sprite failed to load bitmap: '%s'\n", filename);
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
			fprintf(stderr, "Failed to load bitmap: '%s'\n", filename);
			return false;
		}
		else
		{
			this->bitmapFilename = filename;

			ALLEGRO_BITMAP *tempBitmap = NULL;
			int tempX = 0;
			int tempY = 0;
			this->frame = 0;
			this->maxFrames = frames;
			this->frameWidth = width;
			this->frameHeight = height;
			this->columns = columns;

			al_set_target_bitmap(tempBitmap);

			for (int i = 0; i < frames; i++)
			{
				tempBitmap = al_create_bitmap(width, height);
				tempX = 0 + (i % columns) * width;
				tempY = 0 + (i / columns) * height;
				al_draw_bitmap_region(bitmap, tempX, tempY, width, height, 0, 0, 0);
				frameList.push_back(bitmap);
			}

			return true;
		}
	}

	bool Sprite::reloadBitmap()
	{
		if (bitmap != NULL)
		{
			this->frameList.clear();

			if (maxFrames > 1) { this->loadImage(this->bitmapFilename, this->width, this->height, this->columns, this->maxFrames); }
			else { this->loadImage(this->bitmapFilename); }

			if (!bitmap)
			{
				fprintf(stderr, "Sprite failed to reload bitmap: '%s'\n", bitmapFilename);
				return false;
			}
			else
			{
				fprintf(stderr, "Sprite reloaded successfully.\n");
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
		if (frame > maxFrames){ frame = 0; }
	}

	void Sprite::previousFrame()
	{
		this->frame--;
		if (frame < 0){ frame = maxFrames; }
	}

	void Sprite::draw(int x, int y)
	{
		if (bitmap)
		{
			if (this->maxFrames > 0)
			{
				fprintf(stderr, "Frame: %i\n", frame);
				bitmap = frameList[this->frame];
				al_draw_tinted_scaled_rotated_bitmap(bitmap, color, 0, 0, x, y, scale, scale, rotation, 0);
			}
		}

	}
}