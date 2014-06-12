/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "InputManager.h"

namespace M7engine
{
InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	al_destroy_event_queue(this->keyboardQueue);
	al_destroy_event_queue(this->mouseQueue);

	delete[] mouseKeys;
	delete[] oldMouseKeys;
	delete[] mouseKeyStates;
}

bool InputManager::init()
{
	if (!al_install_mouse())
	{
		fprintf(stderr, "Failed to initialize mouse!");
		return false;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "Failed to initialize keyboard!");
		return false;
	}

	keyboardQueue = al_create_event_queue();
	if (!keyboardQueue)
	{
		fprintf(stderr, "Failed to create keyboard input event queue!");
		return false;
	}

	mouseQueue = al_create_event_queue();
	if (!mouseQueue)
	{
		fprintf(stderr, "Failed to create mouse input event queue!");
		return false;
	}

	al_register_event_source(mouseQueue, al_get_mouse_event_source());
	al_register_event_source(keyboardQueue, al_get_keyboard_event_source());

	mouseX = 0;
	mouseY = 0;
	mouseZ = 0;

	mouseKeys = new bool[getMouseKeyNum()];
	oldMouseKeys = new bool[getMouseKeyNum()];
	mouseKeyStates = new int[getMouseKeyNum()];

	for (int i = 0; i < ALLEGRO_KEY_MAX; ++i)
	{
		keys[i] = false;
		oldKeys[i] = false;
	}

	for (int i = 0; i < getMouseKeyNum(); ++i)
	{
		mouseKeys[i] = false;
		oldMouseKeys[i] = false;
	}

	return true;
}

void InputManager::update()
{
	al_get_keyboard_state(&keyboardState);
	al_get_mouse_state(&mouseState);

	for (int i = 0; i < ALLEGRO_KEY_MAX; ++i)
	{
		oldKeys[i] = keys[i];
		keys[i] = al_key_down(&keyboardState, i);
	}
	for (int i = 0; i < ALLEGRO_KEY_MAX; ++i)
	{
		if (keys[i] && !oldKeys[i]){ keyStates[i] = KEY_PRESS; }
		if (!keys[i] && oldKeys[i]){ keyStates[i] = KEY_RELEASE; }
		if (keys[i] && oldKeys[i]){ keyStates[i] = KEY_HELD; }
		if (!keys[i] && !oldKeys[i]){ keyStates[i] = KEY_OPEN; }
	}

	ALLEGRO_EVENT k_ev;
	al_get_next_event(keyboardQueue, &k_ev);

	keyLast = k_ev.keyboard.keycode;

	for (int i = 1; i < getMouseKeyNum(); ++i)
	{
		oldMouseKeys[i] = mouseKeys[i];
		mouseKeys[i] = al_mouse_button_down(&mouseState, i);
	}
	for (int i = 1; i < getMouseKeyNum(); ++i)
	{
		if (mouseKeys[i] && !oldMouseKeys[i]){ mouseKeyStates[i] = KEY_PRESS; }
		if (!mouseKeys[i] && oldMouseKeys[i]){ mouseKeyStates[i] = KEY_RELEASE; }
		if (mouseKeys[i] && oldMouseKeys[i]){ mouseKeyStates[i] = KEY_HELD; }
		if (!mouseKeys[i] && !oldMouseKeys[i]){ mouseKeyStates[i] = KEY_OPEN; }
	}

	ALLEGRO_EVENT m_ev;
	al_get_next_event(mouseQueue, &m_ev);
	al_flush_event_queue(mouseQueue);

	switch (m_ev.type)
	{
	case ALLEGRO_EVENT_MOUSE_AXES:
		mouseX = m_ev.mouse.x;
		mouseY = m_ev.mouse.y;
		mouseZ = m_ev.mouse.z;
		mouseDX = m_ev.mouse.dx;
		mouseDY = m_ev.mouse.dy;
		mouseDZ = m_ev.mouse.dz;
		break;
	}
}
}
