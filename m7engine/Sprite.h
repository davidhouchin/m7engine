/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Sprite
 *  Sprite.h
 *  Purpose: Main class for encasing bitmaps.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>
#include "Logger.h"

namespace M7engine {
class Sprite {
public:
    Sprite();
    virtual ~Sprite();

    /**
     *  Load bitmap to use.
     *  @param *filename The filename to load.
     */
    bool loadImage(const char *filename);
    /**
     *  Load bitmap to use, specifying parameters for animation.
     *  @param *filename The filename to load.
     *  @param width Width of an individual frame.
     *  @param height Height of an individual frame.
     *  @param columns Number of columns in base image of individual frames.
     *  @param frames Total number of animation frames.
     */
    bool loadImage(const char *filename, int width, int height, int columns, int frames);
    /**
     *  Reload bitmap from disk.
     */
    bool reloadBitmap();
    /**
     *  Draws the sprite to the position specified.
     *  @param x The X coordinate to draw to.
     *  @param y The Y coordinate to draw to.
     */
    void draw(int x, int y);

    /**
     *  Set size by specifying width and height.
     *  @param width Width to set.
     *  @param height Height to set.
     */
    void setSize(int width, int height) { this->width = width; this->height = height; }
    /**
     *  Returns width of entity.
     *  @return The current width.
     */
    int getWidth() { return this->width; }
    /**
     *  Set width of entity.
     *  @param width Int to set width to.
     */
    void setWidth(int width) { this->width = width; }
    /**
     *  Returns height of entity.
     *  @return The current height.
     */
    int getHeight() { return this->height; }
    /**
     *  Set height of entity.
     *  @param height Int to set height to.
     */
    void setHeight(int height) { this->height = height; }
    /**
     *  Returns image scale of entity.
     *  @return The current image scale.
     */
    double getScale() { return scale; }
    /**
     *  Set the image scale of the entity.
     *  @param scale Int to set scale to.
     */
    void setScale(double scale) { this->scale = scale; }

    /**
     *  Returns the animation delay time.
     *  @return Int specifying animation delay time.
     */
    int getDelay() { return this->delay; }
    /**
     *  Set the animation delay time before alternating frames.
     *  @param delay The animation delay time.
     */
    void setDelay(int delay) { this->delay = delay; }

    /**
     *  Returns the resource name of the bitmap.
     *  @return Char array containing resource name of bitmap.
     */
    const char* getName(){ return this->name; }
    /**
     *  Sets the resource name of the bitmap.
     *  @param *name Char array containing resource name to set.
     */
    void setName(const char *name) { this->name = name; }

    /**
     *  Change the animation frame to the specified frame.
     *  @return Frame to jump to.
     */
    void changeFrame(int frame);
    /**
     *  Proceed to the next frame. Resets to frame 0 if at last frame.
     */
    void nextFrame();
    /**
     *  Move to the previous frame. Jumps to the last frame if at frame 0.
     */
    void previousFrame();

    /**
     *  Returns the current color as an ALLEGRO_COLOR.
     *  @return The current ALLEGRO_COLOR.
     */
    ALLEGRO_COLOR getColor() { return color; }
    /**
     *  Set color using ALLEGRO_COLOR.
     *  @param color ALLEGRO_COLOR to use.
     */
    void setColor(ALLEGRO_COLOR color) { this->color = color; }

private:
    int width, height, frame, maxFrames, frameWidth, frameHeight, columns, delay, step;
    double rotation, scale;
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR color;
    std::vector<ALLEGRO_BITMAP*> frameList;
    const char *bitmapFilename, *name;
};
};

#endif
