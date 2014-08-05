/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Console
 *  Console.h
 *  Purpose: Debug console for viewing information and setting parameters in-game.
 *  @author David Houchin
 *  @version 1.0 8/4/14
 */

#ifndef CONSOLE_H
#define	CONSOLE_H

#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "Logger.h"
#include "Text.h"

#define LINE_NUM 20

namespace M7engine {
class Console {
public:
    /**
     *  Returns a pointer to the input manager.
     *  @return Pointer to input manager.
     */
    static Console* getInstance();

    virtual ~Console();

    bool init();

    void update();

    void draw();

    void addLine(std::string text, SDL_Color color);

    void parse(std::string text);

    void setFont(Font *font) { this->font = font; }

private:
    Console();
    static Console* consoleInstance;

    bool isOpen;

    std::string text, prompt;

    std::string lines[LINE_NUM];
    SDL_Color lineColors[LINE_NUM];

    SDL_Color defaultColor;

    Font* font;
};
}

#endif
