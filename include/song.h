#ifndef SONG_H
#define SONG_H

#include "estring.h"
#include "evector.h"

#define CHAR_LEN (2<<8)

/*
SongFields stores field names as indices
*/
enum SongFields { TITLE, ARTIST, MINUTES, SECONDS, ALBUM };

/*
Song stores song parameters as an EVector. It enforces a fixed size of 5.
*/
struct Song
{
	Song();
	Song(e::EString title, e::EString artist, e::EString minutes, e::EString seconds, e::EString album);

	e::EString& operator[](int idx){ return fields[idx]; }

	e::EVector<e::EString> fields;

	friend std::ostream& operator<<(std::ostream& os, Song& song)
	{
		os << song[TITLE] << std::endl;

		os << "Artist:   " << song[ARTIST] << std::endl;
		os << "Album:    " << song[ALBUM] << std::endl;
		os << "Duration: " << song[MINUTES] << ":" << song[SECONDS] << std::endl;
		return os;
	}
};


#endif
