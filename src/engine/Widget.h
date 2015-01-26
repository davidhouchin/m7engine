/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Widget
 *  Widget.h
 *  Purpose: Class for in-game GUI elements.
 *  @author David Houchin
 *  @version 1.0 8/5/14
 */

#ifndef WIDGET_H
#define	WIDGET_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "Sprite.h"
#include "ConfigReader.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Logger.h"

namespace M7engine {
class Window;
class Widget {
public:
    Widget();
    virtual ~Widget();

    /**
     *  @brief Main drawing function called per frame.
     */
    virtual void draw() = 0;

    /**
     *  @brief Main update function called per frame. Implemented by child classes.
     */
    virtual void update() {}

    /**
     *  @brief Manually set the widget ID.
     *  @param id Int to set id to.
     */
    void setID(int id) { this->id = id; }

    /**
     *  @brief Returns current widget ID.
     *  @return The current ID.
     */
    int getID() { return id; }

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
    void setX(int x) { this->x = x; }

    /**
     *  @brief Set the current Y position.
     *  @param y Y position to set.
     */
    void setY(int y) { this->y = y; }

    /**
     *  @brief Return current X position.
     *  @return The current X position.
     */
    int getXOffset() { return xOffset; }

    /**
     *  @brief Return current Y position.
     *  @return The current Y position.
     */
    int getYOffset() { return yOffset; }

    /**
     *  @brief Set the current X coordinate.
     *  @param x X position to set.
     */
    void setXOffset(int xOffset) { this->xOffset = xOffset; }

    /**
     *  @brief Set the current Y position.
     *  @param y Y position to set.
     */
    void setYOffset(int yOffset) { this->yOffset = yOffset; }

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
     *  @brief Returns the parent window the widget is contained in.
     *  @return Pointer to parent window, or NULL if currently none.
     */
    Window* getParent() { return this->parent; }

    /**
     *  @brief Set the parent window for the widget to be contained in.
     *  @param window Pointer to window to set parent as.
     */
    void setParent(Window* window) { this->parent = window; }

    /**
     *  @brief Set the name of the widget. Used currently for passing information to parent window.
     *  @param name The name to use.
     */
    void setName(std::string name) { this->name = name; }

    /**
     *  @brief Returns the current name of the widget.
     *  @return String containing the widget name.
     */
    std::string getName() { return this->name; }

protected:
    int x, y, xOffset, yOffset, width, height, depth, id;

    std::string name;

    Window* parent;
};

class Label : public Widget {
public:
    Label(int x, int y, int width, int height);

    /**
     *  @brief Main drawing function called per frame.
     */
    void draw();

    /**
     *  @brief Set whether to draw the borders around the bounds of the label.
     *  @param useBorder Whether to draw a border or not.
     */
    void setBorder(bool useBorder) { drawBorder = useBorder; }

    /**
     *  @brief Set whether to draw a body for the widget.
     *  @param useBody Whether to draw a body or not.
     */
    void setBody(bool useBody) { drawBody = useBody; }

    /**
     *  @brief Set the text to display in the label.
     *  @param text The text to display.
     */
    void setText(std::string text) { this->text = text; }

    /**
     *  @brief Returns the text currently set to display in the label.
     *  @return String containing current text to display.
     */
    std::string getText() { return this->text; }

    /**
     * @brief Set the color of the text displayed in the label.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    void setTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {textColor.r = r; textColor.g = g; textColor.b = b; textColor.a = a;}

    /**
     *  @brief Set the image to display in place of text. Will cause the widget to use the image by default.
     *  @param image Pointer to sprite to use for image.
     */
    void setImage(Sprite* image) { useImage = true; this->image = image; }

    /**
     *  @brief Set whether to use an image or display text.
     *  @param useImage Whether to use the image or not.
     */
    void setUseImage(bool useImage) { this->useImage = useImage; }

protected:
    std::string text;

    bool useImage, drawBorder, drawBody;

    SDL_Color bodyColor, textColor;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter,
              *image;
    Font* font;
};

class Button : public Widget {
public:
    Button(int x, int y, int width, int height);

    /**
     *  @brief Main update function called per frame.
     */
    void update();

    /**
     *  @brief main drawing function called per frame.
     */
    void draw();

    /**
     *  @brief Function called when button is clicked.
     */
    void onClick();

    /**
     *  @brief Set the text to display in the label.
     *  @param text The text to display.
     */
    void setText(std::string text) { this->text = text; }

    /**
     *  @brief Returns the text currently set to display in the label.
     *  @return String containing current text to display.
     */
    std::string getText() { return this->text; }

    /**
     * @brief Set the color of the text displayed in the label.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    void setTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {textColor.r = r; textColor.g = g; textColor.b = b; textColor.a = a;}

    /**
     *  @brief Set the image to display in place of text. Will cause the widget to use the image by default.
     *  @param image Pointer to sprite to use for image.
     */
    void setImage(Sprite* image) { useImage = true; this->image = image; }

    /**
     *  @brief Set whether to use an image or display text.
     *  @param useImage Whether to use the image or not.
     */
    void setUseImage(bool useImage) { this->useImage = useImage; }

protected:
    std::string text;

    bool useImage;

    int state;

    SDL_Color bodyColor, textColor;

    Sprite  *spriteTopLeft[2], *spriteTopRight[2], *spriteBottomLeft[2], *spriteBottomRight[2],
             *spriteTopCenter[2], *spriteBottomCenter[2], *spriteLeftCenter[2], *spriteRightCenter[2],
              *image;

    Font* font;
};

class TextBox : public Widget {
public:
    TextBox(int x, int y, int width, int height);

    void update();

    /**
     *  @brief Main drawing function called per frame.
     */
    void draw();

    /**
     *  @brief Set whether to draw the borders around the bounds of the label.
     *  @param useBorder Whether to draw a border or not.
     */
    void setBorder(bool useBorder) { drawBorder = useBorder; }

    /**
     *  @brief Set whether to draw a body for the widget.
     *  @param useBody Whether to draw a body or not.
     */
    void setBody(bool useBody) { drawBody = useBody; }

    /**
     *  @brief Set the text to display in the label.
     *  @param text The text to display.
     */
    void setText(std::string text) { this->text = text; }

    /**
     * @brief Set the color of the text displayed in the label.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    void setTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {textColor.r = r; textColor.g = g; textColor.b = b; textColor.a = a;}

    /**
     *  @brief Returns the text currently set to display in the label.
     *  @return String containing current text to display.
     */
    std::string getText() { return this->text; }

protected:
    std::string text;

    bool selected, drawBorder, drawBody, cursorFlash, cursorIsFlashing;

    int cursorInterval, cursorTimer, cursorPosition, cursorX, cursorY;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter;

    SDL_Color bodyColor, textColor;

    Font* font;
};

}

#endif
