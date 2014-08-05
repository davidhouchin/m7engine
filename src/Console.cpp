/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Console
 *  Console.cpp
 *  Purpose: Debug console for viewing information and setting parameters in-game.
 *  @author David Houchin
 *  @version 1.0 8/4/14
 */

#include "Console.h"
#include "M7engine.h"

namespace M7engine {
Console* Console::consoleInstance = NULL;

Console* Console::getInstance()
{
    if (!consoleInstance) {
        consoleInstance = new Console;
    }

    return consoleInstance;
}

Console::Console()
{
    isOpen = false;

    text = "";
    prompt = "$ ";

    defaultColor = { 255, 155, 85, 255};

    for (int i = 0; i < LINE_NUM; ++i) {
        lines[i] = " ";
        lineColors[i] = defaultColor;
    }
}

Console::~Console()
{
}

void Console::parse(std::string text)
{
    std::string lineToAdd = "Unrecognized Command: " + text;
    SDL_Color colorToAdd = { 255, 50, 50, 255};
    addLine(lineToAdd, colorToAdd);
}

void Console::addLine(std::string text, SDL_Color color)
{
    for (int i = LINE_NUM-1; i > 0; --i) {
        lines[i] = lines[i-1];
        lineColors[i] = lineColors[i-1];
    }

    lines[0] = text;
    lineColors[0] = color;
}

void Console::update()
{
    if (InputManager::getInstance()->getKeyReleased(KEY_TAB)) {
        isOpen = !isOpen;
        text = "";
        InputManager::getInstance()->eraseTextInput();
    }

    if (isOpen) {
        InputManager::getInstance()->startTextInput();

        if (InputManager::getInstance()->getTextString() != "") {
            text = InputManager::getInstance()->getTextString();
        } else {
            text = "";
        }

        if (InputManager::getInstance()->getKeyReleased(KEY_RETURN) && (text != "")) {
            for (int i = LINE_NUM-1; i > 0; --i) {
                lines[i] = lines[i-1];
                lineColors[i] = lineColors[i-1];
            }

            lines[0] = text;

            parse(text);

            InputManager::getInstance()->eraseTextInput();
            text = "";
        }
    } else {
        InputManager::getInstance()->stopTextInput();
    }
}

void Console::draw()
{
    if (isOpen) {
        drawFilledRectangle(Engine::getInstance()->getViewportX(), Engine::getInstance()->getViewportY(),
                      Engine::getInstance()->getViewportW(), Engine::getInstance()->getViewportH() / 2,
                      0, 0, 0, 160);

        font->setSDLColor(defaultColor);

        Engine::getInstance()->renderTextF(Engine::getInstance()->getViewportX() + 5,
                                           Engine::getInstance()->getViewportY() + (Engine::getInstance()->getViewportH() / 2) - 20,
                                           font,
                                           "%s%s", prompt.c_str(), text.c_str());

        for (int i = 0; i < LINE_NUM; ++i) {
            font->setSDLColor(lineColors[i]);
            Engine::getInstance()->renderText(Engine::getInstance()->getViewportX() + 5,
                                              Engine::getInstance()->getViewportY() + (Engine::getInstance()->getViewportH() / 2) - (10 * i) - 50,
                                              font,
                                              lines[i].c_str());
        }
    }
}
}
