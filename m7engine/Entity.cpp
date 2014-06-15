/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "Entity.h"

namespace M7engine
{
Entity::Entity()
{
	this->id = -1;
	this->visible = true;
	this->active = true;
	this->image = NULL;
	this->setPosition(128, 128);
	this->direction = 0;
	this->scale = 1;
	this->color = al_map_rgb(255, 255, 255);
}

Entity::~Entity()
{
	delete image;
}

bool Entity::loadImage(const char *filename)
{
	if (!image)
	{
		image = new Sprite;
	}

	Logger::getInstance()->logMessage(0, "Entity ID %i loading image: '%s'", id, filename);
	image->loadImage(filename);
	if (!image)
	{
		Logger::getInstance()->logError(0, "Entity failed to set bitmap: '%s'", filename);
		return false;
	}
	else
	{
		this->setSize(image->getWidth(), image->getHeight());
		return true;
	}
}

bool Entity::loadImage(const char *filename, int width, int height, int columns, int frames)
{
	if (!image)
	{
		image = new Sprite;
	}

	Logger::getInstance()->logMessage(0, "Entity ID %i loading image: '%s'", id, filename);
	image->loadImage(filename, width, height, columns, frames);
	if (!image)
	{
		Logger::getInstance()->logError(0, "Entity failed to set bitmap: '%s'", filename);
		return false;
	}
	else
	{
		this->setSize(image->getWidth(), image->getHeight());
		return true;
	}
}

void Entity::setImage(Sprite *image)
{
	this->image = image;
	this->setSize(image->getWidth(), image->getHeight());
}

void Entity::reloadImage()
{
	/*if (image != NULL)
	{
		image->reloadBitmap();
	}*/
}

void Entity::draw()
{
	if (image)
	{
		Logger::getInstance()->logMessage(99, "%i is drawing->", id);
		
		image->setScale(this->getScale());
		image->setColor(this->getColor());
		image->draw(this->getX(), this->getY());
	}
}

void Entity::move()
{
	this->setX(this->getX() + this->velocity.getX());
	this->setY(this->getY() + this->velocity.getY());
}

void Entity::updateTimers()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (timer[i] != 0) 
		{ 
			timer[i]--;
			if (timer[i] == 0)
			{
				alarm(i);
			}
		}
	}
}
}
