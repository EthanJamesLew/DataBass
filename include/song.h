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
	Song(){ fields = e::EVector<e::EString>(5); }
	Song(e::EString title, e::EString artist, e::EString minutes, e::EString seconds, e::EString album)
	{
		fields = e::EVector<e::EString>(5);
		fields[TITLE] = title;
		fields[ARTIST] = artist;
		fields[MINUTES] = minutes;
		fields[SECONDS] = seconds;
		fields[ALBUM] = album;
	}

	e::EString& operator[](int idx){ return fields[idx]; }

	e::EVector<e::EString> fields;
};

std::ostream& operator<<(std::ostream& os, Song& song)
{
	os << song[TITLE] << std::endl;

	os << "Artist:   " << song[ARTIST] << std::endl;
	os << "Album:    "  << song[ALBUM] << std::endl;
	os << "Duration: "  << song[MINUTES] << ":" << song[SECONDS] << std::endl;
	return os;
}

std::istream& operator >>(std::istream &is, e::EString &song)
{
	char str[CHAR_LEN] = {0};
	is >> str;
	song = str;
	return is;
}

#endif
