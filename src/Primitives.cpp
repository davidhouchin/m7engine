/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Primitives
 *  Primitives.cpp
 *  Purpose: Functions for drawing geometry.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Primitives.h"
#include "M7engine.h"

void M7engine::drawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(), r, g, b, a);
    SDL_RenderDrawLine(Engine::getInstance()->getRenderer(), x1- Engine::getInstance()->getViewportX(), y1 - Engine::getInstance()->getViewportY(),
                       x2 - Engine::getInstance()->getViewportX(), y2 - Engine::getInstance()->getViewportY());
}

void M7engine::drawRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Rect drawRect = { x- Engine::getInstance()->getViewportX(), y - Engine::getInstance()->getViewportY(), w, h };
    SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(), r, g, b, a);
    SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &drawRect);
}

void M7engine::drawFilledRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Rect drawRect = { x - Engine::getInstance()->getViewportX(), y - Engine::getInstance()->getViewportY(), w, h };
    SDL_SetRenderDrawColor(Engine::getInstance()->getRenderer(), r, g, b, a);
    SDL_RenderFillRect(Engine::getInstance()->getRenderer(), &drawRect);
}
