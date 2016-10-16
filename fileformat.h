#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include "estring.h"
#include "SongLibrary.h"

#include <fstream>
#include <cstring>

e::EVector<e::EString> getWords(e::EString& vec, char del = ' ')
{
	e::EVector<e::EString> words;
	int prev = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == del && i != 0 && i != vec.size() - 1)
		{
			e::EString word = vec.slice(prev, i);
			if (!(word == e::EString(" ") || word == e::EString("")))
				words.push_back(vec.slice(prev, i));
			prev = i + 1;
		}
	}
	words.push_back(vec.slice(prev, vec.size()));
	return words;
}

class FileFormat
{
public:
	void projectToFile(SongLibrary& lib, e::EString filename)
	{
		std::ofstream file;
		file.open(filename.cstr());
		for (int i = 0; i < lib.getSize(); i++)
		{
			Song* e = lib.searchOrder(i);
			file << (*e)[TITLE] << ";";
			file << (*e)[ARTIST] << ";";
			file << (*e)[MINUTES] << ";";
			file << (*e)[SECONDS] << ";";
			file << (*e)[ALBUM] << std::endl;
		}
		file.close();
	}

	void fileToProject(SongLibrary& lib, e::EString filename)
	{
		std::ifstream file;
		file.open(filename.cstr());
		while (file.peek() != EOF)
		{
			char line[256];
			file.getline(line, 256);
			e::EVector<e::EString> songItems = getWords(e::EString(line), ';');
			if (songItems.size() != 5) file.close();//Throw Error
			Song e;
			e[TITLE] = songItems[TITLE];
			e[ARTIST] = songItems[ARTIST];
			e[MINUTES] = songItems[MINUTES];
			e[SECONDS] = songItems[SECONDS];
			e[ALBUM] = songItems[ALBUM];
			lib.addItem(e);
		}
		file.close();
	}
};
#endif