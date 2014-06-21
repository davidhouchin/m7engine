/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Primitives
 *  Primitives.cpp
 *  Purpose: Primitive drawing routines.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace M7engine {
class Primitives {
public:
    Primitives();
    virtual ~Primitives();

    /**
     *  Initializes the Allegro primitives addon.
     */
    bool init();

    /**
     *  Draws a line.
     *  @param x1 The originating X point.
     *  @param y1 The originating Y point.
     *  @param x2 The destination X point.
     *  @param y2 The destination Y point.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);

    /**
     *  Draws a triangle.
     *  @param x1 The first X point.
     *  @param y1 The first Y point.
     *  @param x2 The second X point.
     *  @param y2 The second Y point.
     *  @param x3 The third X point.
     *  @param y3 The third Y point.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color, float thickness);
    /**
     *  Draws a filled triangle.
     *  @param x1 The first X point.
     *  @param y1 The first Y point.
     *  @param x2 The second X point.
     *  @param y2 The second Y point.
     *  @param x3 The third X point.
     *  @param y3 The third Y point.
     *  @param color The color of the triangle using an ALLEGRO_COLOR.
     */
    void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color);

    /**
     *  Draws a rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
    /**
     *  Draws a filled rectangle.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param color The color of the rectangle using an ALLEGRO_COLOR.
     */
    void drawFilledRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);
    /**
     *  Draws a rectangle with rounded corners.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param rx The radii of the round.
     *  @param ry The radii of the round.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color, float thickness);
    /**
     *  Draws a filled rectangle with rounded corners.
     *  @param x1 The upper left X point.
     *  @param y1 The upper left Y point.
     *  @param x2 The lower right X point.
     *  @param y2 The lower right Y point.
     *  @param rx The radii of the round.
     *  @param ry The radii of the round.
     *  @param color The color of the rectangle using an ALLEGRO_COLOR.
     */
    void drawFilledRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color);

    /**
     *  Draws an ellipse.
     *  @param cx The center X point.
     *  @param cy The center Y point.
     *  @param rx The radii of the ellipse.
     *  @param ry The radii of the ellipse.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color, float thickness);
    /**
     *  Draws a filled ellipse.
     *  @param cx The center X point.
     *  @param cy The center Y point.
     *  @param rx The radii of the ellipse.
     *  @param ry The radii of the ellipse.
     *  @param color The color of the ellipse using an ALLEGRO_COLOR.
     */
    void drawFilledEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color);

    /**
     *  Draws a circle.
     *  @param cx The center X point.
     *  @param cy The center Y point.
     *  @param r The radius of the circle.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawCircle(float cx, float cy, float r, ALLEGRO_COLOR color, float thickness);
    /**
     *  Draws a filled circle.
     *  @param cx The center X point.
     *  @param cy The center Y point.
     *  @param r The radius of the circle.
     *  @param color The color of the circle using an ALLEGRO_COLOR.
     */
    void drawFilledCircle(float cx, float cy, float r, ALLEGRO_COLOR color);

    /**
     *  Draws an arc.
     *  @param cx The center X point.
     *  @param cy The center Y point.
     *  @param r The radius of the arc.
     *  @param start_theta Initial angle from which the arc is calculated.
     *  @param delta_theta Angular span of arc. Use a negative value to switch direction.
     *  @param color The color of the line using an ALLEGRO_COLOR.
     *  @param thickness The thickness of the line.
     */
    void drawArc(float cx, float cy, float r, float start_theta, float delta_theta, ALLEGRO_COLOR color, float thickness);
};
}
#endif
