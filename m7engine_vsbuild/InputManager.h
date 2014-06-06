#ifndef INPUTMANAGER_H
#define	INPUTMANAGER_H

#include <stdio.h>
#include <allegro5/allegro.h>

namespace M7engine
{
	class InputManager
	{
	public:
		InputManager();
		virtual ~InputManager();
		bool init();
		void update();

		int getMouseX() { return this->mouseX; }
		int getMouseY() { return this->mouseY; }
		int getMouseZ() { return this->mouseZ; }
		int getMouseKeyNum() { return al_get_mouse_num_buttons(); }
		bool getMouseState(int arg) { return al_mouse_button_down(&mouseState, arg); }
		bool getMousePressed(int arg) { return mouseKeyStates[arg] & KEY_PRESS; }
		bool getMouseReleased(int arg) { return mouseKeyStates[arg] & KEY_RELEASE; }
		bool getMouseHeld(int arg) { return mouseKeyStates[arg] & KEY_HELD; }
		bool getMouseOpen(int arg) { return mouseKeyStates[arg] & KEY_OPEN; }

		bool getKeyState(int arg) { return al_key_down(&keyboardState, arg); }
		bool getKeyPressed(int arg) { return keyStates[arg] & KEY_PRESS; }
		bool getKeyReleased(int arg) { return keyStates[arg] & KEY_RELEASE; }
		bool getKeyHeld(int arg) { return keyStates[arg] & KEY_HELD; }
		bool getKeyOpen(int arg) { return keyStates[arg] & KEY_OPEN; }

	private:
		int mouseX, mouseY, mouseZ;
		ALLEGRO_EVENT_QUEUE *keyboardQueue;
		ALLEGRO_EVENT_QUEUE *mouseQueue;
		ALLEGRO_KEYBOARD_STATE keyboardState;
		ALLEGRO_MOUSE_STATE mouseState;
		bool* mouseKeys;
		bool* oldMouseKeys;
		int* mouseKeyStates;
		bool keys[ALLEGRO_KEY_MAX];
		bool oldKeys[ALLEGRO_KEY_MAX];
		int keyStates[ALLEGRO_KEY_MAX];
		enum KEYSTATE
		{
			KEY_PRESS = 1, KEY_RELEASE = 2, KEY_HELD = 4, KEY_OPEN = 8
		};
	};
}

#endif
