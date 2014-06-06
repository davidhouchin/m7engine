/*   _      _    ____  _____    ______    ______
/\`\   / \  /  __\/\  __`\ /\  ___\  /\____ \
\ \ `\|   \/\ \_/\\ \ \ \ \\ \ \__/  \/___/\ \
\ \    /\ \ \ \\ \\ \ \ \ \\ \  __\      \ \ \
\ \ \`\ \ \ \ \\_\\ \ \_\ \\ \ \_/_      \ \ \
\ \ \ \ \_\ \____/\ \____, \ \_____\     \ \_\
\/_/  \/_/\/___/  \/___/   \/_____/      \/_/
*/

///////THINGS TO DO///////
//- Display depth for entities.
//- Built in collision detection.
//- Sound modifications.
//- Bitmap fonts.
//- Clean up particle system
//- Timing utils (?)
//- Lower level graphics (Bitmaps/backgrounds, etc)
//////////////////////////

#ifndef M7ENGINE_H
#define M7ENGINE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "Entity.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Vector2.h"
#include "Entity.h"
#include "ParticleEmitter.h"
#include "Primitives.h"
#include "Font.h"
#include "CollisionManager.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 4

namespace M7engine
{
	class Engine
	{
	private:
		bool fullScreen, redraw;
		int screenWidth, screenHeight, colorDepth, frameRate, frameCount;
		std::list<Entity*> entities;
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *eventQueue;
		ALLEGRO_TIMER *timer;

	public:
		Engine();
		virtual ~Engine();
		bool init(int width, int height, bool fullscreen);
		void close();
		bool update();

		void updateEntities();
		void drawEntities();
		void cleanEntities();
		void addEntity(Entity *entity);
		Entity *findEntity(int id);
		std::list<Entity*> getEntityList() { return entities; }
		long getEntityCount() { return (long)entities.size(); }

		void updateCollisions();

		ALLEGRO_DISPLAY* getDisplay() { return display; }
		ALLEGRO_EVENT_QUEUE* getEventQueue() { return eventQueue; }

		int getFrameRate() { return this->frameRate; }
		int getFrameCount() { return this->frameCount; }
		int getScreenWidth() { return this->screenWidth; }
		void setScreenWidth(int value) { this->screenWidth = value; }
		int getScreenHeight() { return this->screenHeight; }
		void setScreenHeight(int value) { this->screenHeight = value; }
		int getColorDepth() { return this->colorDepth; }
		void setColorDepth(int value) { this->colorDepth = value; }
		bool getFullScreen() { return this->fullScreen; }
		void setFullScreen(bool value) { this->fullScreen = value; }

		InputManager *inputManager;
		SoundManager *soundManager;
		FontManager *fontManager;
		Primitives *primitives;
		CollisionManager *collisionManager;

		InputManager* getInputManager() { return inputManager; }
		SoundManager* getSoundManager() { return soundManager; }
		FontManager* getFontManager() { return fontManager; }
		Primitives* getPrimitives() { return primitives; }
		CollisionManager* getCollisionManager() { return collisionManager; }
	};
};

#endif
