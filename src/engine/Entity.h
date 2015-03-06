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
     *  @brief Load bitmap to use as sprite.
     *  This mainly passes to the sprite's loading functions.
     *  @param *filename The filename to load.
     */
    virtual bool loadImage(const char *filename);

    /**
     *  @brief Load bitmap to use as sprite, specifying parameters for animation.
     *  This mainly passes to the sprite's loading functions.
     *  @param *filename The filename to load.
     *  @param width Width of an individual frame.
     *  @param height Height of an individual frame.
     *  @param columns Number of columns in base image of individual frames.
     *  @param frames Total number of animation frames.
     */
    virtual bool loadImage(const char *filename, int width, int height, int columns, int frames);

    /**
     *  @brief Directly set a sprite as the attached sprite.
     *  @param *image Pointer to sprite to use.
     */
    virtual void setImage(Sprite* image);

    /**
     *  @brief Reload bitmap from disk.
     */
    virtual void reloadImage();

    /**
     *  @brief Main update function to be called per frame. Must be implemented by child.
     */
    virtual void update() {}

    /**
     *  @brief Updates timers for ticking alarms.
     */
    void updateTimers();

    /**
     *  @brief Function called upon collision. Must be implemented by child.
     *  @param *other Pointer to entity that was collided with.
     */
    virtual void collision(Entity*) {}

    /**
     *  @brief Main movement function called per frame. Adjusts position based on
     *  current vector and speed.
     */
    void move();

    /**
     *  @brief Main drawing function called per frame.
     */
    virtual void draw();

    /**
     *  @brief Function called in event of timer going off. Called automatically by alarm.
     *  @param timerNum The number of the timer that went off.
     */
    virtual void alarm(int) {}

    /**
     *  @brief Returns the name of the object.
     *  @return String containing the object's name.
     */
    std::string getName() { return name; }

    /**
     *  @brief Set the name of the particular instance.
     *  @param name String containing the new name.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  @brief Returns the name of the object family. Secondary name for grouping objects.
     *  @return String containing the object family name.
     */
    std::string getFamily() { return family; }

    /**
     *  @brief Set the family name of the particular instance.
     *  @param family String containing the new family name.
     */
    void setFamily(std::string family) { this->family = family; }

    /**
     *  @brief Set entity to be solid or not.
     *  @param solid Whether to set solid or not.
     */
    void setSolid(bool solid) { this->solid = solid; }

    /**
     *  @brief Returns whether entity is solid.
     *  @return Whether entity is solid or not.
     */
    bool getSolid() { return solid; }

    /**
     *  @brief Returns current position in vector format.
     *  @return A vector containing positional information.
     */
    Vector2 getPosition() { return position; }

    /**
     *  @brief Set position using a vector.
     *  @param vector Vector to set position to.
     */
    void setPosition(Vector2 vector) { this->position = vector; }

    /**
     *  @brief Set position using X and Y integer coordinates.
     *  @param x X position to set.
     *  @param y Y position to set.
     */
    void setPosition(double x, double y) { position.set(x - xOffset, y - yOffset); }

    /**
     *  @brief Return current X position.
     *  @return The current X position.
     */
    double getX() { return position.getX() + xOffset; }

    /**
     *  @brief Return current Y position.
     *  @return The current Y position.
     */
    double getY() { return position.getY() + yOffset; }

    /**
     *  @brief Set the current X coordinate.
     *  @param x X position to set.
     */
    void setX(double x) { position.setX(x - xOffset); }

    /**
     *  @brief Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(double y) { position.setY(y - yOffset); }

    /**
     *  @brief Return current X offset.
     *  @return The current X offset.
     */
    int getXOffset() { return xOffset; }

    /**
     *  @brief Return current Y offset.
     *  @return The current Y offset.
     */
    int getYOffset() { return yOffset; }

    /**
     *  @brief Set the bounding box using the dimensions of a rect.
     *  @param bbox A SDL_Rect to use as the new bounding box.
     */
    void setBBox(SDL_Rect bbox) {
        this->bbox.x = bbox.x;
        this->bbox.y = bbox.y;
        this->bbox.w = bbox.w;
        this->bbox.h = bbox.h;
    }

    /**
     *  @brief Return the X offset of the bounding box from the entity's top left corner.
     *  @return The current X offset.
     */
    int getBBoxXOffset() { return xBBox; }

    /**
     *  @brief Return the Y offset of the bounding box from the entity's top left corner.
     *  @return The current Y offset.
     */
    int getBBoxYOffset() { return yBBox; }

    /**
     *  @brief Return the in-world X position of the bounding box.
     *  @return The bounding box's X position.
     */
    int getXBBox() { return bbox.x; }

    /**
     *  @brief Return the in-world Y position of the bounding box.
     *  @return The bounding box's Y position.
     */
    int getYBBox() { return bbox.y; }

    /**
     *  @brief Return the width of the bounding box.
     *  @return The bounding box's width.
     */
    int getWBBox() { return bbox.w; }

    /**
     *  @brief Return the height of the bounding box.
     *  @return The bounding box's height.
     */
    int getHBBox() { return bbox.h; }

    /**
     *  @brief Return the bounding box as a whole rect.
     *  @return The bounding box itself.
     */
    SDL_Rect getBBox() { return bbox; }

    /**
     *  @brief Manually set the entity ID.
     *  @param id Int to set id to.
     */
    void setID(int id) { this->id = id; }

    /**
     *  @brief Returns current entity ID.
     *  @return The current ID.
     */
    int getID() { return id; }

    /**
     *  @brief Returns whether entity is visible.
     *  @return Bool specifying visibility.
     */
    bool getVisible() { return visible; }

    /**
     *  @brief Set whether entity is visible or not.
     *  @param visible Bool specifying visibility.
     */
    void setVisible(bool visible) { this->visible = visible; }

    /**
     *  @brief Returns whether entity is active or not.
     *  @return Bool specifiying if active.
     */
    bool getActive() { return active; }

    /**
     *  @brief Retrieve an int value from a loaded configuration file.
     *  @param active Bool specifying if active.
     */
    void setActive(bool active) { this->active = active; }

    /**
     *  @brief Return the current drawing depth.
     *  @return The current drawing depth.
     */
    int getDepth() { return depth; }

    /**
     *  @brief Sets the drawing depth. This sets the order in which this object is drawn. Lower numbers are drawn over higher numbers.
     *  @param depth The drawing depth to set this object to.
     */
    void setDepth(int depth) { this->depth = depth; }

    /**
     *  @brief Return current velocity in vector format.
     *  @return Vector containing current velocity.
     */
    Vector2 getVelocity(){ return velocity; }

    /**
     *  @brief Set current velocity using a vector.
     *  @param v Vector containing velocity information.
     */
    void setVelocity(Vector2 v){ this->velocity = v; }

    /**
     *  @brief Set current velocity manually using X and Y coordinates.
     *  @param x X coordinate to set velocity to.
     *  @param y Y coordinate to set velocity to.
     */
    void setVelocity(double x, double y){ velocity.setX(x); velocity.setY(y); }

    /**
     *  @brief Set size by specifying width and height.
     *  @param width Width to set.
     *  @param height Height to set.
     */
    void setSize(int width, int height) { this->width = width; this->height = height; }

    /**
     *  @brief Set size automatically using sprite dimensions.
     */
    void setSizeToImageScale() { this->width = scale * image->getWidth(); this->height = scale * image->getHeight(); }

    /**
     *  @brief Returns width of entity.
     *  @return The current width.
     */
    int getWidth() { return this->width; }

    /**
     *  @brief Set width of entity.
     *  @param width Int to set width to.
     */
    void setWidth(int width) { this->width = width; }

    /**
     *  @brief Returns height of entity.
     *  @return The current height.
     */
    int getHeight() { return this->height; }

    /**
     *  @brief Set height of entity.
     *  @param height Int to set height to.
     */
    void setHeight(int height) { this->height = height; }

    /**
     *  @brief Set the object origin to the center of the entity in respect to current width and height.
     */
    void setOriginToCenter() { xOffset = width/2; yOffset = height/2; }

    /**
     *  @brief Sets the object origin to the center of the entity in respect to the center of the current sprite.
     */
    void setOriginToImageCenter() { xOffset = image->getWidth()/2; yOffset = image->getHeight()/2; }

    /**
     *  @brief Returns image scale of entity.
     *  @return The current image scale.
     */
    double getScale() { return scale; }

    /**
     *  @brief Set the image scale of the entity.
     *  @param scale Int to set scale to.
     */
    void setScale(double scale) { this->scale = scale; }

    /**
     *  @brief Returns the current direction entity is facing.
     *  @return The current direction.
     */
    int getDirection() { return direction; }

    /**
     *  @brief Set the direction entity is to face.
     *  @param direction Int to set direction to.
     */
    void setDirection(int direction) { this->direction = direction; }

    /**
     *  @brief Returns a pointer to the attached sprite.
     *  @return A pointer to the attached sprite.
     */
    Sprite* getSprite(){ return image; }

    /**
     *  @brief Returns the current color as a SDL_Color.
     *  @return The current SDL_Color.
     */
    SDL_Color getColor() { return color; }

    /**
     *  @brief Set color using RGB values. Accepts values from 0 - 255.
     *  @param r The red value.
     *  @param g The green value.
     *  @param b The blue value.
     */
    void setColor(Uint8 r, Uint8 g, Uint8 b) { color.r = r; color.g = g; color.b = b; }

    /**
     *  @brief Set the alpha. Accepts values from 0 - 255.
     *  @param a The alpha value.
     */
    void setAlpha(Uint8 a) { color.a = a; }

    /**
     *  @brief Sets the main properties from file using a configuration reader. Sets variables not found back to defaults.
     *  @param *reader The ConfigReader to request information from.
     *  @param name String containing name of object properties to request.
     *  @return Whether the request was successful or not. Mainly if the named section could be found.
     */
    virtual bool setProperties(ConfigReader *reader, std::string name);

    /**
     *  @brief Sets the specified timer to the specified time.
     *  @param timer The timer number to adjust.
     *  @param time The time to set the timer to.
     */
    void setTimer(int timer, int time) { this->timer[timer] = time; }

    bool killMe = false;

