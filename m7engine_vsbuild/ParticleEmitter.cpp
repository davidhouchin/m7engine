#include "ParticleEmitter.h"

namespace M7engine
{
	ParticleEmitter::ParticleEmitter()
	{
		image = NULL;
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
		scale = 1;
	}

	ParticleEmitter::~ParticleEmitter()
	{
		al_destroy_bitmap(image);

		for (iter i = particles.begin(); i != particles.end(); ++i)
		{
			delete *i;
		}

		particles.clear();
	}

	bool ParticleEmitter::loadImage(const char* filename)
	{
		image = al_load_bitmap(filename);

		if (!image)
		{
			fprintf(stderr, "Failed to load particle image: '%s'\n", filename);
			return false;
		}

		return true;
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
		p->setColor(al_map_rgba(r, g, b, a));

		p->setScale(scale);

		particles.push_back(p);
	}

	void ParticleEmitter::draw()
	{
		for (iter i = particles.begin(); i != particles.end(); ++i)
		{
			(*i)->draw();
		}
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
