/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Resource Manager
 *  ResourceManager.h
 *  Purpose: Manager to handle loading resources from config files and giving them to requesting objects.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#include <stdio.h>
#include <map>
#include <string>
#include <allegro5/allegro.h>
#include "SoundManager.h"
#include "Sprite.h"
#include "Font.h"
#include "Logger.h"

namespace M7engine {
class ResourceManager {
public:
    /**
     *  Returns the static instance of the resource manager.
     *  @return Pointer to resource manager.
     */
    static ResourceManager* getInstance();

    virtual ~ResourceManager();

    /**
     *  Load a resource configuration file.
     *  @return Char array containing filename to config file.
     */
    bool loadConfig(const char *filename);
    /**
     *  Parse the contents of the loaded configuration file.
     */
    bool parseConfig();

    /**
     *  Reloads all volatile resources from disk.
     */
    bool reloadResources();

    /**
     *  Returns a pointer to the requested sprite, if found.
     *  @return Pointer to requested sprite.
     */
    Sprite* getSprite(const char *name);
    /**
     *  Returns a pointer to the requested sound, if found.
     *  @return Pointer to requested sound.
     */
    Sample* getSound(const char *name);
    /**
     *  Returns a pointer to the requested font, if found.
     *  @return Pointer to requested font.
     */
    Font* getFont(const char *name);

private:
    ResourceManager();
    static ResourceManager* managerInstance;
    ALLEGRO_CONFIG* resourceConfig;
    std::map<std::string, Sprite*> spriteList;
    typedef std::map<std::string, Sprite*>::iterator iterSpriteList;
    std::map<std::string, Sample*> soundList;
    typedef std::map<std::string, Sample*>::iterator iterSoundList;
    std::map<std::string, Font*> fontList;
    typedef std::map<std::string, Font*>::iterator iterFontList;
};
}
#endif
