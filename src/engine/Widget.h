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
     *  @brief Set the color of the text displayed in the widget.
     *  @param r The red component.
     *  @param g The green component.
     *  @param b The blue component.
     *  @param a The alpha component.
     */
    void setTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {textColor.r = r; textColor.g = g; textColor.b = b; textColor.a = a;}

    /**
     *  @brief Set the color of the body of the widget.
     *  @param r The red component.
     *  @param g The green component.
     *  @param b The blue component.
     *  @param a The alpha component.
     */
    void setBodyColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {bodyColor.r = r; bodyColor.g = g; bodyColor.b = b; bodyColor.a = a;}

    Font* getFont() { return this->font; }

protected:
    int x, y, xOffset, yOffset, width, height, depth, id;

    std::string name, text;

    SDL_Color textColor, bodyColor;

    Font *font;

    Window *parent;
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
    bool useImage, drawBorder, drawBody;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter,
              *image;
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
    bool useImage;

    int state;

    Sprite  *spriteTopLeft[2], *spriteTopRight[2], *spriteBottomLeft[2], *spriteBottomRight[2],
             *spriteTopCenter[2], *spriteBottomCenter[2], *spriteLeftCenter[2], *spriteRightCenter[2],
              *image;
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

protected:
    bool selected, drawBorder, drawBody, cursorFlash, cursorIsFlashing;

    int cursorInterval, cursorTimer, cursorPosition, cursorX, cursorY;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter;
};

class DropDownList : public Widget {
public:
    DropDownList(int x, int y, int width, int height);

    void update();

    /**
     *  @brief Main drawing function called per frame.
     */
    void draw();

    /**
     *  @brief Function called when button is clicked.
     */
    void onClick();

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
     *  @brief Returns the current position selected in the drop down list.
     *  @return Int signifying the current position selected.
     */
    int getPosition() { return this->position; }

    /**
     *  @brief Set the selected position of the drop down list.
     *  @param position Position to set to.
     */
    void setPosition(int position) { this->position = position; text = getPositionText(); }

    /**
     *  @brief Get the text of the currently selected position.
     *  @return String containing the text of the currently selected position.
     */
    std::string getPositionText() { return this->positions[position]; }

    /**
     *  @brief Add an item to the list of positions in the drop down list.
     *  @param The text of the item to add.
     */
    void addItem(std::string text) { positions.push_back(text); }

protected:
    std::vector<std::string> positions;

    bool drawBorder, drawBody, isOpen;

    int position, spacing;

    SDL_Color selectedColor;

    Sprite  *spriteTopLeft, *spriteTopRight, *spriteBottomLeft, *spriteBottomRight,
             *spriteTopCenter, *spriteBottomCenter, *spriteLeftCenter, *spriteRightCenter;

};
}

#endif
