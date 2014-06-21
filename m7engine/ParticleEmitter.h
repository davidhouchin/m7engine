/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Particle Emitter
 *  ParticleEmitter.h
 *  Purpose: Particle emitter system to handle SFX.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef PARTICLEEMITTER_H
#define	PARTICLEEMITTER_H

#include <allegro5/allegro.h>
#include <math.h>
#include <vector>
#include "Vector2.h"
#include "Entity.h"
#include "Logger.h"

namespace M7engine {
class Particle : public Entity {
friend class ParticleEmitter;

protected:
    ALLEGRO_COLOR color;

    void draw() {
        if (image) {
            image->setColor(color);
            image->setScale(scale);
            image->draw(this->getX(), this->getY());
        }
    }
};

class ParticleEmitter : public Entity {
public:
    ParticleEmitter();
    virtual ~ParticleEmitter();
    /**
     *  Set the position of the emitter manually using X and Y coordinates.
     *  @param x The X position to set.
     *  @param y The Y position to set.
     */
    void setPosition(double x, double y){ position.set(x, y); }
    /**
     *  Set the position of the emitter using a vector.
     *  @param vector The vector to set position to.
     */
    void setPosition(Vector2 vector){ position = vector; }
    /**
     *  Returns the vector position of the emitter.
     *  @return The position in vector format.
     */
    Vector2 getPosition(){ return position; }
    /**
     *  Set the direction of the emitter.
     *  @param dir The direction in 0-360.
     */
    void setDirection(double dir){ direction = dir; }
    /**
     *  Returns the direction of the emitter.
     *  @return The direction of the emitter.
     */
    double getDirection(){ return direction; }
    /**
     *  Set the maximum number of particles to emit.
     *  @param max The maximum number of particles to emit.
     */
    void setMax(int max){ this->max = max; }
    /**
     *  Set the minumum and maximum transparency values particles can be randomly spawned with.
     *  @param min The minumum alpha value that could be set.
     *  @param max The maximum alpha value that could be set.
     */
    void setAlphaRange(int min, int max){ alphaMin = min; alphaMax = max; }
    /**
     *  Set the minumum and maximum values for randomly setting the color in a spawned particle.
     *  @param r1 Minumum red value that could be set.
     *  @param g1 Minumum green value that could be set.
     *  @param b1 Minumum blue value that could be set.
     *  @param r2 Maximum red value that could be set.
     *  @param g2 Maximum green value that could be set.
     *  @param b2 Maximum blue value that could be set.
     */
    void setColorRange(int r1, int g1, int b1, int r2, int g2, int b2) {
        minR = r1; minG = g1; minB = b1; maxR = r2; maxG = g2; maxB = b2;
    }
    /**
     *  Set the spread in direction for emitting particles.
     *  @param spr The spread to emit particles from the emitter's facing direction.
     */
    void setSpread(int spr){ spread = spr; }
    /**
     *  Set the distance that particles will travel before removing themselves or resetting position.
     *  @param len The distance to set.
     */
    void setLength(double len){ length = len; }
    /**
     *  Set the velocity that particles will travel at.
     *  @param vel The velocity for particles to travel at.
     */
    void setVelocity(double vel){ velocity = vel; }
    /**
     *  Loads an image to use for each particle. Returns true if successful.
     *  @param *filename A char array containing the resource name to request.
     */
    bool loadImage(const char* filename);
    /**
     *  Sets the image directly using a sprite.
     *  @param *setSprite The sprite to change to.
     */
    void setImage(Sprite *setSprite);
    /**
     *  Reload bitmap from disk.
     */
    void reloadImage();
    /**
     *  Main drawing function called per frame.
     */
    void draw();
    /**
     *  Main update function to be called per frame. Must be implemented by child.
     */
    void update();
    /**
     *  Adds a particle(s) to the emitter using the specified particle traits.
     */
    void add();
    /**
     *  Returns a pointer to the used sprite.
     *  @return A pointer to the used sprite.
     */
    Sprite* getSprite() { return image; }

private:
    typedef std::vector<Entity*>::iterator iter;
    std::vector<Entity*> particles;
    Sprite *image;
    Vector2 position;
    double direction, length, velocity;
    int max, alphaMin, alphaMax, minR, minG, minB, maxR, maxG, maxB, spread;
    const char *resourceName;
};
}
#endif
