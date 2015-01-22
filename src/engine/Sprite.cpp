/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Sprite
 *  Sprite.cpp
 *  Purpose: Main class for encasing bitmaps.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Sprite.h"
#include "M7engine.h"

namespace M7engine {
Sprite::Sprite()
{
    Logger::getInstance()->logMessage(1, "Sprite created");

    texture = NULL;
    width = 1;
    height = 1;
    rotation = 0;
    scale = 1;
    frame = 0;
    maxFrames = 1;
    frameWidth = 1;
    frameHeight = 1;
    columns = 1;
    delay = 0;
    step = 0;
    color = { 0, 0, 0, 255 };
}

Sprite::~Sprite()
{
    if (texture != NULL) {
        Logger::getInstance()->logError(1, "Sprite destroying self: %s", textureFilename);
        SDL_DestroyTexture(texture);
    }
}

bool Sprite::loadImage(const char *filename)
{
    Logger::getInstance()->logMessage(0, "Sprite '%s' loading image: '%s'", name.c_str(), filename);
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    texture = IMG_LoadTexture(Engine::getInstance()->getRenderer(), filename);
    if (texture == NULL) {
        Logger::getInstance()->logError(0, "Sprite '%s' failed to load bitmap: '%s'", name.c_str(), filename);
        Logger::getInstance()->logError(0, "SDL error: %s", IMG_GetError());
        return false;
    } else {
        frameList.push_back(texture);
        this->textureFilename = filename;
        this->frame = 0;
        this->maxFrames = 1;
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        this->setSize(w, h);
        return true;
    }
}

bool Sprite::loadImage(const char *filename, int width, int height, int columns, int frames)
{
    if (!width || !height || !columns || !frames) {
        this->loadImage(filename);
        return true;
    }

    Logger::getInstance()->logMessage(0, "Sprite '%s' loading image: '%s'", name.c_str(), filename);

    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    SDL_Surface *loadSurface = IMG_Load(filename);
    if (loadSurface == NULL) {
        Logger::getInstance()->logError(0, "Sprite '%s' failed to load bitmap: '%s'", name.c_str(), filename);
        Logger::getInstance()->logError(0, "SDL error: %s", IMG_GetError());
        return false;
    } else {
        this->textureFilename = filename;

        this->setSize(width, height);

        //SDL_Surface *tempSurface = NULL;
        this->frame = 0;
        this->maxFrames = frames;
        this->frameWidth = width;
        this->frameHeight = height;
        this->columns = columns;

        Uint32 rmask, gmask, bmask, amask;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
        #endif

        for (int i = 0; i < frames; i++) {
            SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
            SDL_Rect srcrect;
            srcrect.x = 0 + (i % columns) * width;
            srcrect.y = 0 + (i / columns) * height;
            srcrect.w = width;
            srcrect.h = height;

            Logger::getInstance()->logMessage(1, "Sprite creating frame %i at %i %i", i, srcrect.y, srcrect.x);

            SDL_BlitSurface(loadSurface, &srcrect, tempSurface, NULL);
            SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), tempSurface);
            if (newTexture == NULL) {Logger::getInstance()->logError(0, "SDL_CreateTextureFromSurface failed");}
            frameList.push_back(newTexture);

            SDL_FreeSurface(tempSurface);
        }

        SDL_FreeSurface(loadSurface);
        return true;
    }
}

void Sprite::changeFrame(int frame)
{
    this->frame = frame;

    if (this->frame > this->maxFrames){ this->frame = 0; }
    if (this->frame < 0){ this->frame = this->maxFrames; }
}

void Sprite::nextFrame()
{
    this->frame++;
    if (frame > maxFrames-1){ frame = 0; }
}

void Sprite::previousFrame()
{
    this->frame--;
    if (frame < 0){ frame = maxFrames-1; }
}

void Sprite::draw(int x, int y)
{
    if (frameList[frame]) {
        if (this->maxFrames > 0) {
            if (this->maxFrames > 1) { Logger::getInstance()->logMessage(99, "Frame: %i", frame); }
            //texture = frameList[this->frame];

            Engine::getInstance()->renderTexture(frameList[frame], x, y, width, height);

            if (delay != -1) { step++; }
            if (step == delay) {
                step = 0;
                this->nextFrame();
            }
        }
    }
}
}
