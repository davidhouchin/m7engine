/**
 *  Utilities
 *  Utilities.cpp
 *  Purpose: General purpose utility functions.
 *  @author Alex Dantas and David Houchin
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
    std::stringstream ss(str);      // "buffer"
    std::string item;               // current thing
    std::vector<std::string> elems; // all things

    while (std::getline(ss, item, delim))
        elems.push_back(M7engine::removeWhitespace(item));

    return elems;
}
