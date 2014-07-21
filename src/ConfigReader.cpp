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
}

bool ConfigReader::loadConfig(const char *filename)
{
    Logger::getInstance()->logMessage(0, "ConfigReader loading config file: '%s'", filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::getInstance()->logError(0, "ConfigReader failed to load config file: '%s'", filename);
        return false;
    }

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
            //line = M7engine::trimEmpty(line);
        line = M7engine::removeWhitespace(line);

            line.erase(line.begin());
            line.erase(line.end()-1);
            curSection = line;

            innerMap newMap;
            config[curSection] = newMap;

            continue;
        }

        std::vector<std::string> current = M7engine::split(line, '=');

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
    return (ConfigReader::loadConfig(ConfigReader::filename.c_str()));
}

bool ConfigReader::hasKey(std::string section, std::string key)
{
    std::map<std::string, innerMap>::iterator sectIter = ConfigReader::config.find(section);

    if (sectIter == config.end()) {
        return false;
    }

    innerMap::iterator keyIter = (*sectIter).second.find(key);

    if (keyIter == (*sectIter).second.end()) {
        return false;
    }

    return true;
}

std::string ConfigReader::getFirstSection()
{
    if (config.empty()) {
        return "";
    }

    std::map<std::string, innerMap>::iterator sectIter = config.begin();

    return (*sectIter).first;
}

std::string ConfigReader::getNextSection(std::string section)
{
    std::map<std::string, innerMap>::iterator sectIter = config.find(section);

    if (sectIter == config.end()) {
        Logger::getInstance()->logError(0, "ConfigReader tried to find nonexistent section '%s'", section.c_str());
        return "";
    }

    ++sectIter;

    if (sectIter == config.end()) {
        return "";
    } else {
        return (*sectIter).first;
    }
}

std::string ConfigReader::getString(std::string section, std::string key)
{
    std::map<std::string, innerMap>::iterator sectIter = ConfigReader::config.find(section);

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

bool ConfigReader::getBool(std::string section, std::string key, bool def)
{
    std::string value = ConfigReader::getString(section, key);
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

int ConfigReader::getInt(std::string section, std::string key, int def)
{
    std::string value = ConfigReader::getString(section, key);
    if (value.empty()) {
        return def;
    }

    return M7engine::stringToInt(value);
}
}
