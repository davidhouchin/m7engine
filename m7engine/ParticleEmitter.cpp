/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "ParticleEmitter.h"

namespace M7engine
{
ParticleEmitter::ParticleEmitter()
{
	max = 100;
	length = 100;
	direction = 0;
	alphaMin = 254;
	alphaMax = 255;
	minR = 0;
	maxR = 255;
	minG = 0;
	maxG = 255;
	minB = 0;
	maxB = 255;
	spread = 10;
	velocity = 1;
}

ParticleEmitter::~ParticleEmitter()
{
	delete image;

	for (iter i = particles.begin(); i != particles.end(); ++i)
	{
		delete *i;
	}

	particles.clear();
}

bool ParticleEmitter::loadImage(const char* filename)
{
	image->loadImage(filename);
	if (!image)
	{
		Logger::getInstance()->logError(0, "Particle emitter failed to load particle image: '%s'", filename);
		return false;
	}

	this->bitmapFilename = filename;
	return true;
}

void ParticleEmitter::setImage(Sprite *setSprite)
{
	this->image = setSprite;
	this->setSize(setSprite->getWidth(), setSprite->getHeight());
}

void ParticleEmitter::reloadImage()
{
	if (image != NULL)
	{
		image->reloadBitmap();
		if (!image)
		{
			Logger::getInstance()->logError(0, "Failed to reload bitmap: '%s'", bitmapFilename);
		}
		else
		{
			for (iter i = particles.begin(); i != particles.end(); ++i)
			{
				(*i)->setImage(this->image);
			}
		}
	}
}

void ParticleEmitter::add()
{
	static double PI_DIV_180 = 3.1415926535 / 180;
	double vx, vy;

	Particle *p = new Particle();
	p->setImage(image);

	p->setPosition(position.getX(), position.getY());
	double variation = (rand() % spread - spread / 2) / 100.0f;

	double dir = direction - 90;
	vx = cos(dir * PI_DIV_180) + variation;
	vy = sin(dir * PI_DIV_180) + variation;
	p->setVelocity(vx * velocity, vy * velocity);

	int r = rand() % (maxR - minR) + minR;
	int g = rand() % (maxG - minG) + minG;
	int b = rand() % (maxB - minB) + minB;
	int a = rand() % (alphaMax - alphaMin) + alphaMin;

	p->color = al_map_rgba(r, g, b, a);

	p->setScale(this->getScale());

	particles.push_back(p);
}

void ParticleEmitter::draw()
{
	al_hold_bitmap_drawing(1);
	for (iter i = particles.begin(); i != particles.end(); ++i)
	{
		(*i)->draw();
	}
	al_hold_bitmap_drawing(0);
}

void ParticleEmitter::update()
{
	if ((int)particles.size() < max)
	{
		add();
	}

	for (iter i = particles.begin(); i != particles.end(); ++i)
	{
		(*i)->move();

		if ((*i)->getPosition().distance(this->position) > length)
		{
			(*i)->setX(position.getX());
			(*i)->setY(position.getY());
		}
	}
}
}
