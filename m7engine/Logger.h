/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

namespace M7engine
{
class Logger
{
public:
	Logger(const char *file);
	virtual ~Logger();

	void setLoggingLevel(int level) { logLevel = level; }
	bool setLogFile(const char *file);

	void logMessage(int level, const char *message, ...);
	void logMessage(const char *message, int level, ALLEGRO_COLOR color);

	void logError(const char *message, int level);
	void logError(const char *message, int level, ALLEGRO_COLOR color);

private:
	int logLevel;
	const char *filename;
	std::ofstream logFile;
};
};

#endif