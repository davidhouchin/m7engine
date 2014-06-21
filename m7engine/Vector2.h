/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Vector2
 *  Vector2.cpp
 *  Purpose: Vector handling routines.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef VECTOR2_H
#define	VECTOR2_H

#include <math.h>

namespace M7engine {
class Vector2 {
public:
    Vector2();
    Vector2(const Vector2& v);
    Vector2(int x, int y);
    Vector2(double x, double y);
    /**
     *  Placeholder description.
     */
    void set(double x1, double y1);
    /**
     *  Placeholder description.
     */
    void set(const Vector2& v);
    /**
     *  Placeholder description.
     */
    double getX(){ return x; }
    /**
     *  Placeholder description.
     */
    void setX(double arg){ x = arg; }
    /**
     *  Placeholder description.
     */
    double getY(){ return y; }
    /**
     *  Placeholder description.
     */
    void setY(double arg){ y = arg; }
    /**
     *  Placeholder description.
     */
    void move(double mx, double my);
    /**
     *  Placeholder description.
     */
    void operator+=(const Vector2& v);
    /**
     *  Placeholder description.
     */
    void operator-=(const Vector2& v);
    /**
     *  Placeholder description.
     */
    void operator*=(const Vector2& v);
    /**
     *  Placeholder description.
     */
    void operator/=(const Vector2& v);
    /**
     *  Placeholder description.
     */
    bool operator==(const Vector2& v) const;
    /**
     *  Placeholder description.
     */
    bool operator!=(const Vector2& p) const;
    /**
     *  Placeholder description.
     */
    Vector2& operator=(const Vector2& v);
    /**
     *  Placeholder description.
     */
    double distance(const Vector2& v);
    /**
     *  Placeholder description.
     */
    double length();
    /**
     *  Placeholder description.
     */
    double dotProduct(const Vector2& v);
    /**
     *  Placeholder description.
     */
    Vector2 normal();

private:
    double x, y;
};
}

#endif
