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
#include "M7engine.h"

namespace M7engine {
Entity::Entity()
{
    id                        = -1; //ID pointing to this instance
    visible                 = true; //Is this object viewable?
    active                  = true; //Does this object get updated?
    image                   = NULL; //Pointer to sprite used
    resourceName              = ""; //Name of the resource from the resource manager
    name                      = ""; //Name of object
    family                    = ""; //Name of family object belongs to
    depth                      = 0; //The display depth of the object
    xOffset                    = 0; //The sprite origin x
    yOffset                    = 0; //The sprite origin y
    direction                  = 0; //Direction object is pointing
    hSpeed                     = 0; //Horizontal speed
    vSpeed                     = 0; //Vertical speed
    width                      = 1; //Width of entity
    height                     = 1; //Height of entity
    scale                      = 1; //Image scale to display at
    color  = { 255, 255, 255, 255}; //RGBA color values
    solid                  = false; //Is considered solid for collision detection?

    setPosition(0, 0);
    setVelocity(0, 0);

    Engine::getInstance()->addEntity(this);
}

Entity::~Entity()
{
}

bool Entity::setProperties(ConfigReader *reader, std::string name)
{
    family = reader->getString(name, "family", "");

    resourceName = reader->getString(name, "sprite", "");
    setImage(ResourceManager::getInstance()->getSprite(resourceName.c_str()));

    depth = reader->getInt(name, "depth", 0);

    width = reader->getInt(name, "width", 1);
    height = reader->getInt(name, "height", 1);

    xOffset = reader->getInt(name, "xoffset", 0);
    yOffset = reader->getInt(name, "yoffset", 0);

    scale = reader->getInt(name, "scale", 1);

    visible = reader->getBool(name, "visible", true);

    solid = reader->getBool(name, "solid", false);

    color.r = reader->getInt(name, "r", 255);
    color.g = reader->getInt(name, "g", 255);
    color.b = reader->getInt(name, "b", 255);
    color.a = reader->getInt(name, "a", 255);
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
    if (this->image != NULL) { this->image->changeFrame(0); }
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
    //this->setX(this->getX() + this->velocity.getX());
    //this->setY(this->getY() + this->velocity.getY());
    setX(getX() + hSpeed);
    setY(getY() + vSpeed);
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
