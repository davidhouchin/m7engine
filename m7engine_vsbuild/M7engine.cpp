/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "M7engine.h"

namespace M7engine
{
	Engine::Engine()
	{
		frameRate = 30;
		frameCount = 0;
		fps = 0;

		this->setScreenWidth(640);
		this->setScreenHeight(480);
		this->setColorDepth(32);
		this->setFullScreen(false);
	}

	Engine::~Engine()
	{
		std::cout << "Cleaning up resources...\n";
		//al_destroy_timer(this->timer);
		//al_destroy_display(this->display);
		//al_destroy_event_queue(this->eventQueue);
	}

	bool Engine::init(int width, int height, bool fullscreen)
	{
		this->setScreenWidth(width);
		this->setScreenHeight(height);

		redraw = true;

		if (!al_init())
		{
			fprintf(stderr, "al_init failed\n");
			return false;
		}

		inputManager = new InputManager;
		inputManager->init();

		soundManager = new SoundManager;
		soundManager->init();

		fontManager = new FontManager;
		fontManager->init();

		primitives = new Primitives;
		primitives->init();

		collisionManager = new CollisionManager;

		al_init_image_addon();

		timer = al_create_timer(1.0 / this->getFrameRate());
		if (!timer)
		{
			fprintf(stderr, "failed to create game loop timer\n");
			return false;
		}

		if (fullscreen)
		{
			al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		}

		al_set_new_display_flags(ALLEGRO_OPENGL);

		display = al_create_display(width, height);
		if (!display)
		{
			fprintf(stderr, "failed to create main display\n");
			al_destroy_timer(timer);
			return false;
		}

		eventQueue = al_create_event_queue();
		if (!eventQueue)
		{
			fprintf(stderr, "failed to create main event queue\n");
			al_destroy_display(display);
			al_destroy_timer(timer);
			return false;
		}

		al_register_event_source(eventQueue, al_get_display_event_source(display));
		al_register_event_source(eventQueue, al_get_timer_event_source(timer));

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

		al_start_timer(timer);

		oldTime = al_get_time();

		return true;
	}

	bool Engine::update()
	{
		//Get current FPS
		double gameTime = al_get_time();
		fps = 1.0f / (gameTime - oldTime);
		oldTime = gameTime;
		frameCount++;

		inputManager->update();

		this->updateEntities();
		this->updateCollisions();
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: return false; break;
		}

		if (redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;

			this->drawEntities();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		this->cleanEntities();

		return true;
	}

	void Engine::updateEntities()
	{
		std::list<Entity*>::iterator iter;
		Entity *entity;
		iter = entities.begin();

		while (iter != entities.end())
		{
			entity = *iter;
			if (entity->getActive())
			{
				entity->update();
			}
			iter++;
		}
	}

	void Engine::drawEntities()
	{
		std::list<Entity*>::iterator iter;
		Entity *entity;
		iter = entities.begin();

		while (iter != entities.end())
		{
			entity = *iter;
			if (entity->getVisible())
			{
				entity->draw();
			}
			iter++;
		}
	}

	void Engine::cleanEntities()
	{
		std::list<Entity*>::iterator iter;
		Entity *entity;
		iter = entities.begin();

		while (iter != entities.end())
		{
			entity = *iter;
			if (!entity->getActive())
			{
				entities.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Engine::addEntity(Entity *entity)
	{
		static int id = 0;
		entity->setID(id);
		entities.push_back(entity);
		id++;
	}

	Entity* Engine::findEntity(int id)
	{
		std::list<Entity*>::iterator iter;
		Entity *entity;
		while (iter != entities.end())
		{
			entity = *iter;
			if (entity->getID() == id)
			{
				return entity;
			}
			else
			{
				iter++;
			}
		}

		return NULL;
	}

	void Engine::updateCollisions()
	{
		std::list<Entity*>::iterator iterA, iterB;
		Entity *entityA;
		Entity *entityB;
		iterA = entities.begin();
		iterB = entities.begin();

		while (iterA != entities.end())
		{
			entityA = *iterA;

			while (iterB != entities.end())
			{
				entityB = *iterB;
				if (collisionManager->getCollisionBBox(entityA, entityB))
				{
					entityA->collision(entityB);
				}
				iterB++;
			}
			iterB = entities.begin();
			iterA++;
		}
	}

};
