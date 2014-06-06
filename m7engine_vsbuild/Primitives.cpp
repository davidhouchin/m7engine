#include "Primitives.h"

namespace M7engine
{
	Primitives::Primitives()
	{
	}

	Primitives::~Primitives()
	{
		//al_shutdown_primitives_addon();
	}

	bool Primitives::init()
	{
		if (!al_init_primitives_addon())
		{
			fprintf(stderr, "al_init_primitives_addon failed\n");
			return false;
		}

		return true;
	}

	void Primitives::drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_line(x1, y1, x2, y2, color, thickness);
	}

	void Primitives::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);
	}

	void Primitives::drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color)
	{
		al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
	}

	void Primitives::drawRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_rectangle(x1, y1, x2, y2, color, thickness);
	}

	void Primitives::drawFilledRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
	{
		al_draw_filled_rectangle(x1, y1, x2, y2, color);
	}

	void Primitives::drawRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_rounded_rectangle(x1, y1, x2, y2, rx, ry, color, thickness);
	}

	void Primitives::drawFilledRoundedRectangle(float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color)
	{
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, rx, ry, color);
	}

	void Primitives::drawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_ellipse(cx, cy, rx, ry, color, thickness);
	}

	void Primitives::drawFilledEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color)
	{
		al_draw_filled_ellipse(cx, cy, rx, ry, color);
	}

	void Primitives::drawCircle(float cx, float cy, float r, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_circle(cx, cy, r, color, thickness);
	}

	void Primitives::drawFilledCircle(float cx, float cy, float r, ALLEGRO_COLOR color)
	{
		al_draw_filled_circle(cx, cy, r, color);
	}

	void Primitives::drawArc(float cx, float cy, float r, float start_theta, float delta_theta, ALLEGRO_COLOR color, float thickness)
	{
		al_draw_arc(cx, cy, r, start_theta, delta_theta, color, thickness);
	}
}
