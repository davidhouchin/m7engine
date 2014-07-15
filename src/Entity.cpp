/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Entity
 *  Entity.cpp
 *  Purpose: The base class for main game objects.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Entity.h"

namespace M7engine {
Entity::Entity()
{
    id = -1;
    visible = true;
    active = true;
    image = NULL;
    resourceName = "";
    direction = 0;
    width = 1;
    height = 1;
    scale = 1;
    color = { 0, 0, 0, 255};

    setPosition(0, 0);
    setVelocity(0, 0);
}

Entity::~Entity()
{
    delete image;
}

bool Entity::loadImage(const char *filename)
{
    if (!image) {
        image = new Sprite;
    }

    Logger::getInstance()->logMessage(0, "Entity ID %i loading image: '%s'", id, filename);
    image->loadImage(filename);
    if (!image) {
        Logger::getInstance()->logError(0, "Entity failed to set bitmap: '%s'", filename);
        return false;
    } else {
        this->setSize(image->getWidth(), image->getHeight());
        return true;
    }
}

bool Entity::loadImage(const char *filename, int width, int height, int columns, int frames)
{
    if (!image) {
        image = new Sprite;
    }

    Logger::getInstance()->logMessage(0, "Entity ID %i loading image: '%s'", id, filename);
    image->loadImage(filename, width, height, columns, frames);
    if (!image) {
        Logger::getInstance()->logError(0, "Entity failed to set bitmap: '%s'", filename);
        return false;
    } else {
        this->setSize(image->getWidth(), image->getHeight());
        return true;
    }
}

void Entity::setImage(Sprite *image)
{
    this->image = image;
    this->setSize(image->getWidth(), image->getHeight());
    this->resourceName = image->getName();
}

void Entity::reloadImage()
{
    /*if (image != NULL) {
        image = ResourceManager::getInstance()->getSprite(resourceName);

        if (!image) {
            Logger::getInstance()->logError(0, "Failed to reload bitmap: '%s'", resourceName);
        }
    }*/
}

void Entity::draw()
{
    if (image) {
        Logger::getInstance()->logMessage(99, "%i is drawing->", id);

        image->setScale(this->getScale());
        image->setColor(color.r, color.g, color.b);
        image->setAlpha(color.a);
        image->draw(this->getX(), this->getY());
    }
}

void Entity::move()
{
    this->setX(this->getX() + this->velocity.getX());
    this->setY(this->getY() + this->velocity.getY());
}

void Entity::updateTimers()
{
    int i;
    for (i = 0; i < TIMER_NUM; i++) {
        if (timer[i] != 0) {
            timer[i]--;
            if (timer[i] == 0) {
                alarm(i);
            }
        }
    }
}
}
