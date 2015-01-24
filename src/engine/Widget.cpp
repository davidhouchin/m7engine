/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Widget
 *  Widget.cpp
 *  Purpose: Class for in-game GUI elements.
 *  @author David Houchin
 *  @version 1.0 8/5/14
 */

#include "Widget.h"
#include "M7engine.h"

namespace M7engine {
Widget::Widget()
{
    x = 0;
    y = 0;
    xOffset = 0;
    yOffset = 0;
    width = 1;
    height = 1;
    depth = 0;
}

Widget::~Widget()
{
    if (parent != NULL) {
        parent->removeWidget(this->id);
    }
}

Label::Label(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    name = "";
    text = "";
    useImage = false;
    image = NULL;
    parent = NULL;

    ConfigReader* c = WindowManager::getInstance()->getConfig();

    drawBorder = c->getBool("label", "draw_border", false);
    drawBody = c->getBool("label", "draw_body", false);

    textColor = { static_cast<Uint8>(c->getInt("label", "text_r", 0)),
                  static_cast<Uint8>(c->getInt("label", "text_g", 0)),
                  static_cast<Uint8>(c->getInt("label", "text_b", 0)),
                  static_cast<Uint8>(c->getInt("label", "text_a", 255))};

    bodyColor = { static_cast<Uint8>(c->getInt("label", "body_r", 192)),
                  static_cast<Uint8>(c->getInt("label", "body_g", 192)),
                  static_cast<Uint8>(c->getInt("label", "body_b", 192)),
                  static_cast<Uint8>(c->getInt("label", "body_a", 255))};

    spriteTopLeft = ResourceManager::getInstance()->getSprite(
                c->getString("label", "topleft"));
    spriteTopRight = ResourceManager::getInstance()->getSprite(
                c->getString("label", "topright"));
    spriteBottomLeft = ResourceManager::getInstance()->getSprite(
                c->getString("label", "bottomleft"));
    spriteBottomRight = ResourceManager::getInstance()->getSprite(
                c->getString("label", "bottomright"));
    spriteTopCenter = ResourceManager::getInstance()->getSprite(
                c->getString("label", "topcenter"));
    spriteBottomCenter = ResourceManager::getInstance()->getSprite(
                c->getString("label", "bottomcenter"));
    spriteLeftCenter = ResourceManager::getInstance()->getSprite(
                c->getString("label", "leftcenter"));
    spriteRightCenter = ResourceManager::getInstance()->getSprite(
                c->getString("label", "rightcenter"));

    font = ResourceManager::getInstance()->getFont(
                c->getString("label", "font"));
}

void Label::draw()
{
    //Draw body.
    if (drawBody) {
        drawFilledRectangle(x + 1, y + 1, width-2, height-2, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    }

    //Draw borders, adjust position if clicked.
    if (drawBorder) {
        spriteTopLeft->draw(x, y);
        spriteTopRight->draw(x + (width-3), y);
        spriteBottomLeft->draw(x, y + (height-3));
        spriteBottomRight->draw(x + (width-3), y + (height-3));

        spriteTopCenter->setWidth(width - 6);
        spriteTopCenter->draw(x + 3, y);
        spriteBottomCenter->setWidth(width - 6);
        spriteBottomCenter->draw(x + 3, y + (height-3));
        spriteLeftCenter->setHeight(height - 6);
        spriteLeftCenter->draw(x, y + 3);
        spriteRightCenter->setHeight(height - 6);
        spriteRightCenter->draw(x + (width-3), y + 3);
    }

    //If not using image, draw the text, otherwise draw the image.
    if ((!useImage) && (text != "")) {
        font->setSDLColor(textColor);

        Engine::getInstance()->renderText(x + (width/2) - font->getTextWidth(text.c_str())/2,
                                          y + (height/2) - font->getTextHeight(text.c_str())/2,
                                          font, text.c_str());
    } else {
        if (image != NULL) {
            image->draw(x + (width/2) - image->getWidth()/2,
                        y + (height/2) - image->getHeight()/2);
        }
    }
}

Button::Button(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    name = "";
    text = "";
    useImage = false;
    image = NULL;
    state = 0;
    parent = NULL;

    ConfigReader* c = WindowManager::getInstance()->getConfig();

    textColor = { static_cast<Uint8>(c->getInt("button", "text_r", 0)),
                  static_cast<Uint8>(c->getInt("button", "text_g", 0)),
                  static_cast<Uint8>(c->getInt("button", "text_b", 0)),
                  static_cast<Uint8>(c->getInt("button", "text_a", 255))};

    bodyColor = { static_cast<Uint8>(c->getInt("button", "body_r", 192)),
                  static_cast<Uint8>(c->getInt("button", "body_g", 192)),
                  static_cast<Uint8>(c->getInt("button", "body_b", 192)),
                  static_cast<Uint8>(c->getInt("button", "body_a", 255))};

    spriteTopLeft[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "topleft"));
    spriteTopRight[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "topright"));
    spriteBottomLeft[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomleft"));
    spriteBottomRight[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomright"));
    spriteTopCenter[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "topcenter"));
    spriteBottomCenter[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomcenter"));
    spriteLeftCenter[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "leftcenter"));
    spriteRightCenter[0] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "rightcenter"));

    spriteTopLeft[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "topleftpressed"));
    spriteTopRight[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "toprightpressed"));
    spriteBottomLeft[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomleftpressed"));
    spriteBottomRight[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomrightpressed"));
    spriteTopCenter[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "topcenterpressed"));
    spriteBottomCenter[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "bottomcenterpressed"));
    spriteLeftCenter[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "leftcenterpressed"));
    spriteRightCenter[1] = ResourceManager::getInstance()->getSprite(
                c->getString("button", "rightcenterpressed"));

    font = ResourceManager::getInstance()->getFont(
                c->getString("button", "font"));
}

