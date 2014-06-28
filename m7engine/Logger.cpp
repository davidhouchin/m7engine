/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Logger
 *  Logger.cpp
 *  Purpose: Class to handle logging output.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Logger.h"

namespace M7engine {

Logger* Logger::loggerInstance = NULL;

Logger* Logger::getInstance() {
    if (!loggerInstance) {
        loggerInstance = new Logger;
    }

    return loggerInstance;
}

Logger::Logger() {
    logLevel = 0;
}

Logger::~Logger() {
    logFile.close();
}

bool Logger::setLogFile(const char *file) {
    filename = file;
    remove(filename);
    logFile.open(filename);
    if (!logFile.is_open()) {
        return false;
    }
    logFile.close();
    return true;
}

void Logger::logMessage(int level, const char *message, ...) {
    if ((level <= logLevel) && (filename != NULL)) {
        char buffer[99];
        va_list args;
        va_start(args, message);
        vsprintf(buffer, message, args);
        va_end(args);

        fprintf(stdout, "%f %s\n", al_get_time(), buffer);

        logFile.open(filename, std::ios::app);
        logFile << al_get_time() << " " << buffer << "\n";
        logFile.close();
    }
}

void Logger::logMessage(int level, const char *message, ALLEGRO_COLOR color, ...) {
    if ((level <= logLevel) && (filename != NULL)) {
        char buffer[99];
        va_list args;
        va_start(args, message);
        vsprintf(buffer, message, args);
        va_end(args);

		fprintf(stdout, "%f %s\n", al_get_time(), buffer);

        logFile.open(filename, std::ios::app);
		logFile << al_get_time() << " " << buffer << "\n";
        logFile.close();
    }
}

void Logger::logError(int level, const char *message, ...) {
    if ((level <= logLevel) && (filename != NULL)) {
        char buffer[99];
        va_list args;
        va_start(args, message);
        vsprintf(buffer, message, args);
        va_end(args);

		fprintf(stderr, "%f %s\n", al_get_time(), buffer);

        logFile.open(filename, std::ios::app);
		logFile << al_get_time() << " " << buffer << "\n";
        logFile.close();
    }
}

void Logger::logError(int level, const char *message, ALLEGRO_COLOR color, ...) {
    if ((level <= logLevel) && (filename != NULL)) {
        char buffer[99];
        va_list args;
        va_start(args, message);
        vsprintf(buffer, message, args);
        va_end(args);

		fprintf(stderr, "%f %s\n", al_get_time(), buffer);

        logFile.open(filename, std::ios::app);
		logFile << al_get_time() << " " << buffer << "\n";
        logFile.close();
    }
}
}
