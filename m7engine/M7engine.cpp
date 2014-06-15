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

	#ifdef _WIN32
		this->displayContext = 0;
	#elif
		this->displayContext = 1;
	#endif

	configReader = new ConfigReader;
}

Engine::~Engine()
{
	Logger::getInstance()->logMessage(0, "Cleaning up resources...");

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
		Logger::getInstance()->logError(0, "al_init failed");
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
		Logger::getInstance()->logError(0, "Failed to create game loop timer");
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
		Logger::getInstance()->logError(0, "Failed to create main display");
		al_destroy_timer(timer);
		return false;
	}

	eventQueue = al_create_event_queue();
	if (!eventQueue)
	{
		Logger::getInstance()->logError(0, "Failed to create main event queue");
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
	Logger::getInstance()->logMessage(1, "Engine update cycle: %i", frameCount);

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
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (gameTime - oldTime >= 1.0)
		{
			fps = this->getFrameRate() / (gameTime - oldTime);
			oldTime = gameTime;
		}
	}

	this->cleanEntities();

	Logger::getInstance()->logMessage(1, "Engine update cycle complete");

	return true;
}

void Engine::updateEntities()
{
	Logger::getInstance()->logMessage(1, "Engine is updating entities");

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
	Logger::getInstance()->logMessage(1, "Engine is drawing");

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
	Logger::getInstance()->logMessage(1, "Engine is cleaning");

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
	Logger::getInstance()->logMessage(0, "Engine added entity id: %i", id);
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
	Logger::getInstance()->logMessage(99, "Engine is updating collisions");

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
	case 0: 
		#ifdef _WIN32
		al_set_new_display_flags(ALLEGRO_DIRECT3D); 
		#endif
		break;
	case 1: al_set_new_display_flags(ALLEGRO_OPENGL); break;
	}

	switch (value)
	{
	case 0:
		Logger::getInstance()->logMessage(0, "Changing to windowed mode...");
		al_destroy_display(this->display);
		display = al_create_display(getScreenWidth(), getScreenHeight());
		if (!display) { Logger::getInstance()->logError(0, "Failed to change to windowed mode"); return 1; }
		this->windowMode = 0;
		break;
	case 1:
		Logger::getInstance()->logMessage(0, "Changing to fullscreen mode...");
		al_destroy_display(this->display);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		display = al_create_display(getScreenWidth(), getScreenHeight());
		if (!display) { Logger::getInstance()->logError(0, "Failed to change to fullscreen mode"); return 1; }
		this->windowMode = 1;
		break;
	case 2:
		Logger::getInstance()->logMessage(0, "Changing to fullscreen windowed mode...");
		al_destroy_display(this->display);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
		display = al_create_display(getScreenWidth(), getScreenHeight());
		if (!display) { Logger::getInstance()->logError(0, "Failed to change to fullscreen windowed mode"); return 1; }
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
		#ifdef _WIN32
		Logger::getInstance()->logMessage(0, "Changing to Direct3D context...");
		al_destroy_display(this->display);
		al_set_new_display_flags(ALLEGRO_DIRECT3D);
		display = al_create_display(getScreenWidth(), getScreenHeight());
		if (!display) { Logger::getInstance()->logError(0, "Failed to change to Direct3D context"); return 1; }
		this->displayContext = 0;
		#endif
		break;
	case 1:
		Logger::getInstance()->logMessage(0, "Changing to OpenGL context...");
		al_destroy_display(this->display);
		al_set_new_display_flags(ALLEGRO_OPENGL);
		display = al_create_display(getScreenWidth(), getScreenHeight());
		if (!display) { Logger::getInstance()->logError(0, "Failed to change to OpenGL context"); return 1; }
		this->displayContext = 1;
		break;
	}

	this->reloadBitmaps();

	return 0;
}

void Engine::reloadBitmaps()
{
	Logger::getInstance()->logMessage(0, "Engine is reloading bitmaps...");
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
