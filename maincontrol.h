#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include "eptr.h"
#include "songlibrary.h"
#include "fileformat.h"
#include "ehash.h"

enum ComKeys: unsigned int
{
	ADD = 993596020,
	EDIT = 1541920145,
	DELETETITLE = 3770845628,
	DELETEIDX = 1544085933,
	SEARCHARTIST = 1902126709,
	SEARCHALBUM = 3877959697,
	SEARCHTITLE = 1276617220,
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

class MainControl
{
	friend class Com;
public:
	MainControl(e::EPtr<SongLibrary>& l) :lib(l){ file = new FileFormat; file->fileToProject(*lib, "songs.txt"); }

	~MainControl(){ file->projectToFile(*lib, "cong1.txt"); }

	void execCommand(char* command)
	{
		trim(command);
		vec = getWords((e::EString)command);
		
		unsigned key = hash(vec[0]);

		switch (key)
		{
		case ADD: add(); break;
		case EDIT:std::cout << "edit command" << std::endl; break;
		case DELETEIDX: delidx(); break;
		case DELETETITLE: ; break;
		case SEARCHALBUM:salbum(); break;
		case SEARCHARTIST: sartist(); break;
		case SEARCHTITLE: stitle(); break;
		case LS: ls(); break;
		default: std::cout << "Unknown command " << vec[0] << std::endl; break;
		}
		std::cout << std::endl;

	}
	
	
private:

	e::EHash_fnv1a<e::EString> hash;
	e::EVector<e::EString> vec;

	e::EPtr<SongLibrary> lib;
	e::EPtr<FileFormat> file;

	void add();
	void edit();
	void delidx();
	void deltitle();
	void search(int idx);
	void salbum();
	void sartist();
	void stitle();
	void ls();
};

void MainControl::add()
{
	Song song = Song();
	char* com = new char(256);

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
		std::cin.getline(com, 256);
		len = com;
		e::EVector<e::EString> temp = getWords( len, ':');
		song[MINUTES] = temp[0];
		song[SECONDS] = temp[1];

		if (temp.size() == 2) break;
		else std::cout << "Could not understand input." << std::endl;
	}

	std::cout << "\tEnter an album: ";
	std::cin.getline(com, 256);
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
			int idx = vec[1].getInteger()-1;
			if (idx >= lib->getSize() || idx < 0) std::cout << "Invalid index range." << std::endl;
			else lib->deleteNumIndex(idx);
		}
		else std::cout << "Could not read index as integer." << std::endl;
	}
}

void MainControl::deltitle()
{

}

e::EString vecToString(e::EVector<e::EString> vec, int a, int b, char* space = " ")
{
	e::EString result = vec[a];
	if (vec.size() > 2) result = result + " ";
	for (int i = a+1; i < b; i++)
	{
		result = result + vec[i];
		if (i != b-1)
		result = result + space;
		
	}
	std::cout << "---" << result << "---" << std::endl;
	return result;
}

void MainControl::search(int idx)
{
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

void MainControl::ls()
{
	int idx = 1;
	std::cout << "Data Bass Songs" << std::endl << std::endl;
	for (int i = 0; i < lib->getSize(); i++)
	{
		std::cout << *(lib->searchOrder(i)) <<"Index: " << idx << std::endl<<std::endl ;
		idx++;
	}
}


#endif