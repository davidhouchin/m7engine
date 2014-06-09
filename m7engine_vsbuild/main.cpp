/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "M7engine.h"

using namespace M7engine;
Engine m7_engine;

class TestE : public M7engine::Entity
{
private:
	bool isMoving;
	int xOffset, yOffset;

public:
	TestE()
	{
		isMoving = false;
		xOffset = 0;
		yOffset = 0;
	}

	void update()
	{
		int r = rand();
		int g = rand();
		int b = rand();
		this->setColor(al_map_rgb(r, g, b));

		if (m7_engine.inputManager->getMouseX() < getX() + getWidth() && m7_engine.inputManager->getMouseX() > getX())
		{
			if (m7_engine.inputManager->getMouseY() < getY() + getHeight() && m7_engine.inputManager->getMouseY() > getY())
			{
				if (m7_engine.inputManager->getMousePressed(1))
				{
					isMoving = true;
					xOffset = m7_engine.inputManager->getMouseX() - getX();
					yOffset = m7_engine.inputManager->getMouseY() - getY();
				}
			}
		}

		if (m7_engine.inputManager->getMouseReleased(1))
		{
			isMoving = false;
		}

		if (isMoving)
		{
			setX(m7_engine.inputManager->getMouseX() - xOffset);
			setY(m7_engine.inputManager->getMouseY() - yOffset);
		}
	}

	void collision(Entity *other)
	{
	}
};

class TestE2 : public M7engine::Entity
{
	void update()
	{
		int r = rand();
		int g = rand();
		int b = rand();
		this->setColor(al_map_rgb(r, g, b));

		if (m7_engine.inputManager->getKeyHeld(ALLEGRO_KEY_W))
		{
			this->setY(this->getY() - 6.0f);
		}
		if (m7_engine.inputManager->getKeyHeld(ALLEGRO_KEY_S))
		{
			this->setY(this->getY() + 6.0f);
		}
		if (m7_engine.inputManager->getKeyHeld(ALLEGRO_KEY_A))
		{
			this->setX(this->getX() - 6.0f);
		}
		if (m7_engine.inputManager->getKeyHeld(ALLEGRO_KEY_D))
		{
			this->setX(this->getX() + 6.0f);
		}

		m7_engine.primitives->drawRectangle(getX(), getY(), getX() + getWidth(), getY() + getHeight(), al_map_rgb(255, 0, 0), 2);
	}

	void collision(Entity *other)
	{
		if (other->getID() == 2)
		{
			m7_engine.primitives->drawTriangle(5, 5, 50, 50, 5, 50, al_map_rgb(255, 0, 0), 2);
		}
	}
};

class Console : public M7engine::Entity
{
private:
	bool isOpen;
	Font *consoleFont;

public:
	Console()
	{
		isOpen = false;
		consoleFont = new Font;
		consoleFont->loadFont("linear.otf", 20);
		consoleFont->setColor(al_map_rgb(255, 255, 255));
		consoleFont->setJustification(0);
	}

	void update()
	{
		if (m7_engine.inputManager->getKeyReleased(ALLEGRO_KEY_TILDE))
		{
			isOpen = !isOpen;
		}

		if (isOpen)
		{
			m7_engine.primitives->drawFilledRectangle(0, 0, m7_engine.getScreenWidth(), 256, al_map_rgba(0, 0, 0, 50));
			m7_engine.fontManager->drawTextF(20, 20, consoleFont, "Frames: %g", (std::round(m7_engine.getFPS())));
			m7_engine.fontManager->drawTextF(20, 40, consoleFont, "X: %i", m7_engine.inputManager->getMouseX());
			m7_engine.fontManager->drawTextF(20, 60, consoleFont, "Y: %i", m7_engine.inputManager->getMouseY());
		}
	}

	void collision(Entity *other)
	{
	}
};

