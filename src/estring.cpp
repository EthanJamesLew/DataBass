#include "estring.h"
#include <iostream>
#include <cstring>
using namespace std;

namespace e
{
	EString::EString(char* cstr)
	{
		int size = strlen(cstr);
		_cstr = (char*)std::malloc(sizeof(char)*size+1);
		strcpy(_cstr, cstr);
		_size = size;
	}

	EString::EString()
	{
		
	}

	EString::~EString()
	{


	}

	void EString::cat(char* cat)
	{
		int size = strlen(cat);
		_size += size;
		_cstr = (char *)realloc(_cstr, _size*sizeof(char) + 1);
		strcat(_cstr, cat);
	}

	void EString::cat(EString cat)
	{
		int size = strlen(cat.cstr());
		_size += size;
		_cstr = (char *)realloc(_cstr, _size*sizeof(char) + 1);
		strcat(_cstr, cat.cstr());
		
	}

	bool EString::cmp(char* cstr)
	{
		return !strcmp(cstr, _cstr) ? true : false;
	}

	bool EString::cmp(EString estr)
	{
		return !strcmp(estr.cstr(), _cstr) ? true : false;
	}

	char* EString::cstr()
	{
		return _cstr;
	}

	EString EString::slice(int a, int b)
	{
		char* newStr = (char *)std::malloc(sizeof(char)*(b-a)+1);
		for (int i = a; i < b; i++)
		{
			newStr[i - a] = _cstr[i];
		}
		newStr[b - a] = '\0';
		EString estr(newStr);
		free(newStr);

		return estr;
	}

	EString EString::slice(int b)
	{
		return slice(0, b);
	}

	bool EString::isInteger()
	{
		char *next;
		long val = strtol(_cstr, &next, 10);
		val++;
		if ((next == _cstr) || (*next != '\0')) return false;
		else return true;
	}

	int EString::getInteger()
	{
		char *next;
		long val = strtol(_cstr, &next, 10);
		if ((next == _cstr) || (*next != '\0')) return false;
		else return val;
	}

	EString EString::toLower()
	{
		char* str = _cstr;
		for(; *str; ++str) *str = tolower(*str);
		EString estr(str);
		return estr;
	}

	EString& EString::operator+(EString& rhs)
	{
		cat(rhs.cstr());
		return *this;
	}

	EString& EString::operator+(char* rhs)
	{
		cat(rhs);
		return *this;
	}

	bool EString::operator==(EString rhs)
	{
		return !strcmp(rhs.cstr(), _cstr) ? true : false;
	}
	bool EString::operator==(char* rhs)
	{
		return !strcmp(rhs, _cstr) ? true : false;
	}

	char& EString::operator[] (const int idx)
	{
		if (idx < _size)
			return _cstr[idx];
		else
			return _cstr[_size-1];
	}

}


