/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
     *  Returns width of sprite.
     *  @return The current width.
     */
    int getWidth() { return this->width; }

    /**
     *  Set width of sprite.
     *  @param width Int to set width to.
     */
    void setWidth(int width) { this->width = width; }

    /**
     *  Returns height of sprite.
     *  @return The current height.
     */
    int getHeight() { return this->height; }

    /**
     *  Set height of sprite.
     *  @param height Int to set height to.
     */
    void setHeight(int height) { this->height = height; }

    /**
     *  Returns image scale of sprite.
     *  @return The current image scale.
     */
    double getScale() { return scale; }

    /**
     *  Set the image scale of the sprite.
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
     *  @return String containing resource name of bitmap.
     */
    std::string getName(){ return this->name; }

    /**
     *  Sets the resource name of the bitmap.
     *  @param name String containing resource name to set.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  Returns the current frame.
     *  @return Current frame.
     */
    int getFrame() { return this->frame; }

    /**
     *  Returns the total number of frames.
     *  @return Total number of frames.
     */
    int getMaxFrames() { return this->maxFrames; }

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
     *  Returns the current color as a SDL_Color.
     *  @return The current SDL_Color.
     */
    SDL_Color getColor() { return color; }

    /**
     *  Set color using RGB values. Accepts values from 0 - 255.
     *  @param r The red value.
     *  @param g The green value.
     *  @param b The blue value.
     */
    void setColor(Uint8 r, Uint8 g, Uint8 b) { color.r = r; color.g = g; color.b = b; SDL_SetTextureColorMod(frameList[frame], color.r, color.g, color.b); }

    /**
     *  Set the alpha. Accepts values from 0 - 255.
     *  @param a The alpha value.
     */
    void setAlpha(Uint8 a) { color.a = a; SDL_SetTextureAlphaMod(frameList[frame], color.a); }

private:
    int width, height, frame, maxFrames, frameWidth, frameHeight, columns, delay, step;
    double rotation, scale;
    SDL_Texture* texture;
    SDL_Color color;
    std::vector<SDL_Texture*> frameList;
    const char *textureFilename;
    std::string name;
};
};

#endif
