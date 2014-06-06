/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef VECTOR2_H
#define	VECTOR2_H

#include <math.h>

namespace M7engine
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(const Vector2& v);
		Vector2(int x, int y);
		Vector2(double x, double y);
		void set(double x1, double y1);
		void set(const Vector2& v);
		double getX(){ return x; }
		void setX(double arg){ x = arg; }
		double getY(){ return y; }
		void setY(double arg){ y = arg; }
		void move(double mx, double my);
		void operator+=(const Vector2& v);
		void operator-=(const Vector2& v);
		void operator*=(const Vector2& v);
		void operator/=(const Vector2& v);
		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& p) const;
		Vector2& operator=(const Vector2& v);
		double distance(const Vector2& v);
		double length();
		double dotProduct(const Vector2& v);
		Vector2 normal();

	private:
		double x, y;

	};
}

#endif
