/*
FileCopyEx - Extended File Copy plugin for Far 2 file manager

Copyright (C) 2004 - 2010 Serge Cheperis aka craZZy
Bugfixes: slst, CDK, Ivanych, Alter, Axxie and Nsky
Special thanks to Vitaliy Tsubin
Far 2 (32 & 64 bit) full unicode version by djdron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "array.h"
#include "objstring.h"

enum TextFormat { tfANSI, tfUnicode, tfUnicodeBE };

#define slSorted 1
#define slIgnoreCase 2

class StringList
{
public:
	StringList(void);
	virtual ~StringList(void);
//	void SetBlock(int);
//	void SetOptions(int);

	int Count();
	const String operator[](int);
	int& Values(int);
	void*& PtrValues(int);
	void Set(int, const String&);

	int Add(const String&, int=0);
	void Insert(int, const String&, int=0);
	int Add(const String&, void*);
	void Insert(int, const String&, void*);
	void Delete(int);
	void Exchange(int, int);
	void Clear();

	int Find(const String&, int=0);
// 	int PFind(const String&, int=0);
// 	int GFind(const String&, int=0);

	int LoadFrom(FILE*);
	int SaveTo(FILE*, TextFormat=tfANSI);
	int Load(const String&);
	int Save(const String&, TextFormat=tfANSI);
	void LoadFromString(const String&, wchar_t);
	void LoadFromString(const wchar_t*, wchar_t);

	void AddList(StringList&);

	struct ListItem
	{
		String str;
		union
		{
			int Data;
			void* PtrData;
		};
	};

private:
	Array<ListItem> items;
};
