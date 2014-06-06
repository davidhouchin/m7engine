/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef ENTITY_H
#define	ENTITY_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include "Vector2.h"

namespace M7engine
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		bool loadImage(const char *filename);
		void setImage(ALLEGRO_BITMAP *image);
		virtual void update() = 0;
		virtual void collision(Entity *other) = 0;
		void move();
		void draw();

		Vector2 getPosition() { return position; }
		void setPosition(Vector2 arg) { this->position = arg; }
		void setPosition(double x, double y) { position.set(x, y); }
		double getX() { return position.getX(); }
		double getY() { return position.getY(); }
		void setX(double x) { position.setX(x); }
		void setY(double y) { position.setY(y); }

		void setID(int arg) { id = arg; }
		int getID() { return id; }

		bool getVisible() { return visible; }
		void setVisible(bool arg) { visible = arg; }

		bool getActive() { return active; }
		void setActive(bool arg) { active = arg; }

		Vector2 getVelocity(){ return velocity; }
		void setVelocity(Vector2 v){ this->velocity = v; }
		void setVelocity(double x, double y){ velocity.setX(x); velocity.setY(y); }

		void setSize(int width, int height) { this->width = width; this->height = height; }
		void setSizeToImageScale() { this->width = width * scale; this->height = height * scale; }
		int getWidth() { return this->width; }
		void setWidth(int arg) { this->width = arg; }
		int getHeight() { return this->height; }
		void setHeight(int arg) { this->height = arg; }

		int getDirection() { return direction; }
		void setDirection(int arg) { direction = arg; }

		double getRotation() { return rotation; }
		void setRotation(double arg) { rotation = arg; }
		double getScale() { return scale; }
		void setScale(double arg) { scale = arg; }

		ALLEGRO_COLOR getColor() { return color; }
		void setColor(ALLEGRO_COLOR arg) { color = arg; }

	private:
		int id, width, height, direction;
		double rotation, scale;
		bool visible, active;
		Vector2 position, velocity;
		ALLEGRO_BITMAP *image;
		ALLEGRO_COLOR color;
	};
}

#endif
