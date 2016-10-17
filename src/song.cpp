#include "song.h"

Song::Song()
{ 
	fields = e::EVector<e::EString>(5); 
}

Song::Song(e::EString title, e::EString artist, e::EString minutes, e::EString seconds, e::EString album)
{
	fields = e::EVector<e::EString>(5);
	fields[TITLE] = title;
	fields[ARTIST] = artist;
	fields[MINUTES] = minutes;
	fields[SECONDS] = seconds;
	fields[ALBUM] = album;
}
