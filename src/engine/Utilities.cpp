/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Utilities
 *  Utilities.cpp
 *  Purpose: General purpose utility functions.
 *  @author David Houchin
 */

#include "Utilities.h"

std::string M7engine::intToString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

int M7engine::stringToInt(std::string text)
{
    return std::atoi(text.c_str());
}

std::string& M7engine::removeWhitespace(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

std::vector<std::string> M7engine::split(const std::string& str, char delim)
{
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> result;

    while (std::getline(ss, item, delim))
        result.push_back(M7engine::removeWhitespace(item));

    return result;
}

std::vector<std::string> M7engine::chunkify(const std::string &str, const char &delim)
{
    std::string nextChar;
    std::vector<std::string> result;

    for (std::string::const_iterator iter = str.begin(); iter != str.end(); iter++) {
        if (*iter == delim) {
            if (!nextChar.empty()) {
                result.push_back(nextChar);
                nextChar.clear();
            }
        } else {
            nextChar += *iter;
        }
    }

    if (!nextChar.empty()) {
        result.push_back(nextChar);
    }

    return result;
}
