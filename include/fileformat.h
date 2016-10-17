#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include "estring.h"
#include "songlibrary.h"

#include <fstream>
#include <cstring>


class FileFormat
{
public:
	void projectToFile(SongLibrary& lib, e::EString filename);

	void fileToProject(SongLibrary& lib, e::EString filename);
};

e::EVector<e::EString> getWords(e::EString& vec, const char del = ' ');

#endif
