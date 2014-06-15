/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#include <stdio.h>
#include <map>
#include <string>
#include <allegro.h>
#include "SoundManager.h"
#include "Sprite.h"
#include "Font.h"
#include "Logger.h"

namespace M7engine
{
	class ResourceManager
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();

		bool loadConfig(const char *filename);
		bool parseConfig();

		void reloadResources();

		Sprite* getSprite(const char *name);
		Sample* getSound(const char *name);
		Font* getFont(const char *name);


	private:
		ALLEGRO_CONFIG* resourceConfig;
		std::map<std::string, Sprite*> spriteList;
		std::map<std::string, Sample*> soundList;
		std::map<std::string, Font*> fontList;

	};
}
#endif