protected:
    int id, depth, width, height, xOffset, yOffset, direction, hSpeed, vSpeed, xBBox, yBBox;
    double scale;
    bool visible, active, solid;
    int timer[TIMER_NUM];
    Vector2 position, velocity;
    SDL_Rect bbox;
    SDL_Color color;
    Sprite* image;
    std::string resourceName, name, family;
};

//Minimal entity class for drawing background objects that don't need much processing.
class Tile {
public:
    Tile();
    virtual ~Tile();

    /**
     *  @brief Directly set a sprite as the attached sprite.
     *  @param *image Pointer to sprite to use.
     */
    virtual void setImage(Sprite* image);

    /**
     *  @brief Main drawing function called per frame.
     */
    virtual void draw();

    /**
     *  @brief Returns the name of the object.
     *  @return String containing the object's name.
     */
    std::string getName() { return name; }

    /**
     *  @brief Set the name of the particular instance.
     *  @param name String containing the new name.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  @brief Returns current position in vector format.
     *  @return A vector containing positional information.
     */
    Vector2 getPosition() { return position; }

    /**
     *  @brief Set position using a vector.
     *  @param vector Vector to set position to.
     */
    void setPosition(Vector2 vector) { this->position = vector; }

    /**
     *  @brief Set position using X and Y integer coordinates.
     *  @param x X position to set.
     *  @param y Y position to set.
     */
    void setPosition(double x, double y) { position.set(x, y); }

    /**
     *  @brief Return current X position.
     *  @return The current X position.
     */
    double getX() { return position.getX(); }

    /**
     *  @brief Return current Y position.
     *  @return The current Y position.
     */
    double getY() { return position.getY(); }

    /**
     *  @brief Set the current X coordinate.
     *  @param x X position to set.
     */
    void setX(double x) { position.setX(x); }

    /**
     *  @brief Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(double y) { position.setY(y); }

    /**
     *  @brief Return the current drawing depth.
     *  @return The current drawing depth.
     */
    int getDepth() { return depth; }

    /**
     *  @brief Sets the drawing depth. This sets the order in which this tile is drawn. Lower numbers are drawn over higher numbers.
     *  @param depth The drawing depth to set this tile to.
     */
    void setDepth(int depth) { this->depth = depth; }

    /**
     *  @brief Sets the main properties from file using a configuration reader. Sets variables not found back to defaults.
     *  @param *reader The ConfigReader to request information from.
     *  @param name String containing name of object properties to request.
     *  @return Whether the request was successful or not. Mainly if the named section could be found.
     */
    bool setProperties(ConfigReader *reader, std::string name);

protected:
    int depth;
    Sprite* image;
    Vector2 position;
    std::string resourceName, name;
};
};

#endif
