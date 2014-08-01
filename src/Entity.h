/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Entity
 *  Entity.h
 *  Purpose: The base class for main game objects.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <stdio.h>
#include <SDL2/SDL.h>

#include "Vector2.h"
#include "Sprite.h"
#include "ConfigReader.h"
#include "ResourceManager.h"
#include "Logger.h"

#define TIMER_NUM 10

namespace M7engine {
class Entity {
public:
    Entity();
    virtual ~Entity();

    /**
     *  Load bitmap to use as sprite.
     *  This mainly passes to the sprite's loading functions.
     *  @param *filename The filename to load.
     */
    virtual bool loadImage(const char *filename);

    /**
     *  Load bitmap to use as sprite, specifying parameters for animation.
     *  This mainly passes to the sprite's loading functions.
     *  @param *filename The filename to load.
     *  @param width Width of an individual frame.
     *  @param height Height of an individual frame.
     *  @param columns Number of columns in base image of individual frames.
     *  @param frames Total number of animation frames.
     */
    virtual bool loadImage(const char *filename, int width, int height, int columns, int frames);

    /**
     *  Directly set a sprite as the attached sprite.
     *  @param *image Pointer to sprite to use.
     */
    virtual void setImage(Sprite* image);

    /**
     *  Reload bitmap from disk.
     */
    virtual void reloadImage();

    /**
     *  Main update function to be called per frame. Must be implemented by child.
     */
    virtual void update() {}

    /**
     *  Updates timers for ticking alarms.
     */
    void updateTimers();

    /**
     *  Function called upon collision. Must be implemented by child.
     *  @param *other Pointer to entity that was collided with.
     */
    virtual void collision(Entity *other) {}

    /**
     *  Main movement function called per frame. Adjusts position based on
     *  current vector and speed.
     */
    void move();

    /**
     *  Main drawing function called per frame.
     */
    virtual void draw();

    /**
     *  Function called in event of timer going off. Called automatically by alarm.
     *  @param timerNum The number of the timer that went off.
     */
    virtual void alarm(int timerNum) {}

    /**
     *  Returns the name of the object.
     *  @return String containing the object's name.
     */
    std::string getName() { return name; }

    /**
     *  Set the name of the particular instance.
     *  @param name String containing the new name.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  Returns the name of the object family. Secondary name for grouping objects.
     *  @return String containing the object family name.
     */
    std::string getFamily() { return family; }

    /**
     *  Set the family name of the particular instance.
     *  @param family String containing the new family name.
     */
    void setFamily(std::string family) { this->family = family; }

    /**
     *  Set entity to be solid or not.
     *  @param solid Whether to set solid or not.
     */
    void setSolid(bool solid) { this->solid = solid; }

    /**
     *  Returns whether entity is solid.
     *  @return Whether entity is solid or not.
     */
    bool getSolid() { return solid; }

    /**
     *  Returns current position in vector format.
     *  @return A vector containing positional information.
     */
    Vector2 getPosition() { return position; }

    /**
     *  Set position using a vector.
     *  @param vector Vector to set position to.
     */
    void setPosition(Vector2 vector) { this->position = vector; }

    /**
     *  Set position using X and Y integer coordinates.
     *  @param x X position to set.
     *  @param y Y position to set.
     */
    void setPosition(double x, double y) { position.set(x - xOffset, y - yOffset); }

    /**
     *  Return current X position.
     *  @return The current X position.
     */
    double getX() { return position.getX() + xOffset; }

    /**
     *  Return current Y position.
     *  @return The current Y position.
     */
    double getY() { return position.getY() + yOffset; }

    /**
     *  Set the current X coordinate.
     *  @param x X position to set.
     */
    void setX(double x) { position.setX(x - xOffset); }

    /**
     *  Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(double y) { position.setY(y - yOffset); }

    /**
     *  Return current X offset.
     *  @return The current X offset.
     */
    int getXOffset() { return xOffset; }

    /**
     *  Return current Y offset.
     *  @return The current Y offset.
     */
    int getYOffset() { return yOffset; }

    /**
     *  Manually set the entity ID.
     *  @param id Int to set id to.
     */
    void setID(int id) { this->id = id; }

    /**
     *  Returns current entity ID.
     *  @return The current ID.
     */
    int getID() { return id; }

    /**
     *  Returns whether entity is visible.
     *  @return Bool specifying visibility.
     */
    bool getVisible() { return visible; }

    /**
     *  Set whether entity is visible or not.
     *  @param visible Bool specifying visibility.
     */
    void setVisible(bool visible) { this->visible = visible; }

    /**
     *  Returns whether entity is active or not.
     *  @return Bool specifiying if active.
     */
    bool getActive() { return active; }

    /**
     *  Retrieve an int value from a loaded configuration file.
     *  @param active Bool specifying if active.
     */
    void setActive(bool active) { this->active = active; }

    int getDepth() { return depth; }

    void setDepth(int depth) { this->depth = depth; }

    /**
     *  Return current velocity in vector format.
     *  @return Vector containing current velocity.
     */
    Vector2 getVelocity(){ return velocity; }

    /**
     *  Set current velocity using a vector.
     *  @param v Vector containing velocity information.
     */
    void setVelocity(Vector2 v){ this->velocity = v; }

    /**
     *  Set current velocity manually using X and Y coordinates.
     *  @param x X coordinate to set velocity to.
     *  @param y Y coordinate to set velocity to.
     */
    void setVelocity(double x, double y){ velocity.setX(x); velocity.setY(y); }

    /**
     *  Set size by specifying width and height.
     *  @param width Width to set.
     *  @param height Height to set.
     */
    void setSize(int width, int height) { this->width = width; this->height = height; }

    /**
     *  Set size automatically using sprite dimensions.
     */
    void setSizeToImageScale() { this->width = scale * image->getWidth(); this->height = scale * image->getHeight(); }

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
     *  Set the object origin to the center of the entity in respect to current width and height.
     */
    void setOriginToCenter() { xOffset = width/2; yOffset = height/2; }

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
     *  Returns the current direction entity is facing.
     *  @return The current direction.
     */
    int getDirection() { return direction; }

    /**
     *  Set the direction entity is to face.
     *  @param direction Int to set direction to.
     */
    void setDirection(int direction) { this->direction = direction; }

    /**
     *  Returns a pointer to the attached sprite.
     *  @return A pointer to the attached sprite.
     */
    Sprite* getSprite(){ return image; }

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
    void setColor(Uint8 r, Uint8 g, Uint8 b) { color.r = r; color.g = g; color.b = b; }

    /**
     *  Set the alpha. Accepts values from 0 - 255.
     *  @param a The alpha value.
     */
    void setAlpha(Uint8 a) { color.a = a; }

    /**
     *  Sets the main properties from file using a configuration reader. Sets variables not found back to defaults.
     *  @param *reader The ConfigReader to request information from.
     *  @param name String containing name of object properties to request.
     *  @return Whether the request was successful or not. Mainly if the named section could be found.
     */
    bool setProperties(ConfigReader *reader, std::string name);

protected:
    int id, depth, width, height, xOffset, yOffset, direction, hSpeed, vSpeed;
    double scale;
    bool visible, active, solid;
    int timer[TIMER_NUM];
    Vector2 position, velocity;
    SDL_Color color;
    Sprite* image;
    std::string resourceName, name, family;
};
};

#endif
