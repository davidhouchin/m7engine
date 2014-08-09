/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Window
 *  Window.h
 *  Purpose: Class for in-game window elements and window manager.
 *  @author David Houchin
 *  @version 1.0 8/6/14
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h>

#include "Sprite.h"
#include "ConfigReader.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Logger.h"
#include "Widget.h"

namespace M7engine {
class Window {
public:
    Window();
    virtual ~Window();

    /**
     *  Main drawing function called per frame.
     */
    void draw();

    void update();

    void addWidget(Widget* widget);

    /**
     *  Manually set the window ID.
     *  @param id Int to set id to.
     */
    void setID(int id) { this->id = id; }

    /**
     *  Returns current window ID.
     *  @return The current ID.
     */
    int getID() { return id; }

    void setTitle(std::string text) { title = text; }
    std::string getTitle() { return title; }

    /**
     *  Return current X position.
     *  @return The current X position.
     */
    int getX() { return x; }

    /**
     *  Return current Y position.
     *  @return The current Y position.
     */
    int getY() { return y; }

    /**
     *  Set the current X coordinate.
     *  @param x X position to set.
     */
    void setX(int x) { this->x = x; }

    /**
     *  Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(int y) { this->y = y; }

    /**
     *  Returns width of widget.
     *  @return The current width.
     */
    int getWidth() { return this->width; }

    /**
     *  Set width of widget.
     *  @param width Int to set width to.
     */
    void setWidth(int width) { this->width = width; }

    /**
     *  Returns height of widget.
     *  @return The current height.
     */
    int getHeight() { return this->height; }

    /**
     *  Set height of widget.
     *  @param height Int to set height to.
     */
    void setHeight(int height) { this->height = height; }


    /**
     *  Return the current drawing depth.
     *  @return The current drawing depth.
     */
    int getDepth() { return depth; }

    /**
     *  Sets the drawing depth. This sets the order in which this tile is drawn. Lower numbers are drawn over higher numbers.
     *  @param depth The drawing depth to set this tile to.
     */
    void setDepth(int depth) { this->depth = depth; }

private:
    int x, y, xOffset, yOffset, width, height, titleHeight, depth, id, idCount;

    bool active, isMoving;

    std::vector<Widget*> children;

    Font* font;

    std::string title;

    SDL_Color textColor, bodyColor, titleActiveColor, titleInactiveColor;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter;
};

class WindowManager {
public:
    virtual ~WindowManager();
    static WindowManager* getInstance();

    void update();

    void addWindow(Window* window);

    bool loadConfig(std::string filename);

    ConfigReader* getConfig() { return this->config; }

private:
    WindowManager();
    static WindowManager* wmInstance;

    std::vector<Window*> windows;

    ConfigReader* config;
};
}
#endif
