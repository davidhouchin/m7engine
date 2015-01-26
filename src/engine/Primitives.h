/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Primitives
 *  Primitives.h
 *  Purpose: Functions for drawing geometry.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#include <SDL2/SDL.h>

namespace M7engine {

    /**
     *  @brief Draws a line.
     *  @param x1 The originating X point.
     *  @param y1 The originating Y point.
     *  @param x2 The destination X point.
     *  @param y2 The destination Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  @brief Draws an outlined rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param w The width of the rectangle.
     *  @param h The height of the rectangle.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  @brief Draws a filled rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param w The width of the rectangle.
     *  @param h The height of the rectangle.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
}

#endif
