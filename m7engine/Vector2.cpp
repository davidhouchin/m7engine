/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "Vector2.h"

namespace M7engine
{
Vector2::Vector2()
{
	x = y = 0;
}

Vector2::Vector2(const Vector2& v)
{
	*this = v;
}

Vector2::Vector2(int x, int y)
{
	set((double)x, (double)y);
}

Vector2::Vector2(double x, double y)
{
	set(x, y);
}

void Vector2::set(double x1, double y1)
{
	x = x1;
	y = y1;
}

void Vector2::set(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

void Vector2::move(double mx, double my)
{
	x += mx;
	y += my;
}

void Vector2::operator +=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator -=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator *=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
}

void Vector2::operator /=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
}

bool Vector2::operator ==(const Vector2& v) const
{
	return(
		(((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
		(((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))));
}

bool Vector2::operator !=(const Vector2& p) const
{
	return (!(*this == p));
}

Vector2& Vector2::operator =(const Vector2& v)
{
	set(v);
	return *this;
}

double Vector2::distance(const Vector2& v)
{
	return sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y));
}

double Vector2::length()
{
	return sqrt(x*x + y*y);
}

double Vector2::dotProduct(const Vector2& v)
{
	return (x*v.x + y*v.y);
}
}
