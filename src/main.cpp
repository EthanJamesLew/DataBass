#include "mainconsole.h"
#include "songlibrary.h"
#include "eptr.h"

int main()
{
	MainConsole console;
	console.init();
	console.renderMenu();
	console.mainLoop();

	return 0;
}
