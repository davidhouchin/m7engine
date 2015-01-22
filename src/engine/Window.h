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
    Window(int x, int y, int width, int height);
    virtual ~Window();

    /**
     *  Main drawing function called per frame.
     */
    void draw();

    /**
     *  Main update function called per frame.
     */
    void update();

    /**
     *  Function to handle the input when a widget is interacted with through passing the widget's name. To be implemented by user-defined windows.
     */
    virtual void handleInput(std::string name) {
        Logger::getInstance()->logMessage(1, "Window %i recieved input from widget %s", this->id, name.c_str());
    }

    /**
     *  Add a widget to the group of tracked widgets.
     *  @return The ID assigned to the widget.
     */
    int addWidget(Widget* widget);

    /**
     *  Removes a widget from the tracked widgets based on it's ID.
     *  @return Whether the requested id was found and removed or not.
     */
    bool removeWidget(int id);

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

    /**
     *  Set the window to be active or inactive.
     *  @param active Whether active or not.
     */
    void setActive(bool active) { this->active = active; }

    /**
     *  Returns whether the window is active or not.
     *  @return Whether active or not.
     */
    bool getActive() { return this->active; }

    /**
     *  Set the window to be visible or invisible.
     *  @param active Whether visible or not.
     */
    void setVisible(bool visible) { this->visible = visible; }

    /**
     *  Returns whether the window is visible or not.
     *  @return Whether visible or not.
     */
    bool getVisible() { return this->visible; }

    /**
     *  Find a widget based on it's name.
     *  @return Pointer to widget, if found. Otherwise NULL.
     */
    Widget* findWidget(std::string name);

    /**
     *  Find a widget based on it's id.
     *  @return Pointer to widget, if found. Otherwise NULL.
     */
    Widget* findWidget(int id);

    /**
     *  Set the window title using a string.
     *  @param text String specifying new title.
     */
    void setTitle(std::string text) { title = text; }

    /**
     *  Returns the current window title.
     *  @return String containing current title.
     */
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
     *  Returns the current height of the title bar.
     *  @return Current height of the title bar.
     */
    int getTitleBarHeight() { return this->titleHeight; }

    /**
     *  Set the height of the title bar. 0 means no bar displayed.
     *  @param height The new height of the title bar.
     */
    void setTitleBarHeight(int height) { titleHeight = height; }

    /**
     *  Return the current drawing depth.
     *  @return The current drawing depth.
     */
    int getDepth() { return depth; }

    /**
     *  Sets the drawing depth. This sets the order in which this window is drawn. Lower numbers are drawn over higher numbers.
     *  @param depth The drawing depth to set this tile to.
     */
    void setDepth(int depth) { this->depth = depth; }

    /**
     *  Sets whether the window is static in the viewport, following the screen around without being clicked and dragged.
     *  @param sticky Whether to keep window in a relative spot on the viewport.
     */
    void setSticky(bool sticky) { this->sticky = sticky; }

    /**
     *  Returns whether window is currently set to be sticky or not.
     *  @return Whether currently sticky.
     */
    bool getSticky() { return this->sticky; }

protected:
    int x, y, xOffset, yOffset, xMouseOffset, yMouseOffset, width, height, titleHeight, depth, id, idCount;

    bool visible, active, isMoving, sticky;

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

    /**
     *  Main update function called per frame.
     */
    void update();

    /**
     *  Add a window to the group of tracked windows.
     *  @param window Pointer to the window to be added.
     */
    void addWindow(Window* window);

    /**
     *  Loads widget definitions from a file, specifying colors, sprites, etc.
     *  @param filename Config file to load.
     *  @return Whether file was successfully loaded or not.
     */
    bool loadConfig(std::string filename);

    /**
     *  Returns a pointer to the config reader used to load the definition file. Used currently by widgets to get default style settings.
     *  @return Pointer to the config reader used by the window manager.
     */
    ConfigReader* getConfig() { return this->config; }

private:
    WindowManager();
    static WindowManager* wmInstance;

    std::vector<Window*> windows;

    ConfigReader* config;
};
}
#endif
