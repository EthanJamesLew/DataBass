#ifndef MAINCONSOLE_H
#define MAINCONSOLE_H

#include <fstream>
#include <iostream>
#include "estring.h"
#include "maincontrol.h"
#include "songlibrary.h"
#include "eptr.h"
#include "fileformat.h"



class MainConsole
{
public:
	~MainConsole();
	void mainLoop();
	void renderMenu();
	bool init();
private:
	char command[CHAR_LEN];
	e::EPtr<MainControl> console;
	e::EPtr<SongLibrary> lib;
};

#endif