void Button::update()
{
    int mx, my, tx, ty;
    mx = InputManager::getInstance()->getMouseX();
    my = InputManager::getInstance()->getMouseY();
    tx = x - Engine::getInstance()->getViewportX();
    ty = y - Engine::getInstance()->getViewportY();

    //If user clicked inside button:
    if ((mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+height)) && InputManager::getInstance()->getMousePressed(MOUSE_LEFT)) {
        state = 1;
    }
    //If user released mouse inside button:
    else if ((mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+height)) && InputManager::getInstance()->getMouseReleased(MOUSE_LEFT)) {
        if (state == 1) {
            onClick();
        }
        state = 0;
    }
    //If user moved cursor outside button:
    else if ((mx < tx) || (mx > (tx+width)) || (my < ty) || (my > (ty+height))) {
        state = 0;
    }
}

void Button::draw()
{
    //Draw body.
    drawFilledRectangle(x + 1, y + 1, width-2, height-2, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);

    //Draw borders, adjust position if clicked.
    if (state == 0) {
        spriteTopLeft[0]->draw(x, y);
        spriteTopRight[0]->draw(x + (width-3), y);
        spriteBottomLeft[0]->draw(x, y + (height-3));
        spriteBottomRight[0]->draw(x + (width-3), y + (height-3));

        spriteTopCenter[0]->setWidth(width - 6);
        spriteTopCenter[0]->draw(x + 3, y);
        spriteBottomCenter[0]->setWidth(width - 6);
        spriteBottomCenter[0]->draw(x + 3, y + (height-3));
        spriteLeftCenter[0]->setHeight(height - 6);
        spriteLeftCenter[0]->draw(x, y + 3);
        spriteRightCenter[0]->setHeight(height - 6);
        spriteRightCenter[0]->draw(x + (width-3), y + 3);
    } else {
        spriteTopLeft[1]->draw(x, y);
        spriteTopRight[1]->draw(x + (width-3), y);
        spriteBottomLeft[1]->draw(x, y + (height-3));
        spriteBottomRight[1]->draw(x + (width-3), y + (height-3));

        spriteTopCenter[1]->setWidth(width - 6);
        spriteTopCenter[1]->draw(x + 3, y);
        spriteBottomCenter[1]->setWidth(width - 6);
        spriteBottomCenter[1]->draw(x + 3, y + (height-3));
        spriteLeftCenter[1]->setHeight(height - 6);
        spriteLeftCenter[1]->draw(x, y + 3);
        spriteRightCenter[1]->setHeight(height - 6);
        spriteRightCenter[1]->draw(x + (width-3), y + 3);
    }

    //If not using image, draw the text, otherwise draw the image.
    if ((!useImage) && (text != "")) {
        font->setSDLColor(textColor);

        if (state == 0) {
            Engine::getInstance()->renderText(x + (width/2) - font->getTextWidth(text.c_str())/2,
                                              y + (height/2) - font->getTextHeight(text.c_str())/2,
                                              font, text.c_str());
        } else {
            Engine::getInstance()->renderText(x + 1 + (width/2) - font->getTextWidth(text.c_str())/2,
                                              y + 1 + (height/2) - font->getTextHeight(text.c_str())/2,
                                              font, text.c_str());
        }
    } else {
        if (image != NULL) {
            if (state == 0) {
                image->draw(x + (width/2) - image->getWidth()/2,
                            y + (height/2) - image->getHeight()/2);
            } else {
                image->draw(x + 1 + (width/2) - image->getWidth()/2,
                            y + 1 + (height/2) - image->getHeight()/2);
            }
        }
    }
}

