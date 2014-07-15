/**
 *  Utilities
 *  Utilities.cpp
 *  Purpose: General purpose utility functions.
 *  @author Alex Dantas and David Houchin
 */

#include "Utilities.h"

std::string M7engine::intToString(int num)
{
    return std::to_string(num);
}

int M7engine::stringToInt(std::string text)
{
    int i;
    for (i = 0; i < text.length(); i++) {
        if (!std::isdigit(text[i])) {
            return 0; //String had non integer characters.. returning 0
        }
    }
    return std::stoi(text);
}

std::string& M7engine::trimEmptyLeft(std::string &str)
{
    // Using some std black magic. Taken from here:
    // http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

    // Here we create a predicate to be compared.
    // (In other words, "an element that `isspace`")
    std::pointer_to_unary_function<int, int> function = std::ptr_fun<int, int>(std::isspace);

    // This returns the first element that's not a space.
    //
    // It will go inside `str` looking for the first
    // element that matches a predicate.

    std::string::iterator it = std::find_if(str.begin(),
                                            str.end(),

                                            // And here we negate the predicate
                                            // ("an element that's NOT `isspace`")
                                            std::not1(function));

    // And here we erase everything up to it.
    str.erase(str.begin(),
              it);

    return str;
}

std::string& M7engine::trimEmptyRight(std::string& str)
{
    // More std magic. Sorry for the mess.
    // Please check method above (`ltrim`).

    str.erase(std::find_if(str.rbegin(),
                           str.rend(),
                           std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              str.end());

    return str;
}

std::string& M7engine::trimEmpty(std::string& str)
{
    return M7engine::trimEmptyRight(M7engine::trimEmptyRight(str));
}

std::vector<std::string> M7engine::split(const std::string& str, char delim)
{
    std::stringstream ss(str);      // "buffer"
    std::string item;               // current thing
    std::vector<std::string> elems; // all things

    while (std::getline(ss, item, delim))
        elems.push_back(M7engine::trimEmpty(item));

    return elems;
}
