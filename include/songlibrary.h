#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include "evector.h"
#include "estring.h"

#include "song.h"


/*
Library is an abstract class that define storage and searching of a library type
*/
template <class T>
class Library
{
public:
	void addItem(T item){ items.push_back(item); }
	
	template <class V>
	T* searchIndex(unsigned idx, V val)
	{
		for (T* it = items.begin(); it != items.end(); ++it)
		{
			if ((*it)[idx] == val)
				return it;
		}
		return NULL;
	}

	template <class V>
	e::EVector<T> searchMultiIndex(unsigned idx, V val)
	{
		e::EVector<T> results;
		for (T* it = items.begin(); it != items.end(); ++it)
		{
			if ((*it)[idx] == val)
				results.push_back(*it);
		}
		return results;
	}

	T* searchOrder(unsigned idx)
	{
		return &items[idx];
	}

	size_t getSize(){ return items.size(); }
	

	template <class V>
	bool deleteIndex(unsigned idx, V val)
	{
		for (T* it = items.begin(); it != items.end(); ++it)
		{
			if ((*it)[idx] == val)
			{
				std::swap(*it, items.back());
				items.pop_back();
				return true;
			}
		}
		return false;
	}

	bool deleteNumIndex(unsigned idx)
	{
		if (idx >= items.size() || idx < 0) return false;
		else
		{
			std::swap(items[idx], items.back());
			items.pop_back();
			return true;
		}
	}

private:
	e::EVector<T> items;
};

/*
SongLibrary is a library type that stores songs
*/

class SongLibrary: public Library<Song>
{
public:
	Song* searchSong(int idx, e::EString val)
	{
		return searchIndex<e::EString>(idx, val);
	}

	Song* searchSong(int idx, char* val)
	{
		return searchIndex<e::EString>(idx, val);
	}

	e::EVector<Song> searchSongs(int idx, e::EString val)
	{
		return searchMultiIndex<e::EString>(idx, val);
	}

	e::EVector<Song> searchSongs(int idx, char* val)
	{
		return searchMultiIndex<char*>(idx, val);
	}
	
	bool deleteSong(int idx, e::EString val)
	{
		return deleteIndex<e::EString>(idx, val);
	}

	bool deleteSong(int idx, char* val)
	{
		return deleteIndex<char*>(idx, val);
	}

};
#endif

