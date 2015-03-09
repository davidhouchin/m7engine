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
    Window();

    virtual ~Window();

    /**
     *  @brief Main drawing function called per frame.
     */
    virtual void draw();

    /**
     *  @brief Main update function called per frame.
     */
    virtual void update();

    /**
     *  @brief Function to handle the input when a widget is interacted with through passing the widget's name. To be implemented by user-defined windows.
     */
    virtual void handleInput(Widget *widget) {
        Logger::getInstance()->logMessage(1, "Window %i recieved input from widget %s", this->id, widget->getName().c_str());
    }

    /**
     *  @brief Add a widget to the group of tracked widgets.
     *  @return The ID assigned to the widget.
     */
    int addWidget(Widget* widget);

    /**
     *  @brief Removes a widget from the tracked widgets based on it's ID.
     *  @return Whether the requested id was found and removed or not.
     */
    bool removeWidget(int id);

    /**
     *  @brief Manually set the window ID.
     *  @param id Int to set id to.
     */
    void setID(int id) { this->id = id; }

    /**
     *  @brief Returns current window ID.
     *  @return The current ID.
     */
    int getID() { return id; }

    /**
     *  @brief Set the window to be active or inactive.
     *  @param active Whether active or not.
     */
    void setActive(bool active) { this->active = active; }

    /**
     *  @brief Returns whether the window is active or not.
     *  @return Whether active or not.
     */
    bool getActive() { return this->active; }

    /**
     *  @brief Set the window to be visible or invisible.
     *  @param active Whether visible or not.
     */
    void setVisible(bool visible) { this->visible = visible; }

    /**
     *  @brief Returns whether the window is visible or not.
     *  @return Whether visible or not.
     */
    bool getVisible() { return this->visible; }

    /**
     *  @brief Find a widget based on it's name.
     *  @return Pointer to widget, if found. Otherwise NULL.
     */
    Widget* findWidget(std::string name);

    /**
     *  @brief Find a widget based on it's id.
     *  @return Pointer to widget, if found. Otherwise NULL.
     */
    Widget* findWidget(int id);

    /**
     *  @brief Set the window title using a string.
     *  @param text String specifying new title.
     */
    void setTitle(std::string text) { title = text; }

    /**
     *  @brief Returns the current window title.
     *  @return String containing current title.
     */
    std::string getTitle() { return title; }

    /**
     *  @brief Return current X position.
     *  @return The current X position.
     */
    int getX() { return x; }

    /**
     *  @brief Return current Y position.
     *  @return The current Y position.
     */
    int getY() { return y; }

    /**
     *  @brief Set the current X coordinate.
     *  @param x X position to set.
     */
    void setX(int x);

    /**
     *  @brief Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(int y);

    /**
     *  @brief Returns width of widget.
     *  @return The current width.
     */
    int getWidth() { return this->width; }

    /**
     *  @brief Set width of widget.
     *  @param width Int to set width to.
     */
    void setWidth(int width) { this->width = width; }

    /**
     *  @brief Returns height of widget.
     *  @return The current height.
     */
    int getHeight() { return this->height; }

    /**
     *  @brief Set height of widget.
     *  @param height Int to set height to.
     */
    void setHeight(int height) { this->height = height; }

    /**
     *  @brief Returns the current height of the title bar.
     *  @return Current height of the title bar.
     */
    int getTitleBarHeight() { return this->titleHeight; }

    /**
     *  @brief Set the height of the title bar. 0 means no bar displayed.
     *  @param height The new height of the title bar.
     */
    void setTitleBarHeight(int height) { titleHeight = height; }

    /**
     *  @brief Return the current drawing depth.
     *  @return The current drawing depth.
     */
    int getDepth() { return depth; }

    /**
     *  @brief Sets the drawing depth. This sets the order in which this window is drawn. Lower numbers are drawn over higher numbers.
     *  @param depth The drawing depth to set this tile to.
     */
    void setDepth(int depth) { this->depth = depth; }

    /**
     *  @brief Sets whether the window is static in the viewport, following the screen around without being clicked and dragged.
     *  @param sticky Whether to keep window in a relative spot on the viewport.
     */
    void setSticky(bool sticky) { this->sticky = sticky; }

    /**
     *  @brief Returns whether window is currently set to be sticky or not.
     *  @return Whether currently sticky.
     */
    bool getSticky() { return this->sticky; }

    bool killMe = false;

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
     *  @brief Main update function called per frame.
     */
    void update();

    /**
     *  @brief Add a window to the group of tracked windows.
     *  @param window Pointer to the window to be added.
     */
    void addWindow(Window* window);

    /**
     *  @brief Destroy the window with the given window ID.
     *  @param id ID of window to destroy.
     */
    void destroyWindow(int id);

    /**
     *  @brief Loads widget definitions from a file, specifying colors, sprites, etc.
     *  @param filename Config file to load.
     *  @return Whether file was successfully loaded or not.
     */
    bool loadConfig(std::string filename);

    /**
     *  @brief Returns a pointer to the config reader used to load the definition file. Used currently by widgets to get default style settings.
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
