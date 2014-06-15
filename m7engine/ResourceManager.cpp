/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "ResourceManager.h"

namespace M7engine
{

ResourceManager* ResourceManager::managerInstance = NULL;

ResourceManager* ResourceManager::getInstance()
{
	if (!managerInstance)
	{
		managerInstance = new ResourceManager;
	}

	return managerInstance;
}

ResourceManager::ResourceManager()
{
	resourceConfig = NULL;
}

ResourceManager::~ResourceManager()
{
	al_destroy_config(resourceConfig);

	for (iterSpriteList iter = spriteList.begin(); iter != spriteList.end(); ++iter)
	{
		delete iter->second;
	}
	spriteList.clear();

	for (iterSoundList iter = soundList.begin(); iter != soundList.end(); ++iter)
	{
		delete iter->second;
	}
	soundList.clear();

	for (iterFontList iter = fontList.begin(); iter != fontList.end(); ++iter)
	{
		delete iter->second;
	}
	fontList.clear();
}

bool ResourceManager::loadConfig(const char *filename)
{
	Logger::getInstance()->logMessage(0, "ResourceManager loading config file: '%s'", filename);

	resourceConfig = al_load_config_file(filename);
	if (!resourceConfig)
	{
		Logger::getInstance()->logError(0, "ResourceManager failed to load config file: '%s'", filename);
		return false;
	}
	else
	{
		parseConfig();
		return true;
	}
}

bool ResourceManager::parseConfig()
{
	if (!resourceConfig)
	{
		Logger::getInstance()->logError(0, "ResourceManager failed to parse resources, no config file");

		return false;
	}

	ALLEGRO_CONFIG_SECTION *iter;
	const char *section = al_get_first_config_section(resourceConfig, &iter);

	while (section != NULL)
	{
		if (section != "")
		{
			const char *fname;

			if (al_get_config_value(resourceConfig, section, "filename")) { 
				fname = al_get_config_value(resourceConfig, section, "filename");
				
				if (std::strcmp(al_get_config_value(resourceConfig, section, "type"), "sprite") == 0)
				{
					int fw = NULL, fh = NULL, fc = NULL, f = NULL;
					Sprite *newSprite = new Sprite;
					newSprite->setName(section);

					if (al_get_config_value(resourceConfig, section, "frameWidth")) { fw = atoi(al_get_config_value(resourceConfig, section, "frameWidth")); }
					if (al_get_config_value(resourceConfig, section, "frameHeight")) { fh = atoi(al_get_config_value(resourceConfig, section, "frameHeight")); }
					if (al_get_config_value(resourceConfig, section, "frameColumns")) { fc = atoi(al_get_config_value(resourceConfig, section, "frameColumns")); }
					if (al_get_config_value(resourceConfig, section, "frames")) { f = atoi(al_get_config_value(resourceConfig, section, "frames")); }
					if (al_get_config_value(resourceConfig, section, "delay")) { newSprite->setDelay(atoi(al_get_config_value(resourceConfig, section, "delay"))); }

					newSprite->loadImage(fname, fw, fh, fc, f);

					spriteList.insert(std::pair<const char*, Sprite*>(section, newSprite));
				}
				else if (std::strcmp(al_get_config_value(resourceConfig, section, "type"), "sound") == 0)
				{
					Sample *newSample = new Sample;
					newSample->setName(section);

					newSample->loadSample(fname);

					soundList.insert(std::pair<const char*, Sample*>(section, newSample));
				}
				else if (std::strcmp(al_get_config_value(resourceConfig, section, "type"), "font") == 0)
				{
					Font *newFont = new Font;
					newFont->setName(section);

					int s = NULL;
					if (al_get_config_value(resourceConfig, section, "size")) { s = atoi(al_get_config_value(resourceConfig, section, "size")); }

					newFont->loadFont(fname, s);

					fontList.insert(std::pair<const char*, Font*>(section, newFont));
				}
			}
		}

		section = al_get_next_config_section(&iter);
	}

	Logger::getInstance()->logMessage(0, "ResourceManager done parsing config file");
	return true;
}

bool ResourceManager::reloadResources()
{
	for (iterSpriteList iter = spriteList.begin(); iter != spriteList.end(); ++iter)
	{
		delete iter->second;
	}
	spriteList.clear();
	
	if (!resourceConfig)
	{
		Logger::getInstance()->logError(0, "ResourceManager failed to parse resources, no config file");

		return false;
	}

	ALLEGRO_CONFIG_SECTION *iter;
	const char *section = al_get_first_config_section(resourceConfig, &iter);

	while (section != NULL)
	{
		if (section != "")
		{
			const char *fname;

			if (al_get_config_value(resourceConfig, section, "filename")) {
				fname = al_get_config_value(resourceConfig, section, "filename");

				if (std::strcmp(al_get_config_value(resourceConfig, section, "type"), "sprite") == 0)
				{
					int fw = NULL, fh = NULL, fc = NULL, f = NULL;
					Sprite *newSprite = new Sprite;
					newSprite->setName(section);

					if (al_get_config_value(resourceConfig, section, "frameWidth")) { fw = atoi(al_get_config_value(resourceConfig, section, "frameWidth")); }
					if (al_get_config_value(resourceConfig, section, "frameHeight")) { fh = atoi(al_get_config_value(resourceConfig, section, "frameHeight")); }
					if (al_get_config_value(resourceConfig, section, "frameColumns")) { fc = atoi(al_get_config_value(resourceConfig, section, "frameColumns")); }
					if (al_get_config_value(resourceConfig, section, "frames")) { f = atoi(al_get_config_value(resourceConfig, section, "frames")); }
					if (al_get_config_value(resourceConfig, section, "delay")) { newSprite->setDelay(atoi(al_get_config_value(resourceConfig, section, "delay"))); }

					newSprite->loadImage(fname, fw, fh, fc, f);

					spriteList.insert(std::pair<const char*, Sprite*>(section, newSprite));
				}
			}
		}

		section = al_get_next_config_section(&iter);
	}

	Logger::getInstance()->logMessage(0, "ResourceManager done reloading sprites from config file");
	return true;
}

Sprite* ResourceManager::getSprite(const char *name)
{
	Sprite *reqSprite = spriteList[name];
	if (reqSprite != NULL)
	{
		return reqSprite;
	}
	else
	{
		Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name);
		return NULL;
	}
}

Sample* ResourceManager::getSound(const char *name)
{
	Sample *reqSample = soundList[name];
	if (reqSample != NULL)
	{
		return reqSample;
	}
	else
	{
		Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name);
		return NULL;
	}
}

Font* ResourceManager::getFont(const char *name)
{
	Font *reqFont = fontList[name];
	if (reqFont != NULL)
	{
		return reqFont;
	}
	else
	{
		Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name);
		return NULL;
	}
}
}