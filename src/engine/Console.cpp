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

    showDebug = true;

    gridWidth = 1;

    text = "";
    prompt = "$ ";

    inputColor = { 255, 155, 85, 255}; //Gold-Yellow
    systemColor = { 0, 255, 0, 25}; //Green
    errorColor = { 255, 0, 0, 255}; //Red
    defaultColor = { 255, 255, 255, 255}; //White

    for (int i = 0; i < LINE_NUM; ++i) {
        lines[i] = " ";
        lineColors[i] = defaultColor;
    }
}

Console::~Console()
{
}

Console::command Console::translateString(std::string const& str)
{
    if (str == "version") return eVersion;
    else if (str == "quit") return eQuit;
    else if (str == "exit") return eQuit;
    else if (str == "help") return eHelp;
    else if (str == "drawbbox") return eDrawBBox;
    else if (str == "showdebug") return eDebug;
    else if (str == "log") return eLog;
    else if (str == "framedelay") return eFps;
    else if (str == "framecap") return eCap;
    else if (str == "grid") return eGrid;
    else if (str == "rand") return eRand;
    else return eNone;
}

void Console::parse(std::string text)
{
    std::string lineToAdd;
    SDL_Color colorToAdd = defaultColor;

    std::vector<std::string> command = chunkify(text, ' ');

    switch (translateString(command[0])) {
    case eVersion: lineToAdd = Engine::getInstance()->getVersion(); break;
    case eQuit: InputManager::getInstance()->setQuit(); break;
    case eHelp: lineToAdd = "version,quit,help,drawbbox,showdebug,log,framedelay,framecap,grid"; break;
    case eDrawBBox: Engine::getInstance()->toggleDrawBoundingBoxes(); break;
    case eDebug: toggleDebug(); break;
    case eLog: Logger::getInstance()->setLoggingLevel(stringToInt(command[1])); break;
    case eFps: Engine::getInstance()->setFrameDelay(stringToInt(command[1])); break;
    case eCap: Engine::getInstance()->toggleFrameCap(); break;
    case eGrid: if (stringToInt(command[1]) != 0) {gridWidth = stringToInt(command[1]);} break;
    case eRand: if ((stringToInt(command[1]) != 0) && (stringToInt(command[2]) != 0)) {lineToAdd = intToString(randomRangeInt(stringToInt(command[1]), stringToInt(command[2]))); } break;
    default: colorToAdd = errorColor; lineToAdd = "Unrecognized Command: " + text; break;
    }

    if (lineToAdd != "") {
        addLine(lineToAdd, colorToAdd);
    }
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
    if (InputManager::getInstance()->getKeyReleased(KEY_GRAVE)) {
        isOpen = !isOpen;
        text = "";
        InputManager::getInstance()->eraseTextInput();

        if (!isOpen) {
            InputManager::getInstance()->stopTextInput();
        }
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
            lineColors[0] = inputColor;

            parse(text);

            InputManager::getInstance()->eraseTextInput();
            text = "";
        }
    }
}

void Console::draw()
{
    if (showDebug) {
        font->setSDLColor(systemColor);

        Engine::getInstance()->renderTextF(Engine::getInstance()->getViewportX() + Engine::getInstance()->getViewportW() - 50, Engine::getInstance()->getViewportY() + 10, font,
                                           "FPS: %i", Engine::getInstance()->getFPS());
        Engine::getInstance()->renderTextF(Engine::getInstance()->getViewportX() + Engine::getInstance()->getViewportW() - 110, Engine::getInstance()->getViewportY() + 20, font,
                                           "MOUSE XY: %i %i", snapToGrid(InputManager::getInstance()->getMouseX(), gridWidth), snapToGrid(InputManager::getInstance()->getMouseY(), gridWidth));
    }

    if (isOpen) {
        drawFilledRectangle(Engine::getInstance()->getViewportX(), Engine::getInstance()->getViewportY(),
                      Engine::getInstance()->getViewportW(), Engine::getInstance()->getViewportH() / 2,
                      0, 0, 0, 160);

        font->setSDLColor(inputColor);

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
