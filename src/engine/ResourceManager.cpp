/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Resource Manager
 *  ResourceManager.cpp
 *  Purpose: Manager to handle loading resources from config files and giving them to requesting objects.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "ResourceManager.h"

namespace M7engine {

ResourceManager* ResourceManager::managerInstance = NULL;

ResourceManager* ResourceManager::getInstance() {
    if (!managerInstance) {
        managerInstance = new ResourceManager;
    }
    return managerInstance;
}

ResourceManager::ResourceManager() {
    resourceReader = new ConfigReader;
    configLoaded = false;
    resolvePath = "";
}

ResourceManager::~ResourceManager() {
    delete resourceReader;

    for (iterSpriteList iter = spriteList.begin(); iter != spriteList.end(); ++iter) {
        delete iter->second;
    }
    spriteList.clear();

    for (iterSoundList iter = soundList.begin(); iter != soundList.end(); ++iter) {
        delete iter->second;
    }
    soundList.clear();

    for (iterFontList iter = fontList.begin(); iter != fontList.end(); ++iter) {
        delete iter->second;
    }
    fontList.clear();
}

bool ResourceManager::loadConfig(std::string filename) {
    Logger::getInstance()->logMessage(0, "ResourceManager loading config file: '%s'", filename.c_str());

    if (!resourceReader->loadConfig(filename.c_str())) {
        Logger::getInstance()->logError(0, "ResourceManager failed to load config file: '%s'", filename.c_str());
        return false;
    } else {
        configLoaded = true;
        parseConfig();
        return true;
    }
}

bool ResourceManager::parseConfig() {
    if (!configLoaded) {
        Logger::getInstance()->logError(0, "ResourceManager failed to parse resources, no config file");

        return false;
    }

    std::string sectIter = resourceReader->getFirstSection();

    while (sectIter != "") {
            std::string fname;
            if (resourceReader->hasKey(sectIter, "filename")) {
                if (resolvePath != "") {
                    fname = resolvePath + resourceReader->getString(sectIter, "filename");
                } else {
                    fname = resourceReader->getString(sectIter, "filename");
                }


                if (resourceReader->getString(sectIter, "type").compare("sprite") == 0) {
                    int fw = 0, fh = 0, fc = 0, f = 0;
                    Sprite *newSprite = new Sprite;
                    newSprite->setName(sectIter);

                    if (resourceReader->hasKey(sectIter, "frameWidth")) { fw = resourceReader->getInt(sectIter, "frameWidth", 1); }
                    if (resourceReader->hasKey(sectIter, "frameHeight")) { fh = resourceReader->getInt(sectIter, "frameHeight", 1); }
                    if (resourceReader->hasKey(sectIter, "frameColumns")) { fc = resourceReader->getInt(sectIter, "frameColumns", 1); }
                    if (resourceReader->hasKey(sectIter, "frames")) { f = resourceReader->getInt(sectIter, "frames", 1); }
                    if (resourceReader->hasKey(sectIter, "delay")) { newSprite->setDelay(resourceReader->getInt(sectIter, "delay", 0)); }

                    newSprite->loadImage(fname.c_str(), fw, fh, fc, f);

                    spriteList.insert(std::pair<std::string, Sprite*>(sectIter, newSprite));
                } else if (resourceReader->getString(sectIter, "type").compare("sound") == 0) {
                    Sound *newSample = new Sound;
                    newSample->setName(sectIter);

                    newSample->loadSound(fname.c_str());

                    soundList.insert(std::pair<std::string, Sound*>(sectIter, newSample));
                } else if (resourceReader->getString(sectIter, "type").compare("font") == 0) {
                    Font *newFont = new Font;
                    newFont->setName(sectIter);

                    int s = 0;
                    if (resourceReader->hasKey(sectIter, "size")) { s = resourceReader->getInt(sectIter, "size", 0); }

                    newFont->loadFont(fname.c_str(), s);

                    fontList.insert(std::pair<std::string, Font*>(sectIter, newFont));
                }
            }

        sectIter = resourceReader->getNextSection();
    }

    Logger::getInstance()->logMessage(0, "ResourceManager done parsing config file");
    return true;
}

Sprite* ResourceManager::getSprite(std::string name) {
    Sprite *reqSprite = spriteList[name];
    if (reqSprite != NULL) {
        return reqSprite;
    } else {
        Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name.c_str());
        return NULL;
    }
}

Sound* ResourceManager::getSound(std::string name) {
    Sound *reqSample = soundList[name];
    if (reqSample != NULL) {
        return reqSample;
    } else {
        Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name.c_str());
        return NULL;
    }
}

Font* ResourceManager::getFont(std::string name) {
    Font *reqFont = fontList[name];
    if (reqFont != NULL) {
        return reqFont;
    } else {
        Logger::getInstance()->logError(0, "Requested resource not found: '%s'", name.c_str());
        return NULL;
    }
}
}
