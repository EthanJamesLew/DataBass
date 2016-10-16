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

MainConsole::~MainConsole()
{

}

bool MainConsole::init()
{
	lib = new SongLibrary;
	console = new MainControl(lib);
	return true;
}

void MainConsole::renderMenu()
{
	std::ifstream infile1;
	infile1.open("menu.txt");

	if (infile1.fail())
	{
		std::cout << "File failed to open.\n";
		exit(1);
	}

	do
	{
		if (infile1.peek() != EOF) std::cout << (char)infile1.get();
	} while ((infile1.good()));
}

void MainConsole::mainLoop()
{
	while (true)
	{
		std::cout << "data-bass>";
		std::cin.getline(command, 1000);
		if (!strcmp(command, "exit") | !strcmp(command, "quit") | !strcmp(command, "q") | !strcmp(command, "break"))
		{
			break;
		}
		console->execCommand(command);
	}
}

#endif
