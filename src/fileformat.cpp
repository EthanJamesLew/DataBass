#include "fileformat.h"

void FileFormat::projectToFile(SongLibrary& lib, e::EString filename)
{
	std::ofstream file;
	file.open(filename.cstr());
	for (unsigned i = 0; i < lib.getSize(); i++)
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

void FileFormat::fileToProject(SongLibrary& lib, e::EString filename)
{
	std::ifstream file;
	file.open(filename.cstr());
	while (file.peek() != EOF)
	{
		char line[256];
		file.getline(line, 256);
		e::EString li = (e::EString) line;
		e::EVector<e::EString> songItems = getWords(li, ';');
		if (songItems.size() != 5) break;//Throw Error
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

e::EVector<e::EString> getWords(e::EString& vec, const char del)
{
	e::EVector<e::EString> words;
	int prev = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == del && i != 0 && i != vec.size() - 1)
		{
			e::EString word = vec.slice(prev, i);
			if (!(word == (char*)" " || word == (char*)""))
				words.push_back(vec.slice(prev, i));
			prev = i + 1;
		}
	}
	words.push_back(vec.slice(prev, vec.size()));
	return words;
}