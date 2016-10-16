#include "mainconsole.h"
#include "songlibrary.h"
#include "eptr.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	MainConsole console;
	console.init();
	console.renderMenu();
	console.mainLoop();

	return 0;
}