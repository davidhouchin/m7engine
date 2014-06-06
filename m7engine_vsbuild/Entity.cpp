#include "Entity.h"

namespace M7engine
{
	Entity::Entity()
	{
		this->id = -1;
		this->visible = true;
		this->active = true;
		this->image = NULL;
		this->setPosition(128, 128);
		this->direction = 0;
		this->width = 1;
		this->height = 1;
		this->rotation = 0;
		this->scale = 1;
		this->color = al_map_rgb(255, 255, 255);
	}

	Entity::~Entity()
	{
		if (image != NULL)
		{
			al_destroy_bitmap(image);
		}
	}

	bool Entity::loadImage(const char *filename)
	{
		if (image != NULL)
		{
			al_destroy_bitmap(image);
		}

		image = al_load_bitmap(filename);
		if (!image)
		{
			fprintf(stderr, "Failed to load bitmap: '%s'\n", filename);
			return false;
		}
		else
		{
			this->setSize(al_get_bitmap_width(image), al_get_bitmap_height(image));
			return true;
		}

	}

	void Entity::setImage(ALLEGRO_BITMAP *image)
	{
		this->image = image;
		this->setSize(al_get_bitmap_width(image), al_get_bitmap_height(image));
	}

	void Entity::draw()
	{
		if (image)
		{
			al_draw_tinted_scaled_rotated_bitmap(image, color, 0, 0, this->getX(), this->getY(), scale, scale, rotation, 0);
		}
	}

	void Entity::move()
	{
		this->setX(this->getX() + this->velocity.getX());
		this->setY(this->getY() + this->velocity.getY());
	}
}