void Button::onClick()
{
    if (parent != NULL) {
        parent->handleInput(getName());
    }
}


TextBox::TextBox(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    selected = false;

    name = "";
    text = "";
    parent = NULL;

    ConfigReader* c = WindowManager::getInstance()->getConfig();

    drawBorder = c->getBool("textbox", "draw_border", false);
    drawBody = c->getBool("textbox", "draw_body", false);

    textColor = { static_cast<Uint8>(c->getInt("textbox", "text_r", 0)),
                  static_cast<Uint8>(c->getInt("textbox", "text_g", 0)),
                  static_cast<Uint8>(c->getInt("textbox", "text_b", 0)),
                  static_cast<Uint8>(c->getInt("textbox", "text_a", 255))};

    bodyColor = { static_cast<Uint8>(c->getInt("textbox", "body_r", 192)),
                  static_cast<Uint8>(c->getInt("textbox", "body_g", 192)),
                  static_cast<Uint8>(c->getInt("textbox", "body_b", 192)),
                  static_cast<Uint8>(c->getInt("textbox", "body_a", 255))};

    spriteTopLeft = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "topleft"));
    spriteTopRight = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "topright"));
    spriteBottomLeft = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "bottomleft"));
    spriteBottomRight = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "bottomright"));
    spriteTopCenter = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "topcenter"));
    spriteBottomCenter = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "bottomcenter"));
    spriteLeftCenter = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "leftcenter"));
    spriteRightCenter = ResourceManager::getInstance()->getSprite(
                c->getString("textbox", "rightcenter"));

    font = ResourceManager::getInstance()->getFont(
                c->getString("textbox", "font"));
}

void TextBox::update()
{
    int mx, my, tx, ty;
    mx = InputManager::getInstance()->getMouseX();
    my = InputManager::getInstance()->getMouseY();
    tx = x - Engine::getInstance()->getViewportX();
    ty = y - Engine::getInstance()->getViewportY();

    //If user clicked inside textbox:
    if ((mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+height)) && InputManager::getInstance()->getMouseReleased(MOUSE_LEFT)) {
        selected = true;
        text = "";

    }
    //If user clicked outside textbox:
    else if ((selected) && ((mx < tx) || (mx > (tx+width)) || (my < ty) || (my > (ty+height))) && InputManager::getInstance()->getMouseReleased(MOUSE_LEFT)) {
        selected = false;
        InputManager::getInstance()->eraseTextInput();
        InputManager::getInstance()->stopTextInput();
    }

    if (cursorFlash) {
        cursorTimer++;
        if (cursorTimer >= cursorInterval) {
            cursorIsFlashing = !cursorIsFlashing;
            cursorTimer = 0;
        }
    }

    if (selected) {
        InputManager::getInstance()->startTextInput();

        if (InputManager::getInstance()->getTextString() != "") {
            text = InputManager::getInstance()->getTextString();
        }
    }
}

void TextBox::draw()
{
    //Draw body.
    if ((selected) && (drawBody)) {
        drawFilledRectangle(x + 1, y + 1, width-2, height-2, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    }

    //Draw borders, adjust position if clicked.
    if (drawBorder) {
        spriteTopLeft->draw(x, y);
        spriteTopRight->draw(x + (width-3), y);
        spriteBottomLeft->draw(x, y + (height-3));
        spriteBottomRight->draw(x + (width-3), y + (height-3));

        spriteTopCenter->setWidth(width - 6);
        spriteTopCenter->draw(x + 3, y);
        spriteBottomCenter->setWidth(width - 6);
        spriteBottomCenter->draw(x + 3, y + (height-3));
        spriteLeftCenter->setHeight(height - 6);
        spriteLeftCenter->draw(x, y + 3);
        spriteRightCenter->setHeight(height - 6);
        spriteRightCenter->draw(x + (width-3), y + 3);
    }

    //Draw the text
    if (text != "") {
        font->setSDLColor(textColor);

        Engine::getInstance()->renderText(x + (width/2) - font->getTextWidth(text.c_str())/2,
                                          y + (height/2) - font->getTextHeight(text.c_str())/2,
                                          font, text.c_str());
    }
}
}
