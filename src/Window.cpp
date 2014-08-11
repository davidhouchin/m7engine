/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Window
 *  Window.cpp
 *  Purpose: Class for in-game window elements and window manager.
 *  @author David Houchin
 *  @version 1.0 8/6/14
 */

#include "Window.h"
#include "M7engine.h"

namespace M7engine {
WindowManager* WindowManager::wmInstance = NULL;

WindowManager* WindowManager::getInstance()
{
    if (!wmInstance) {
        wmInstance = new WindowManager;
    }

    return wmInstance;
}

WindowManager::WindowManager()
{
    config = new ConfigReader();
}

WindowManager::~WindowManager()
{
}

bool WindowManager::loadConfig(std::string filename){
    Logger::getInstance()->logMessage(0, "WindowManager loading config file: '%s'", filename.c_str());

    if (!config->loadConfig(filename.c_str())) {
        Logger::getInstance()->logError(0, "WindowManager failed to load config file: '%s'", filename.c_str());
        return false;
    } else {
        return true;
    }
}

void WindowManager::update()
{
    std::vector<Window*>::iterator iter;
    Window *window;
    iter = windows.begin();
    while (iter != windows.end()) {
        window = *iter;
        window->update();
        window->draw();
        iter++;
    }
}

void WindowManager::addWindow(Window *window)
{
    static int id = 0;
    window->setID(id);
    windows.push_back(window);
    Logger::getInstance()->logMessage(1, "WM added window id: %i", id);
    id++;
}

Window::Window(int x, int y, int width, int height)
{
    active             = true;
    isMoving           = false;
    id                 = -1;
    this->x            = x;
    this->y            = y;
    xOffset            = 0;
    yOffset            = 0;
    xStartOffset       = x - Engine::getInstance()->getViewportX();
    yStartOffset       = y - Engine::getInstance()->getViewportY();
    this->width        = width;
    this->height       = height;
    depth              = 0;
    title              = "";

    ConfigReader* c    = WindowManager::getInstance()->getConfig();

    titleHeight        = c->getInt("window", "title_height", 16);

    textColor          = { static_cast<Uint8>(c->getInt("window", "text_r", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_g", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_b", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_a", 255))};

    bodyColor          = { static_cast<Uint8>(c->getInt("window", "body_r", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_g", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_b", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_a", 255))};

    titleActiveColor   = { static_cast<Uint8>(c->getInt("window", "title_r", 255)),
                           static_cast<Uint8>(c->getInt("window", "title_g", 0)),
                           static_cast<Uint8>(c->getInt("window", "title_b", 0)),
                           static_cast<Uint8>(c->getInt("window", "title_a", 255))};

    titleInactiveColor = { static_cast<Uint8>(c->getInt("window", "title_inactive_r", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_g", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_b", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_a", 255))};

    spriteTopLeft      = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topleft"));
    spriteTopRight     = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topright"));
    spriteBottomLeft   = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomleft"));
    spriteBottomRight  = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomright"));
    spriteTopCenter    = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topcenter"));
    spriteBottomCenter = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomcenter"));
    spriteLeftCenter   = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "leftcenter"));
    spriteRightCenter  = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "rightcenter"));

    font               = ResourceManager::getInstance()->getFont(
                         c->getString("window", "font"));
}

Window::~Window()
{
}

void Window::update()
{
    int mx, my, tx, ty, vx, vy;
    mx = InputManager::getInstance()->getMouseX();
    my = InputManager::getInstance()->getMouseY();
    vx = Engine::getInstance()->getViewportX();
    vy = Engine::getInstance()->getViewportY();
    tx = x - vx;
    ty = y - vy;

    //If user clicked inside title:
    if ((!sticky) && (mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+titleHeight+2)) && InputManager::getInstance()->getMousePressed(MOUSE_LEFT)) {
        isMoving = true;
        xOffset = mx - tx;
        yOffset = my - ty;
    }
    else if (InputManager::getInstance()->getMouseReleased(MOUSE_LEFT)) {
        isMoving = false;
    }

    if (isMoving) {
        x = mx - xOffset + vx;
        y = my - yOffset + vy;
    }

    if (sticky) {
        setX(vx + xStartOffset);
        setY(vy + yStartOffset);
    }

    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;

        widget->setX(this->x + widget->getXOffset());
        widget->setY(this->y + widget->getYOffset());

        widget->update();
        iter++;
    }
}

void Window::draw()
{
    //Draw body.
    drawFilledRectangle(x + 1, y + 1, width-2, height-2, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);

    //Draw borders, adjust position if clicked.
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

    //Draw title bar.
    if (active) {
        drawFilledRectangle(x + 1, y + 1, width-2, titleHeight, titleActiveColor.r, titleActiveColor.g, titleActiveColor.b, titleActiveColor.a);
    } else {
        drawFilledRectangle(x + 1, y + 1, width-2, titleHeight, titleInactiveColor.r, titleInactiveColor.g, titleInactiveColor.b, titleInactiveColor.a);
    }

    //Draw title text.
    if ((title != "") && (titleHeight != 0)) {
        font->setSDLColor(textColor);

        Engine::getInstance()->renderText(x + (width/2) - font->getTextWidth(title.c_str())/2,
                                          y + (titleHeight/2) - font->getTextHeight(title.c_str())/2,
                                          font, title.c_str());
    }

    //Draw child widgets
    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;
        widget->draw();
        iter++;
    }
}

int Window::addWidget(Widget *widget)
{
    int newId = idCount;
    widget->setID(newId);
    widget->setParent(this);
    widget->setXOffset(widget->getX() - this->x);
    widget->setYOffset(widget->getY() - this->y);
    children.push_back(widget);
    Logger::getInstance()->logMessage(1, "Window %i added widget id: %i", id, idCount);
    idCount++;
    return idCount-1;
}

bool Window::removeWidget(int id)
{
    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;
        if (widget->getID() == id) {
            children.erase(iter);
            return true;
        } else {
            iter++;
        }
    }

    return false;
}

Widget* Window::findWidget(std::string name)
{
    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;
        if (widget->getName() == name) {
            return widget;
        } else {
            iter++;
        }
    }

    return NULL;
}

Widget* Window::findWidget(int id)
{
    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;
        if (widget->getID() == id) {
            return widget;
        } else {
            iter++;
        }
    }

    return NULL;
}
}
