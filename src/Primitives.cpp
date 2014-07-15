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
 *  Purpose: Primitive drawing routines.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Primitives.h"
#include "M7engine.h"

namespace M7engine {
Primitives::Primitives()
{
}

Primitives::~Primitives()
{
}

bool Primitives::init()
{
    return true;
}

void Primitives::drawLine(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    lineRGBA(Engine::getInstance()->getInstance()->getRenderer(), x1, y1, x2, y2, r, g, b, a);
}

void Primitives::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    trigonRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, x3, y3, r, g, b, a);
}

void Primitives::drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    filledTrigonRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, x3, y3, r, g, b, a);
}

void Primitives::drawRectangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    rectangleRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, r, g, b, a);
}

void Primitives::drawFilledRectangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    boxRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, r, g, b, a);
}

void Primitives::drawRoundedRectangle(float x1, float y1, float x2, float y2, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    roundedRectangleRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, rad, r, g, b, a);
}

void Primitives::drawFilledRoundedRectangle(float x1, float y1, float x2, float y2, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    roundedBoxRGBA(Engine::getInstance()->getRenderer(), x1, y1, x2, y2, rad, r, g, b, a);
}

void Primitives::drawEllipse(int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    ellipseRGBA(Engine::getInstance()->getRenderer(), x, y, rx, ry, r, g, b, a);
}

void Primitives::drawFilledEllipse(int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    filledEllipseRGBA(Engine::getInstance()->getRenderer(), x, y, rx, ry, r, g, b, a);
}

void Primitives::drawCircle(int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    circleRGBA(Engine::getInstance()->getRenderer(), x, y, rad, r, g, b, a);
}

void Primitives::drawFilledCircle(int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    filledCircleRGBA(Engine::getInstance()->getRenderer(), x, y, rad, r, g, b, a);
}

void Primitives::drawArc(int x, int y, int rad, int start, int delta, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    arcRGBA(Engine::getInstance()->getRenderer(), x, y, rad, start, delta, r, g, b, a);
}
}
