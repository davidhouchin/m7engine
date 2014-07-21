/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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
#include <SDL2/SDL.h>

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"
#include "ConfigReader.h"
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
    bool loadConfig(std::string filename);

    /**
     *  Parse the contents of the loaded configuration file.
     */
    bool parseConfig();

    /**
     *  Set the path to resolve resource names from.
     *  @param path String to use as resource path.
     */
    void setPath(std::string path) {resolvePath = path; }

    /**
     *  Get the path to resolve resource names from.
     *  @return String being used as resource path.
     */
    std::string getPath() { return resolvePath; }

    /**
     *  Returns a pointer to the requested sprite. Returns NULL if not found.
     *  @return Pointer to requested sprite.
     */
    Sprite* getSprite(const char *name);

    /**
     *  Returns a pointer to the requested sound. Returns NULL if not found.
     *  @return Pointer to requested sound.
     */
    Sound* getSound(const char *name);

    /**
     *  Returns a pointer to the requested font. Returns NULL if not found.
     *  @return Pointer to requested font.
     */
    Font* getFont(const char *name);

private:
    ResourceManager();
    static ResourceManager* managerInstance;
    std::map<std::string, Sprite*> spriteList;
    typedef std::map<std::string, Sprite*>::iterator iterSpriteList;
    std::map<std::string, Sound*> soundList;
    typedef std::map<std::string, Sound*>::iterator iterSoundList;
    std::map<std::string, Font*> fontList;
    typedef std::map<std::string, Font*>::iterator iterFontList;

    bool configLoaded;

    std::string resolvePath;

    ConfigReader *resourceReader;
};
}
#endif
