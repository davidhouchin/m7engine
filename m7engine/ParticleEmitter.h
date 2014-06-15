/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef PARTICLEEMITTER_H
#define	PARTICLEEMITTER_H

#include <allegro5/allegro.h>
#include <math.h>
#include <vector>
#include "Vector2.h"
#include "Entity.h"
#include "Logger.h"

namespace M7engine
{
class Particle : public Entity
{
friend class ParticleEmitter;

protected:
	ALLEGRO_COLOR color;

	void draw()
	{
		if (image)
		{
			image->setColor(color);
			image->setScale(scale);
			image->draw(this->getX(), this->getY());
		}
	}
};

class ParticleEmitter : public Entity
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();
	void setPosition(double x, double y){ position.set(x, y); }
	void setPosition(Vector2 arg){ position = arg; }
	Vector2 getPosition(){ return position; }
	void setDirection(double arg){ direction = arg; }
	double getDirection(){ return direction; }
	void setMax(int arg){ max = arg; }
	void setAlphaRange(int min, int max){ alphaMin = min; alphaMax = max; }
	void setColorRange(int r1, int g1, int b1, int r2, int g2, int b2)
	{
		minR = r1; minG = g1; minB = b1; maxR = r2; maxG = g2; maxB = b2;
	}
	void setSpread(int arg){ spread = arg; }
	void setLength(double arg){ length = arg; }
	void setVelocity(double arg){ velocity = arg; }
	bool loadImage(const char* filename);
	void setImage(Sprite *setSprite);
	void reloadImage();
	void draw();
	void update();
	void add();
	Sprite* getSprite() { return image; }

private:
	typedef std::vector<Entity*>::iterator iter;
	std::vector<Entity*> particles;
	Sprite *image;
	Vector2 position;
	double direction, length, velocity;
	int max, alphaMin, alphaMax, minR, minG, minB, maxR, maxG, maxB, spread;
	const char *bitmapFilename;

};
}
#endif
