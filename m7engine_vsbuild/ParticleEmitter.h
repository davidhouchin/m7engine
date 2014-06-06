#ifndef PARTICLEEMITTER_H
#define	PARTICLEEMITTER_H

#include <allegro5/allegro.h>
#include <math.h>
#include <vector>
#include "Vector2.h"
#include "Entity.h"

namespace M7engine
{
	class Particle : public Entity
	{
		void update()
		{
		}

		void collision(Entity *other)
		{
		}
	};

	class ParticleEmitter
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
		void setScale(double arg){ scale = arg; }
		bool loadImage(const char* filename);
		void draw();
		void update();
		void add();

	private:
		typedef std::vector<Entity*>::iterator iter;
		std::vector<Entity*> particles;
		ALLEGRO_BITMAP *image;
		Vector2 position;
		double direction, length, velocity, scale;
		int max, alphaMin, alphaMax, minR, minG, minB, maxR, maxG, maxB, spread;

	};
}
#endif
