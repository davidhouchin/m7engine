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
 *  Purpose: Wrapper for SDL_gfx primitive routines.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

namespace M7engine {
class Primitives {
public:
    Primitives();
    virtual ~Primitives();

    bool init();

    /**
     *  Draws a line.
     *  @param x1 The originating X point.
     *  @param y1 The originating Y point.
     *  @param x2 The destination X point.
     *  @param y2 The destination Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawLine(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  Draws a triangle.
     *  @param x1 The first X point.
     *  @param y1 The first Y point.
     *  @param x2 The second X point.
     *  @param y2 The second Y point.
     *  @param x3 The third X point.
     *  @param y3 The third Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a filled triangle.
     *  @param x1 The first X point.
     *  @param y1 The first Y point.
     *  @param x2 The second X point.
     *  @param y2 The second Y point.
     *  @param x3 The third X point.
     *  @param y3 The third Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  Draws a rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawRectangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a filled rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledRectangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a rectangle with rounded corners.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param rad The radii of the round.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawRoundedRectangle(float x1, float y1, float x2, float y2, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a filled rectangle with rounded corners.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param rad The radii of the round.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledRoundedRectangle(float x1, float y1, float x2, float y2, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  Draws an ellipse.
     *  @param x The center X point.
     *  @param y The center Y point.
     *  @param rx The radii of the ellipse.
     *  @param ry The radii of the ellipse.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawEllipse(int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a filled ellipse.
     *  @param x The center X point.
     *  @param y The center Y point.
     *  @param rx The radii of the ellipse.
     *  @param ry The radii of the ellipse.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledEllipse(int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  Draws a circle.
     *  @param x The center X point.
     *  @param y The center Y point.
     *  @param rad The radius of the circle.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawCircle(int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    /**
     *  Draws a filled circle.
     *  @param x The center X point.
     *  @param y The center Y point.
     *  @param rad The radius of the circle.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawFilledCircle(int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     *  Draws an arc.
     *  @param x The center X point.
     *  @param y The center Y point.
     *  @param rad The radius of the arc.
     *  @param start Initial angle from which the arc is calculated.
     *  @param delta Angular span of arc. Use a negative value to switch direction.
     *  @param r The red component of the draw color.
     *  @param g The green component of the draw color.
     *  @param b The blue component of the draw color.
     *  @param a The alpha component of the draw color.
     */
    void drawArc(int x, int y, int rad, int start, int delta, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};
}
#endif