int main(int argc, char **argv)
{
	using namespace M7engine;
	bool running = true;

	m7_engine.init(640, 480, 0);

	//FOR TEST
	Sample *Tsample;
	TestE2 *Tentity;
	TestE *Tentity2;
	TestE *Tentity3;
	ParticleEmitter *Temitter;
	Font *Tfont;
	Font *Tfont2;
	Console *console;
	//////////

	//Print working directory (debug)
	TCHAR pwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pwd);
	fprintf(stderr, pwd);
	fprintf(stderr, "\n");

	console = new Console();

	Tentity = new TestE2();
	Tentity->loadImage("monster2.png");
	Tentity->setScale(3);
	Tentity->setSize(96, 96);

	Tentity2 = new TestE();
	Tentity2->loadImage("monster2.png");
	Tentity2->setScale(1);
	Tentity2->setColor(al_map_rgb(0, 255, 0));

	Tentity3 = new TestE();
	Tentity3->loadImage("monster2.png");
	Tentity3->setScale(2);
	Tentity3->setColor(al_map_rgb(0, 0, 255));
	Tentity3->setPosition(256, 128);
	Tentity3->setSizeToImageScale();
	
	Temitter = new ParticleEmitter();
	Temitter->loadImage("particle16.png");
	Temitter->setPosition(128, 128);
	Temitter->setScale(2);
	Temitter->setDirection(0);
	Temitter->setMax(500);
	Temitter->setAlphaRange(0, 100);
	Temitter->setColorRange(0, 0, 0, 255, 255, 255);
	Temitter->setSpread(40);
	Temitter->setVelocity(8);
	Temitter->setLength(800);

	m7_engine.addEntity(Tentity);
	m7_engine.addEntity(Tentity2);
	m7_engine.addEntity(Tentity3);
	m7_engine.addEntity(console);
	m7_engine.addEntity(Temitter);

	Tsample = new Sample();
	Tsample->loadSample("explode2.wav");

	Tfont = new Font;
	Tfont->loadFont("linear.otf", 20);
	Tfont->setColor(al_map_rgb(0, 200, 200));
	Tfont->setJustification(1);

	Tfont2 = new Font;
	Tfont2->setFont(Tfont->getFont());
	Tfont2->setColor(al_map_rgb(200, 200, 0));
	Tfont2->setJustification(0);

	while (running)
	{
		if (!m7_engine.update())
		{
			running = false;
		}

		Temitter->setPosition(Tentity->getX(), Tentity->getY());

		if (m7_engine.inputManager->getKeyReleased(ALLEGRO_KEY_ESCAPE))
		{
			return false;
		}
		if (m7_engine.inputManager->getKeyReleased(ALLEGRO_KEY_SPACE))
		{
			m7_engine.soundManager->playSample(Tsample);
		}
		if (m7_engine.inputManager->getKeyReleased(ALLEGRO_KEY_BACKSPACE))
		{
			switch (m7_engine.getWindowMode())
			{
			case 0: m7_engine.setWindowMode(1); break;
			case 1: m7_engine.setWindowMode(2); break;
			case 2: m7_engine.setWindowMode(0); break;
			}
		}
		if (m7_engine.inputManager->getKeyReleased(ALLEGRO_KEY_TAB))
		{
			switch (m7_engine.getDisplayContext())
			{
			case 0: m7_engine.setDisplayContext(1); break;
			case 1: m7_engine.setDisplayContext(0); break;
			}
		}

		if (m7_engine.collisionManager->getCollisionBBox(Tentity, Tentity2))
		{
			m7_engine.primitives->drawFilledRectangle(4, 4, 200, 200, al_map_rgba(0, 255, 0, 100));
		}
		m7_engine.fontManager->drawTextF(2, 250, Tfont2, "D:%f x1:%f x2:%f", Tentity->getPosition().distance(Tentity2->getPosition()), Tentity->getX(), Tentity2->getX());
	}

	return 0;
}
