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
		this->windowMode = 0;
		this->displayContext = 0;

		configReader = new ConfigReader;
	}

	Engine::~Engine()
	{
		std::cout << "Cleaning up resources...\n";
		//Comment out for now because it causes a crash on exit
		/*delete inputManager;
		delete soundManager;
		delete fontManager;
		delete primitives;
		delete collisionManager;

		al_destroy_bitmap(this->icon);
		al_destroy_timer(this->timer);
		al_destroy_display(this->display);
		al_destroy_event_queue(this->eventQueue);*/
	}

	bool Engine::init(int width, int height, int mode)
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

		switch (mode)
		{
		case 1: al_set_new_display_flags(ALLEGRO_FULLSCREEN); this->windowMode = 1; break;
		case 2: al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW); this->windowMode = 2; break;
		}

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
		al_register_event_source(eventQueue, al_get_mouse_event_source());

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

		al_start_timer(timer);

		oldTime = al_get_time();

		return true;
	}

	bool Engine::update()
	{
		fprintf(stdout, "Engine update cycle: %i\n", frameCount);

		inputManager->update();
		
		frameCount++;

		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: 
			return false;
			break;
		}

		if (redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;

			double gameTime = al_get_time();

			updateCollisions();
			updateEntities();
			drawEntities();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 255, 255));

			if (gameTime - oldTime >= 1.0)
			{
				fps = this->getFrameRate() / (gameTime - oldTime);
				oldTime = gameTime;
			}
		}

		this->cleanEntities();

		fprintf(stdout, "Engine update cycle complete.\n");
		return true;
	}

	void Engine::updateEntities()
	{
		fprintf(stdout, "Engine is updating entities.\n");
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
		fprintf(stdout, "Engine is drawing.\n");
		al_set_target_backbuffer(display);
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
		fprintf(stdout, "Engine is cleaning.\n");
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
		fprintf(stdout, "Engine added entity id: %i\n", id);
		id++;
	}

	void Engine::addParticleEmitter(ParticleEmitter *particleEmitter)
	{
		particleEmitters.push_back(particleEmitter);
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
		fprintf(stdout, "Engine is updating collisions.\n");
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

	bool Engine::setWindowMode(int value)
	{
		switch (displayContext)
		{
		case 0: al_set_new_display_flags(ALLEGRO_DIRECT3D); break;
		case 1: al_set_new_display_flags(ALLEGRO_OPENGL); break;
		}

		switch (value)
		{
		case 0:
			std::cout << "Changing to windowed mode...\n";
			al_destroy_display(this->display);
			display = al_create_display(getScreenWidth(), getScreenHeight());
			if (!display) { fprintf(stderr, "Failed to change to windowed mode!\n"); return 1; }
			this->windowMode = 0;
			break;
		case 1:
			std::cout << "Changing to fullscreen...\n";
			al_destroy_display(this->display);
			al_set_new_display_flags(ALLEGRO_FULLSCREEN);
			display = al_create_display(getScreenWidth(), getScreenHeight());
			if (!display) { fprintf(stderr, "Failed to change to fullscreen mode!\n"); return 1; }
			this->windowMode = 1;
			break;
		case 2:
			std::cout << "Changing to fullscreen windowed...\n";
			al_destroy_display(this->display);
			al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
			display = al_create_display(getScreenWidth(), getScreenHeight());
			if (!display) { fprintf(stderr, "Failed to change to fullscreen windowed mode!\n"); return 1; }
			this->windowMode = 2;
			break;
		}

		this->reloadBitmaps();

		return 0;
	}

	bool Engine::setDisplayContext(int value)
	{
		switch (windowMode)
		{
		case 1: al_set_new_display_flags(ALLEGRO_FULLSCREEN); break;
		case 2: al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW); break;
		}

		switch (value)
		{
		case 0:
			std::cout << "Changing to Direct3D context...\n";
			al_destroy_display(this->display);
			al_set_new_display_flags(ALLEGRO_DIRECT3D);
			display = al_create_display(getScreenWidth(), getScreenHeight());
			if (!display) { fprintf(stderr, "Failed to change to Direct3D context!\n"); return 1; }
			this->displayContext = 0;
			break;
		case 1:
			std::cout << "Changing to OpenGL context...\n";
			al_destroy_display(this->display);
			al_set_new_display_flags(ALLEGRO_OPENGL);
			display = al_create_display(getScreenWidth(), getScreenHeight());
			if (!display) { fprintf(stderr, "Failed to change to OpenGL context!\n"); return 1; }
			this->displayContext = 1;
			break;
		}

		this->reloadBitmaps();

		return 0;
	}

	void Engine::reloadBitmaps()
	{
		fprintf(stdout, "Engine is reloading bitmaps.\n");
		std::list<Entity*>::iterator iter;
		Entity *entity;
		iter = entities.begin();

		while (iter != entities.end())
		{
			entity = *iter;
			if (entity->getActive())
			{
				entity->reloadImage();
			}
			iter++;
		}
	}
};
