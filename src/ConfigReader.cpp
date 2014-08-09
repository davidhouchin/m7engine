/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Configuration Reader
 *  ConfigReader.cpp
 *  Purpose: Reads a configuration file to set engine options.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "ConfigReader.h"

namespace M7engine {
ConfigReader::ConfigReader()
{
}

ConfigReader::~ConfigReader()
{
    config.clear();
}

bool ConfigReader::loadConfig(std::string filename)
{
    Logger::getInstance()->logMessage(0, "ConfigReader loading config file: '%s'", filename.c_str());

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        Logger::getInstance()->logError(0, "ConfigReader failed to load config file: '%s'", filename.c_str());
        return false;
    }

    this->filename = filename;

    bool inSection = false;
    std::string curSection;

    while (!file.eof()) {
        std::string line;
        std::getline(file, line, '\n');

        if (line.empty()) {
            continue;
        }

        if (line[0] == COMMENT_CHAR) {
            continue;
        }

        if (line[0] == SECTION_BEGIN_CHAR) {
            inSection = true;

            line = removeWhitespace(line);
            line.erase(line.begin());
            line.erase(line.end()-1);

            curSection = line;

            innerMap newMap;
            config[curSection] = newMap;

            continue;
        }

        std::vector<std::string> current = split(line, '=');

        if (ConfigReader::hasKey(curSection, current.front())) {
            Logger::getInstance()->logError(0, "ConfigReader found existing key '" +
                                            current.front() +
                                            "' that maps to '" +
                                            current.back() +
                                            "'");
            continue;
        }

        if (inSection) {
            std::pair<std::string, std::string> keyPair = std::make_pair(current.front(), current.back());
            config[curSection].insert(keyPair);
        }
    }

    Logger::getInstance()->logMessage(0, "ConfigReader done parsing config file");
    return true;
}

bool ConfigReader::reloadConfig()
{
    if (filename != "") {
        return (loadConfig(filename));
    } else {
        return false;
    }
}

bool ConfigReader::hasKey(std::string section, std::string key)
{
    std::map<std::string, innerMap>::iterator sectIter = config.find(section);

    if (sectIter == config.end()) {
        return false;
    }

    innerMap::iterator keyIter = (*sectIter).second.find(key);

    if (keyIter == (*sectIter).second.end()) {
        return false;
    }

    return true;
}

bool ConfigReader::hasSection(std::string section)
{
    std::map<std::string, innerMap>::iterator sectIter = config.find(section);

    if (sectIter == config.end()) {
        return false;
    }

    return true;
}

std::string ConfigReader::getFirstSection()
{
    if (config.empty()) {
        return "";
    }

    mapIter = config.begin();

    return (*mapIter).first;
}

std::string ConfigReader::getNextSection()
{
    ++mapIter;

    if (mapIter == config.end()) {
        return "";
    } else {
        return (*mapIter).first;
    }
}

std::string ConfigReader::getString(std::string section, std::string key)
{
    std::map<std::string, innerMap>::iterator sectIter = config.find(section);

    if (sectIter == config.end()) {
        Logger::getInstance()->logError(0, "ConfigReader tried to find nonexistent section '%s'", section.c_str());
        return "";
    }

    innerMap::iterator keyIter = (*sectIter).second.find(key);

    if (keyIter == (*sectIter).second.end()) {
        Logger::getInstance()->logError(0, "ConfigReader tried to find nonexistent key '%s' in section '%s'", key.c_str(), section.c_str());
        return "";
    }

    return (*keyIter).second;
}

std::string ConfigReader::getString(std::string section, std::string key, std::string def)
{
    std::map<std::string, innerMap>::iterator sectIter = config.find(section);

    if (sectIter == config.end()) {
        return def;
    }

    innerMap::iterator keyIter = (*sectIter).second.find(key);

    if (keyIter == (*sectIter).second.end()) {
        return def;
    }

    return (*keyIter).second;
}

bool ConfigReader::getBool(std::string section, std::string key)
{
    std::string value = getString(section, key);
    if (value.empty()) {
        return false;
    }

    if ((value.compare("true") == 0) ||
        (value.compare("yes")  == 0) ||
        (value.compare("1") == 0)) {
        return true;
    }

    return false;
}

bool ConfigReader::getBool(std::string section, std::string key, bool def)
{
    std::string value = getString(section, key, "");
    if (value.empty()) {
        return def;
    }

    if ((value.compare("true") == 0) ||
        (value.compare("yes")  == 0) ||
        (value.compare("1") == 0)) {
        return true;
    }

    return false;
}

int ConfigReader::getInt(std::string section, std::string key)
{
    std::string value = getString(section, key);
    if (value.empty()) {
        return -1;
    }

    return stringToInt(value);
}

int ConfigReader::getInt(std::string section, std::string key, int def)
{
    std::string value = getString(section, key, "");
    if (value.empty()) {
        return def;
    }

    return stringToInt(value);
}
}
