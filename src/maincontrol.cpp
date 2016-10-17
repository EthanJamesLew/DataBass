#ifndef MAINCONTROL_CPP
#define MAINCONTROL_CPP

#include "maincontrol.h"

bool isFile(e::EString file)
{
	std::ifstream infile(file.cstr());
	return infile.good();
}


enum ComKeys : unsigned int
{
	ADD = 993596020,
	EDIT = 1541920145,
	DELETETITLE = 3770845628,
	DELETEIDX = 1544085933,
	SEARCHARTIST = 1902126709,
	SEARCHALBUM = 3877959697,
	SEARCHTITLE = 1276617220,
	SAVE = 3439296072,
	LOAD = 3859241449,
	LS = 1446109160

};

char* trim(char *str)
{
	char* end;

	// Trim leading space
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator
	*(end + 1) = 0;

	return str;
}

MainControl::MainControl(e::EPtr<SongLibrary>& l) :lib(l)
{ 
	file = new FileFormat; file->fileToProject(*lib, e::EString((char*)"songs.txt")); 
}

MainControl::~MainControl()
{
	file->projectToFile(*lib, e::EString((char*)"songs.txt")); 
}

void MainControl::execCommand(char* command)
{
	trim(command);
	e::EString com = (e::EString)command;
	vec = getWords(com);

	unsigned key = hash(vec[0]);

	switch (key)
	{
	case ADD: add(); break;
	case EDIT:std::cout << "edit command" << std::endl; break;
	case DELETEIDX: delidx(); break;
	case DELETETITLE:; break;
	case SEARCHALBUM:salbum(); break;
	case SEARCHARTIST: sartist(); break;
	case SEARCHTITLE: stitle(); break;
	case LS: ls(); break;
	case SAVE: save(); break;
	case LOAD: load(); break;
	default: std::cout << "Unknown command " << vec[0] << std::endl; break;
	}
	std::cout << std::endl;

}

void MainControl::add()
{
	Song song = Song();
	char com[CHAR_LEN] = { 0 };

	std::cout << "\tEnter a title: ";
	std::cin.getline(com, 256);
	song[TITLE] = com;

	std::cout << "\tEnter a artist: ";
	std::cin.getline(com, 256);
	song[ARTIST] = com;

	e::EVector<e::EString> temp;

	while (true)
	{
		std::cout << "\tEnter a duration (mm:ss): ";
		e::EString len;
		std::cin.getline(com, CHAR_LEN);
		len = com;
		e::EVector<e::EString> temp = getWords(len, ':');
		song[MINUTES] = temp[0];
		song[SECONDS] = temp[1];


		
		if (temp.size() == 2)
		{
			if ((temp[0].isInteger() && temp[1].isInteger()))
			{
				if (temp[0].getInteger() >-1 && temp[1].getInteger() > -1 &&temp[1].getInteger() < 60)
					break;
				else
				{
					std::cout << "\t\tInvalid time" << std::endl;
				}
			}
			else
			{
				std::cout << "\t\tCould not read as number" << std::endl;
			}
		}
		
		else std::cout << "Could not understand input." << std::endl;
	}

	std::cout << "\tEnter an album: ";
	std::cin.getline(com, CHAR_LEN);
	song[ALBUM] = com;

	lib->addItem(song);

}

void MainControl::edit()
{

}

void MainControl::delidx()
{
	if (vec.size() > 2) std::cout << "Too many parameters. Pass an idx number." << std::endl;
	else if (vec.size() == 1) std::cout << "An index number is needed." << std::endl;
	else
	{
		if (vec[1].isInteger())
		{
			unsigned idx = vec[1].getInteger() - 1;
			if (idx >= lib->getSize() || idx < 0) std::cout << "Invalid index range." << std::endl;
			else lib->deleteNumIndex(idx);
		}
		else std::cout << "Could not read index as integer." << std::endl;
	}
}

void MainControl::deltitle()
{

}

e::EString vecToString(e::EVector<e::EString> vec, unsigned a, unsigned b, char* space = (char*)" ")
{
	e::EString result = vec[a];
	if (vec.size() > 2) result = result + space;
	for (unsigned i = a + 1; i < b; i++)
	{
		result = result + vec[i];
		if (i != b - 1)
			result = result + space;

	}
	std::cout << "---" << result << "---" << std::endl;
	return result;
}

void MainControl::search(unsigned idx)
{
	if (vec.size() == 1)
	{
		std::cout << "Nothing to search" << std::endl;
		return;
	}
	e::EVector<Song> results = e::EVector<Song>();
	e::EString str = vecToString(vec, 1, vec.size());
	results = lib->searchSongs(idx, str);
	for (Song* it = results.begin(); it != results.end(); ++it)
		std::cout << *it << std::endl;
}

void MainControl::salbum()
{

	search(ALBUM);
}

void MainControl::sartist()
{
	search(ARTIST);
}

void MainControl::stitle()
{
	search(TITLE);
}

bool MainControl::checkFile()
{
	if (vec.size() > 2)
	{
		std::cout << "Filename must be one word." << std::endl;
	}
	else if (vec.size() == 1)
	{
		std::cout << "Provide a filename" << std::endl;
	}
	else
	{
		return true;
	}
	return false;
}

void MainControl::save()
{
	if (checkFile())
	{
		file->projectToFile(*lib, vec[1]);
	}

}

void MainControl::load()
{
	if (checkFile())
	{
		if (!isFile(vec[1]))
		{
			std::cout << vec[1] << " does not exist." << std::endl;
			return;
		}
		file->fileToProject(*lib, vec[1]);
	}
}

void MainControl::ls()
{
	int idx = 1;
	std::cout << "Data Bass Songs" << std::endl << std::endl;
	for (unsigned i = 0; i < lib->getSize(); i++)
	{
		std::cout << *(lib->searchOrder(i)) << "Index: " << idx << std::endl << std::endl;
		idx++;
	}
}

#endif
