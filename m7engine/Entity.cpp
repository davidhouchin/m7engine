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
	this->image = new Sprite();
	this->setPosition(128, 128);
	this->direction = 0;
}

Entity::~Entity()
{
	delete image;
}

bool Entity::loadImage(const char *filename)
{
	fprintf(stdout, "Entity ID %i loading image: '%s'\n", id, filename);
	image->loadImage(filename);
	if (!image)
	{
		fprintf(stderr, "Entity failed to set bitmap: '%s'\n", filename);
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
	if (image != NULL)
	{
		image->reloadBitmap();
	}
}

void Entity::draw()
{
	if (image)
	{
		#ifdef DEBUG_CYCLE
		fprintf(stderr, "%i is drawing->\n", id);
		#endif
		image->draw(this->getX(), this->getY());
	}
}

void Entity::move()
{
	this->setX(this->getX() + this->velocity.getX());
	this->setY(this->getY() + this->velocity.getY());
}
}
